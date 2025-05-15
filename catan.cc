/*
Update Notes:
[ Aiden July 18 2:46 ] : 1) Created buildRes()

[ Yi Bo July 18 21:32 ] : 1) Created nextPlayer()
                          2) created steal() (WIP)

[ Aiden July 18 00:46 ] : 1) Created buildRoad()

[ Frances July 19 16:35 ] : 1) Added include <fstream>
                            2) Created save(fileName);
                            3) Created getNextTurn()

[ Yi Bo July 19 18:00 ] : continued implenentation of steal() (WIP)

[ Aiden July 19 22:10 ] : 1) changed codes like inventory.Brick.second to inventory.curInv[Resource::Brick] or inventory.curInv.at(Resource::Brick)
                                due to changes on fields in Inventory struct.
                          2) created trade()

[ Yi Bo July 21 00:40 ] 1) completed steal()
                        2) (needed rng in steal()) so added #include <chrono> #include <random> #include <algorithm>
                        3) added resource2Str()

[ Yi Bo July 21 15:57 ] added include <vector>

[ Yi Bo July 21 23:47 ] 1) added playTurn()

[ Aiden July 22 2:54 ] 1) Moved helper functions which convert between enum class and string to enum.cc file; declared in enum.h
                       2) trade() done.

[ Frances July 22 10:20 ] : 1) Created load(fileName)

[ Yi Bo July 22 13:51 ] 1) renamed roll() to distribute(int)
                        2) implemented distribute() into playTurn()
                        3) implemented checkWinner()
                        4) implemented deduct()

[ Yi Bo July 23 13:21 ] 1) added const string param type for load() and save()

[ Yi Bo July 24 13:59 ] 1) added loadRandom()
                        2) changed load() to loadGameState()
                        3) added loadBoardOnly()

[ July 24 21:09 ] 1) corrected some implementation in save()
                2) added include <fstream>
                3) corrected some implementation in steal()
                4) corrected some implementation in loadGameState()
                5) included <sstream>
                6) added ~Catan();
                7) add const to checkWinner()
                8) change something in loadBoardOnly and loadRandom
                9) added Catan() (initializer)

[ July 25 0:23 ] : 1) change some implementation in steal()

[ Frances July 26 14:40 ] : 1) change ">" to "> "

Fix Requirement:
[ Yi Bo July 19 20:42 ] : - in steal(), colourToString() (and more) are not defined, but it is defined in builder.cc
                          - maybe we can store enumToString() functions in another class in enum.h
                            so we can reuse.

[ Aiden July 22 3:47 ] : need exception for all parts that include readin

[ Aiden July 22 3:47 ] : consider moving trade() to Builder class
                         Created the lines in roll() that's associated to updateResOnTile()

[ Yi Bo July 22 13:51 ] 1) might need constants for some numbers, (like 7 for geese and more)
                        2) I think trade should stay in Catan since it requires other Builders (i.e. needs builderList)

[ Frances July 24 21:04 ] : 1) need to handle the name of the saving file in main

*/

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "catan.h"
#include "builder.h"
//#include "inventory.h"

using namespace std;

// private methods:
void Catan::nextPlayer()
{
    ++activeBuilderIndex;

    if (activeBuilderIndex == builderList.size())
    {
        activeBuilderIndex = 0;
    }
}

// public methods

void Catan::status() const
{
    for (auto builder : builderList)
    {
        builder->printStatus();
    }
}

