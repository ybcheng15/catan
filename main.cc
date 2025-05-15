/*
Update Notes:


Fix Requirement:

Missing:
        [DONE]1) need some way to load only the board
        [DONE]2) need to load a random board (tile distrubutiion 3.5.5)
        3) need to give Catan a seed field to pass on the seed to all shuffle functions
            OR make seed a global constant**
        4) need ctor and dtor for all classes (espcially Catan and Tile)
        5) change uneeded public functions into private
        6) NEED TO DISPLAY > where input is needed (see 4.5)
        7) backup.sv implementation (see 4.5)

*/
#include <iostream>
#include <string>
#include <sstream>
#include "catan.h"
using namespace std;

int main(int argc, char *argv[])
{

    // cmd line interface
    bool givenBoard = false;

    Catan *catan = new Catan{};
    string boardLayout;

    for (int i = 1; i < argc; ++i)
    {
        string str = argv[i];
        if (str == "-seed")
        {
            if (i + 1 < argc)
            {
                string s = argv[i + 1];
                istringstream ss{s};
                ss >> seed;
            }
        }
        else if (str == "-load")
        {
            if (i + 1 < argc)
            {
                boardLayout = catan->loadGameState(argv[i + 1]);
                givenBoard = true;
            }
        }
        else if (str == "-board")
        {
            if (i + 1 < argc)
            {
                boardLayout = catan->loadBoardOnly(argv[i + 1]);
                givenBoard = true;
            }
        }
        else if (str == "-random-board" && !givenBoard)
        {
            givenBoard = false;
        }
    }

    if (!givenBoard)
    {
        boardLayout = catan->loadRandom();
    }

    // 4.1
    catan->initialSetup();

    while (true)
    {

        while (catan->checkWinner() == Colour::NoColour)
        {
            try
            {
                catan->playTurn();
            }
            catch (bool)
            {
                cout << "User Entered EOF - Game over. Current game state is saved to backup.sv." << endl;
                catan->save("backup.sv");
		delete catan;
		return 0;
            }
        }

        // game ended
        cout << "Would you like to play again?" << endl
             << "> ";
        string i;
        while (cin >> i)
        {
            if (i == "yes")
            {
                delete catan;
                catan = new Catan{};
                catan->loadBoardOnlyFromStr(boardLayout);
                catan->initialSetup();
                break;
            }
            else if (i == "no")
            {
                delete catan;
                return 0;
            }
        }
        if (cin.eof()) {
            delete catan;
            return 0;
        }
    }
}
