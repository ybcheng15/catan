/*
Update Notes:
[ Aiden July 18 2:46 ] : 1) REMOVED SEVERAL #INCLUDE THAT ARE ALREADY INCLUDED IN BUILDER.H;
                         2) ADDED USING NAMESPACE STD;
                         3) CREATED updateRes(), getInventory(), updatePoint(...)

[ Yi Bo July 18 19:12 ] : 1) printStatus() operator+ between string and points, changed + to << instead

[ Aiden July 19 00:46 ] : 1) Created updateInventory(...)

[ Aiden July 19 22:10 ] : 1) updated printStatus() and updateInventory() due to field changes in Inventory struct.

[ Yi Bo July 21 18:07 ] : 1) added Builder() and ~Builder()
                          2) added swapDice() and roll()

[ Aiden July 22 2:07 ] : 1) added loadeddice.h and fairdice.h
                         2) added body of Builder()
                         3) added sstream header

[ Frances July 22 10:20 ] : 1) Created save(fileName)
                      2) Added include <fstream>
                      3) Created Builder(colour, brick, energy, glass, heat, wifi, resList, roadList)



Fix Requirement:
[ Aiden July 18 2:46 ] : printStatus() operator+ between string and points [solved]
[ Aiden July 19 00:46 ] : Better change inventory from a struct to map.

[ Aiden July 22:10 ] : if we use map in inventory, printStatus() can't be const with std::map::[]. Use std::map::at instead.

*/

#include <iostream>
#include <sstream>
#include <fstream>
#include "loadeddice.h"
#include "fairdice.h"

#include "builder.h"
using namespace std;

// public
Builder::Builder(Colour colour) : points{0}, colour{colour}, dice{new LoadedDice{}}
{
    inventory.curInv[Resource::BRICK] = 0;
    inventory.curInv[Resource::ENERGY] = 0;
    inventory.curInv[Resource::GLASS] = 0;
    inventory.curInv[Resource::HEAT] = 0;
    inventory.curInv[Resource::WIFI] = 0;
    inventory.reconcile();
}

Builder::~Builder() { delete dice; }

void Builder::setRoadList(vector<int> roadList) {
    this->roadList = roadList;
}

void Builder::setResList(map<int, Residence> resList) {
    this->resList = resList;
}

int Builder::getPoint() {
    return points;
}

void Builder::printStatus() const
{
    int brick = inventory.curInv.at(Resource::BRICK);
    int energy = inventory.curInv.at(Resource::ENERGY);
    int glass = inventory.curInv.at(Resource::GLASS);
    int heat = inventory.curInv.at(Resource::HEAT);
    int wifi = inventory.curInv.at(Resource::WIFI);

    cout << colour2Str(colour) << " has " << points << " building points, " << brick;
    cout << " brick, " << energy << " energy, " << glass << " glass, " << heat << " heat, and " << wifi << " WiFi." << endl;
}

void Builder::printResList() const
{
    cout << colour2Str(colour) << " has built:" << endl;
    for (auto res : resList)
    {
        cout << res.first << " " << residence2Str(res.second) << endl;
    }
}

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^    Aiden Begin    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void Builder::updateRes(int i)
{
    if (resList.find(i) == resList.end())
    {
        resList.insert(pair<int, Residence>(i, Residence::B));
    }
    else
    {
        if (resList[i] == Residence::B)
        {
            resList[i] = Residence::H;
        }
        else if (resList[i] == Residence::H)
        {
            resList[i] = Residence::T;
        }
        else
        {
        }
    }
}

Inventory &Builder::getInventory() { return inventory; }

void Builder::updatePoint(int p) { points += p; }

void Builder::updateRoad(int edgeNum)
{
    roadList.emplace_back(edgeNum);
}

void Builder::updateInventory(Resource resource, Residence residence)
{
    switch (resource)
    {
    case Resource::BRICK:
        inventory.curInv[Resource::BRICK] += static_cast<int>(residence);
        break;
    case Resource::ENERGY:
        inventory.curInv[Resource::ENERGY] += static_cast<int>(residence);
        break;
    case Resource::GLASS:
        inventory.curInv[Resource::GLASS] += static_cast<int>(residence);
        break;
    case Resource::HEAT:
        inventory.curInv[Resource::HEAT] += static_cast<int>(residence);
        break;
    case Resource::WIFI:
        inventory.curInv[Resource::WIFI] += static_cast<int>(residence);
        break;
    default : break;
    }
}

bool Builder::afterDistribute() {
    ostringstream oss{""};
    bool retVal = false;
    for (auto p : inventory.curInv) {
        if (p.second != inventory.oldInv[p.first]) {
            oss << resource2Str(p.first) << " " << p.second - inventory.oldInv[p.first] << "\n";
        }
    }
    if (oss.str() != "") {
        cout << "Builder " << colour2Str(colour) << " gained:" << endl;
        cout << oss.str();
        retVal = true;
    }
    inventory.reconcile();
    return retVal;
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^    Aiden End    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void Builder::swapDice(const DiceType type)
{
    switch (type)
    {
    case DiceType::Loaded:
        delete dice;
        dice = new LoadedDice{};
        break;
    case DiceType::Fair:
        delete dice;
        dice = new FairDice{};
        break;
    default:
        break;
    }
}

int Builder::roll()
{
    return dice->getNumber();
}

void Builder::save(const string fileName)
{
    ofstream outfile;
    outfile.open(fileName, std::ios_base::app);

    for (auto r : inventory.curInv) {
        outfile << r.second << " ";
    }
    
    outfile << "r ";
    for (size_t i = 0; i < roadList.size(); ++i)
    {
        outfile << to_string(roadList[i]) << " ";
    }

    outfile << "h";
    for (auto r : resList)
    {
        if (r.second != Residence::NoRes)
        {
            outfile << " " << r.first << " " << residence2Str(r.second);
        }
    }
    
    outfile << '\n';

}

Colour Builder::getColour() {
    return colour;
}

map<int, Residence> Builder::getResList() {
    return resList;
}
