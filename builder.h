/*
Update Notes:
[ Aiden July 18 2:46 ] : 1) Changed getInventory() and updatePoint(...) signature

[ Yi Bo July 18 19:07 ] : removed double #include "inventory.h"

[ Yi Bo July 21 18:07 ] : 1) added Dice *dice field
                          2) added swapDice();

[ Frances July 22 ] : 1) added save(fileName)
                      2) change std::vector<Edge> roadList; to std::vector<int> roadList;
                      3) added Builder(colour, brick, energy, glass, heat, wifi, resList, roadList)

[ Yi Bo July 23 13:21 ] 1) added const string param type for load() and save()

[ July 24 22:43 ] : 1) added setRoadList and setResList

Fix Requirement:
[ Aiden July 19 00:46 ] : 1) Changed inventory's type to a map instead

[ Aiden July 22 4:31 ] : added afterDistribute()

[ Frances July 22 10:20 ] : might not need getRoadList() anymore
                       
*/
#ifndef _BUILDER_H_
#define _BUILDER_H_
#include <map>
#include <vector>
#include <string>
#include "inventory.h"
#include "enum.h"
#include "dice.h"

class Vertex;
class Edge;
class Inventory;

class Builder
{
    Inventory inventory;
    int points;
    std::map<int, Residence> resList;
    std::vector<int> roadList;
    Colour colour;
    Dice *dice;

    // std::string colourToString(const Colour colour) const;
    std::string residenceToString(const Residence residence) const;

public:
    Builder(Colour colour);
    void updateRes(int i);
    void updateRoad(int i);
    void updateInventory(Resource, Residence);
    bool afterDistribute(); // print the update after the resources are distributed and return true 
                            //  if builder received any resources. Also write updates back to oldInv.
                            //  oldInv and curInv should be the same after the function call.
    Inventory &getInventory();
    int getPoint();
    Colour getColour();
    // std::vector<int> getRoadList();
    std::map<int, Residence> getResList();
    void setRoadList(std::vector<int> roadList);
    void setResList(std::map<int, Residence> resList);
    void updatePoint(int p);
    
    void swapDice(const DiceType type);
    int roll(); 

    void save(const std::string fileName);
    void printStatus() const;
    void printResList() const;
    ~Builder();
};

#endif