void Catan::steal()
{
    Builder *stealer = builderList.at(activeBuilderIndex);
    Colour stealerColour = stealer->getColour();

    // check Geese location
    int geeseTileNum = board->getGeese().getTileNumber();
    vector<Tile> tileList = board->getTileList();
    Tile geeseTile = tileList[geeseTileNum];

    vector<Observer *> geeseTileVertices = geeseTile.getObservers();

    vector<Builder *> stealable;
    // loop through builderList instead of vertexList, since we dont want repeated Colours, also in player order order
    for (auto builder : builderList)
    {
        if (builder != stealer)
        {
            bool haveRes = false;
            for (auto vertex : geeseTileVertices)
            {
                Colour vertexColour = vertex->getColour();
                if (vertexColour == builder->getColour())
                {
                    haveRes = true;
                    break;
                }
            }

            // check builder have non-zero inventory
            if (haveRes)
            {
                // inv check here
                Inventory inv = builder->getInventory();
                for (auto i : inv.curInv)
                {
                    if (i.second > 0)
                    {
                        stealable.emplace_back(builder);
                        break;
                    }
                }
            }
        }
    }

    if (stealable.empty())
    {
        cout << "Builder " << colour2Str(stealerColour) << " has no builders to steal from." << endl;
    }
    else
    {
        cout << "Builder " << colour2Str(stealerColour) << " can choose to steal from ";
        for (auto builder : stealable)
        {
            // cout formating purposes
            if (builder == stealable.front())
            {
                cout << colour2Str(builder->getColour());
            }
            else
            {
                cout << ", " << colour2Str(builder->getColour());
            }
        }
        cout << "." << endl;
        cout << "Choose a builder to steal from." << endl
             << "> ";

        string input;
        while (cin >> input)
        {
            if (cin.eof())
            {
                throw true;
            }
            bool foundVictim = false;
            for (auto victim : stealable)
            {
                if (input == colour2Str(victim->getColour()))
                {
                    foundVictim = true;
                    Inventory &victimInv = victim->getInventory();
                    Inventory &stealerInv = stealer->getInventory();

                    // steal system: get ALL (literally) resources in a vector, shuffle it and use the first element
                    vector<Resource> allVictimResource = victimInv.vectorizeInv();

                    // shuffle vector and get the first Resource
                    shuffle(allVictimResource.begin(), allVictimResource.end(), std::default_random_engine(seed));

                    Resource stealResource = allVictimResource.front();

                    // modify both Inventory accordingly
                    victimInv.curInv.at(stealResource) -= 1;
                    stealerInv.curInv.at(stealResource) += 1;
                    victimInv.reconcile();
                    stealerInv.reconcile();
                    cout << "Builder " << colour2Str(stealerColour) << " steals " << resource2Str(stealResource) << " from builder " << colour2Str(victim->getColour()) << "." << endl;
                    break;
                }
            }

            if (foundVictim)
            {
                break;
            }
            else
            {
                cout << "Please input a valid victim." << endl
                     << "> ";
            }
        }
    }
}

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^    Aiden Begin    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void Catan::buildRes(int vertexNum, Builder *builder)
{
    board->colourVertex(vertexNum, builder, false);
}

void Catan::improveRes(int vertexNum, Builder *builder)
{
    board->upgradeVertex(vertexNum, builder);
}

void Catan::buildRoad(int edgeNum, Builder *builder)
{
    board->colourEdge(edgeNum, builder);
}

