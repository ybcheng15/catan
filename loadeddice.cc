/*
Update Notes:

[ Yi Bo July 21 15:52 ] added getNumber()

Fix Requirement:

[ Aiden July 22 2: 26 ] FairDice scope used in loadeddice.cc

*/

#include "loadeddice.h"
#include <iostream>

using namespace std;

LoadedDice::LoadedDice() {}

int LoadedDice::getNumber() const
{

    cout << "Input a roll between 2 and 12:" << endl << "> ";

    int i;
    while (cin >> i)
    {
        if (cin.eof()) {
            throw true;
        }
        if (i >= 2 && i <= 12)
        {
            break;
        }
        else
        {
            cout << "Invalid roll." << endl;
            cout << "Input a roll between 2 and 12:" << endl << "> ";
        }
    }
    return i;
}