void Catan::trade(string colour, string give, string take)
{
    int tBuilderIndex = static_cast<int>(conv2Colour(colour)) - 1;
    Resource rGive = conv2Resource(give);
    Resource rTake = conv2Resource(take);
    Builder *tBuilder = builderList[tBuilderIndex];
    Builder *aBuilder = builderList[activeBuilderIndex];
    if (aBuilder->getInventory().curInv[rGive] >= 1) // active builder has enough resource to give
    {
        cout << colour2Str(aBuilder->getColour()) << " offers " << colour2Str(tBuilder->getColour()) << " one " << give << " for one " << take << "." << endl;
        cout << "Does " << colour2Str(tBuilder->getColour()) << " accept this offer?" << endl
             << "> ";
        string answer;
        while (true)
        {
            if (!(cin >> answer))
            {
                if (cin.eof())
                {
                    throw true;
                }
                cin.clear();
                cin.ignore();
                cout << "> ";
                continue;
            }
            if (answer == "no") // offer rejected
            {
                cout << colour2Str(tBuilder->getColour()) << " refused the offer." << endl;
            }
            else if (answer == "yes" && tBuilder->getInventory().oldInv[rTake] >= 1) // offer accpeted and the opposite has enough resource to trade
            {
                // Update the opposite's inventory
                tBuilder->getInventory().curInv[rTake] -= 1;
                tBuilder->getInventory().curInv[rGive] += 1;
                tBuilder->getInventory().reconcile();
                cout << colour2Str(tBuilder->getColour()) << " gets one " << give << " and lost one " << take << endl; // print update
                // Update the active Builder's inventory
                aBuilder->getInventory().curInv[rGive] -= 1;
                aBuilder->getInventory().curInv[rTake] += 1;
                aBuilder->getInventory().reconcile();
                cout << colour2Str(aBuilder->getColour()) << " gets one " << take << " and lost one " << give << endl; // print update
            }
            else if (answer == "yes" && tBuilder->getInventory().oldInv[rTake] < 1) // offer accpetes but not enough resource
            {
                cout << colour2Str(tBuilder->getColour()) << " accpets the offer but has not enough resource to complete the trade." << endl;
            }
            else
            {
                cout << "Invalid answer. Please enter only yes/no!" << endl
                     << "> ";
                continue;
            }
            break;
        }
    }
    else
    {
        cout << "You do not have enough resources." << endl;
    }
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^    Aiden End    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// save(fileName) saves the current game status to fileName, if fileName is
//  empty string then saves the current game status to backup.sv
void Catan::save(const string fileName)
{
    ofstream outfile;
    outfile.open(fileName);

    outfile << activeBuilderIndex << '\n';
    outfile.close();

    for (auto builder : builderList)
    {
        builder->save(fileName);
    }

    board->save(fileName);

    board->getGeese().save(fileName);
}

void Catan::playTurn()
{

    Builder *currentBuilder = builderList.at(activeBuilderIndex);
    Colour currentColour = currentBuilder->getColour();

    cout << "Builder " << colour2Str(currentColour) << "’s turn." << endl;

    // dice

    string i;
    while (true)
    {
        cout << "> ";
        cin >> i;
        if (cin.eof())
        {
            throw true;
        }
        if (i == "roll")
        {
            break;
        }
        else if (i == "load")
        {
            currentBuilder->swapDice(DiceType::Loaded);
        }
        else if (i == "fair")
        {
            currentBuilder->swapDice(DiceType::Fair);
        }
        else
        {
            cout << "Invalid command." << endl;
        }
    }

    int roll = currentBuilder->roll();
    cout << "You rolled a " << roll << "." << endl;
    if (roll == 7)
    {
        deduct(2, 10);
        board->getGeese().moveGeese();
        steal();
    }
    else
    {
        distribute(roll);
    }

    // during turn
    while (true)
    {
        cout << "> ";
        cin >> i;
        if (cin.eof())
        {
            throw true;
        }
        if (i == "next")
        {
            break;
        }
        else if (i == "board")
        {
            board->display();
        }
        else if (i == "status")
        {
            status();
        }
        else if (i == "residences")
        {
            cout << colour2Str(currentBuilder->getColour()) << "has built:" << endl;
            for (auto r : currentBuilder->getResList())
            {
                cout << r.first << " " << residence2Str(r.second) << endl;
            }
        }
        else if (i == "build-road")
        {
            cout << "> ";
            int i;
            cin >> i;
            if (cin.eof())
            {
                throw true;
            }
            else if (cin)
            {
                buildRoad(i, currentBuilder);
            }
            else
            {
                cin.clear();
                cin.ignore();
            }
        }
        else if (i == "build-res")
        {
            int i;
            cin >> i;
            if (cin.eof())
            {
                throw true;
            }
            else if (cin)
            {
                buildRes(i, currentBuilder);
            }
            else
            {
                cin.clear();
                cin.ignore();
            }
        }
        else if (i == "improve")
        {
            int i;
            cin >> i;
            if (cin.eof())
            {
                throw true;
            }
            else if (cin)
            {
                improveRes(i, currentBuilder);
            }
            else
            {
                cin.clear();
                cin.ignore();
            }
        }
        else if (i == "trade")
        {
            vector<string> args;
            string arg;
            while (true)
            { // loop to ensure we get 3 elements
                cin >> arg;
                if (cin.eof())
                {
                    throw true;
                }
                args.emplace_back(arg);
                if (args.size() == 3)
                {
                    break;
                }
            }

            // check each arg is valid
            bool validColour = false;
            // check colour
            for (auto builder : builderList)
            {
                if (builder != currentBuilder && conv2Colour(args.at(0)) == builder->getColour())
                {
                    validColour = true;
                    break;
                }
            }

            // loop enum class
            // check valid resources
            bool validResource1 = false;
            bool validResource2 = false;
            Inventory inv = currentBuilder->getInventory();
            for (auto resourcePair : inv.curInv)
            {
                if (conv2Resource(args.at(1)) == resourcePair.first)
                {
                    validResource1 = true;
                }
                if (conv2Resource(args.at(2)) == resourcePair.first)
                {
                    validResource2 = true;
                }
            }

            if (validColour && validResource1 && validResource2)
            {
                trade(args.at(0), args.at(1), args.at(2));
            }
            else
            {
                cout << "Invalid Trade." << endl;
            }
        }
        else if (i == "save")
        {
            string fileName;
            cin >> fileName;
            if (cin.eof())
            {
                throw true;
            }
            save(fileName);
        }
        else if (i == "help")
        {
            cout << "Valid commands:" << endl;
            cout << "board" << endl;
            cout << "status" << endl;
            cout << "residences" << endl;
            cout << "build-road <edge#>" << endl;
            cout << "build-res <housing#>" << endl;
            cout << "trade <colour> <give> <take>" << endl;
            cout << "next" << endl;
            cout << "save <file>" << endl;
            cout << "help" << endl;
        }
        else
        {
            cout << "Invalid Command." << endl;
        }
    }
    nextPlayer();
}

void Catan::distribute(const int tile)
{
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^    Aiden Begin    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    bool gain = false;
    board->updateResOnTile(tile);
    for (auto b : builderList)
    {
        if (b->afterDistribute())
        {
            gain = true;
        }
    }
    if (!gain)
    {
        cout << "No builders gained resoruces." << endl;
    }
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^    Aiden End    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}

string Catan::loadGameState(const string fileName)
{
    ifstream inFile;
    inFile.open(fileName);
    // current turn
    int curTurn;
    string input;
    getline(inFile, input);
    istringstream ss{input};
    ss >> curTurn;
    activeBuilderIndex = curTurn;

    vector<string> builderInfo;
    for (int i = 0; i < 4; ++i)
    {
        getline(inFile, input);
        builderInfo.emplace_back(input);
    }

    // Board
    getline(inFile, input);
    board = new Board();
    string boardLayout = input;
    board->load(input);

    // Builder
    for (size_t i = 0; i < builderInfo.size(); ++i)
    {
        int brick;
        int energy;
        int glass;
        int heat;
        int wifi;
        Inventory &builderInv = builderList[i]->getInventory();
        istringstream line{builderInfo[i]};
        char c;
        line >> brick;
        builderInv.curInv[Resource::BRICK] = brick;
        line >> energy;
        builderInv.curInv[Resource::ENERGY] = energy;
        line >> glass;
        builderInv.curInv[Resource::GLASS] = glass;
        line >> heat;
        builderInv.curInv[Resource::HEAT] = heat;
        line >> wifi;
        builderInv.curInv[Resource::WIFI] = wifi;
        builderInv.reconcile();
        line >> c;
        int road;
        vector<int> roadList;
        while (line >> road)
        {
            roadList.push_back(road);
        }
        builderList[i]->setRoadList(roadList);

        for (auto r : roadList)
        {
            board->getEdgeList()[r].setColour(builderList[i]->getColour());
        }

        line.clear();
        line.ignore();
        int resLocation;
        char resType;
        map<int, Residence> resList;
        while (line >> resLocation)
        {
            line >> resType;
            if (resType == 'B')
            {
                resList.insert({resLocation, Residence::B});
                board->getVertexList()[resLocation].setRes(Residence::B);
                builderList[i]->updatePoint(1);
            }
            else if (resType == 'H')
            {
                resList.insert({resLocation, Residence::H});
                board->getVertexList()[resLocation].setRes(Residence::H);
                builderList[i]->updatePoint(2);
            }
            else /* (resType == 'T') */
            {
                resList.insert({resLocation, Residence::T});
                board->getVertexList()[resLocation].setRes(Residence::T);
                builderList[i]->updatePoint(3);
            }
            board->getVertexList()[resLocation].setBuilder(builderList[i]);
            board->getVertexList()[resLocation].setColour(builderList[i]->getColour());
        }
        builderList[i]->setResList(resList);
    }

    // Geese
    int tileNum;
    getline(inFile, input);
    istringstream ss1{input};
    ss1 >> tileNum;
    Geese g;
    g.setTileNumber(tileNum);
    board->setGeese(g);

    return boardLayout;
}

string Catan::loadBoardOnly(const string fileName)
{
    delete board;
    board = new Board();
    string layout = board->loadFromFile(fileName);
    for (auto tile : board->getTileList())
    {
        if (tile.getResourceType() == Resource::PARK)
        {
            Geese g;
            g.setTileNumber(tile.getNum());
            board->setGeese(g);
        }
    }
    return layout;
}

void Catan::loadBoardOnlyFromStr(const string layoutStr)
{
    delete board;
    board = new Board();
    board->load(layoutStr);
    for (auto tile : board->getTileList())
    {
        if (tile.getResourceType() == Resource::PARK)
        {
            Geese g;
            g.setTileNumber(tile.getNum());
            board->setGeese(g);
        }
    }
}

string Catan::loadRandom()
{
    delete board;
    board = new Board;
    string layout = board->loadRandomBoard();
    for (auto tile : board->getTileList())
    {
        if (tile.getResourceType() == Resource::PARK)
        {
            Geese g;
            g.setTileNumber(tile.getNum());
            board->setGeese(g);
        }
    }
    return layout;
}

void Catan::deduct(const int deductFactor, const int bound)
{

    for (auto builder : builderList)
    {
        Inventory &builderInv = builder->getInventory();
        int invTotal = builderInv.totalInvCount();
        if (invTotal >= bound)
        {
            // deduct by factor
            int totalResourceLost = invTotal / deductFactor;

            map<Resource, int> deductCount = builderInv.curInv;
            vector<Resource> allResourceTypes;
            // set all deductCount map to 0, this will act as a counter for each Resource
            for (auto &resourcePair : deductCount)
            {
                allResourceTypes.emplace_back(resourcePair.first);
                resourcePair.second = 0;
            }

            for (int i = 0; i < totalResourceLost; ++i)
            {
                shuffle(allResourceTypes.begin(), allResourceTypes.end(), std::default_random_engine(seed));

                Resource stealing = allResourceTypes.at(0);
                if (builderInv.curInv.at(stealing) > 0)
                {
                    builderInv.curInv.at(stealing) -= 1;
                    deductCount.at(stealing) += 1;
                }
                else
                {
                    // reshuffle
                    --i;
                }
            }

            cout << "Builder " << colour2Str(builder->getColour()) << " loses " << totalResourceLost << " resources to the geese. They lose:" << endl;

            for (auto resourcePair : deductCount)
            {
                if (resourcePair.second > 0)
                {
                    cout << resourcePair.second << " " << resource2Str(resourcePair.first) << endl;
                }
            }
            builderInv.reconcile();
        }
    }
}

Colour Catan::checkWinner() const
{
    for (auto builder : builderList)
    {
        if (builder->getPoint() >= 10)
        {
            return builder->getColour();
        }
    }
    return Colour::NoColour;
}

Catan::~Catan()
{
    delete board;
    for (auto builderPtr : builderList)
    {
        delete builderPtr;
    }
}

Catan::Catan() : board{nullptr}, activeBuilderIndex{0}
{
    // intialize 4 builders
    builderList.emplace_back(new Builder{Colour::Blue});
    builderList.emplace_back(new Builder{Colour::Red});
    builderList.emplace_back(new Builder{Colour::Orange});
    builderList.emplace_back(new Builder{Colour::Yellow});
}

void Catan::initialSetup()
{
    for (int i = 0; i < 2; ++i)
    {
        for (auto b : builderList)
        {
            board->colourVertex(0, b, true);
        }
    }
}
