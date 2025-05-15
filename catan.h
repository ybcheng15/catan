/*
Update Notes:
[ Aiden July 18 2:46 ] : 1) REMOVED SEVERAL #INCLUDE THAT ARE ALREADY INCLUDED IN BUILDER.H;
                         2) ADDED USING NAMESPACE STD;
                         3) ADDED ';' AFTER CLASS DEF;
                         4) Changed buildRes() and buildRoad() signature
                         5) Changed board type from Board to Board *

[ Yi Bo July 18 19:00 ] : 1) Changed to Dice to Dice ptr
                          2) added some private fields to keep track of the current builder (will be used to conduct player actions such as steal, trade, build etc.)

[ Frances July 19 16:35 ] : 1) Changed save() to save(fileName);
                            2) Added private method getNextTurn();

[ Aiden July 19 22:10 ] : 1) added parameter to trade();

[ Yi Bo July 21 18:26 ] : 1) removed Dice *dice (moved to Builder)

[ Yi Bo July 21 23:46 ] : 1) added playTurn()

[ Frances July 22 10:20 ] : 1) change load() to load(fileName)

[ Yi Bo July 22 13:51 ] : 1) removed roll() and added distribute(int) as a private method
                          2) Changed checkWinner() return type from bool to Colour
                          3) added deduct()

[ Yi Bo July 23 13:21 ] 1) added const std::string param type for save()

Fix Requirement:
[ Aiden July 18 2:46 ] : Dice has pure virtual functions. Can't create Dice object directly. Suggestion: make dice a ptr to Dice for polymorphism purpose [solved]

*/

#ifndef _CATAN_H
#define _CATAN_H
#include "board.h"
#include "dice.h"
#include "enum.h"
#include <string>
#include <vector>

class Builder;

class Catan
{
    Board *board;
    std::vector<Builder *> builderList;
    size_t activeBuilderIndex;

    void distribute(const int tile);
    void deduct(const int deductFactor, const int bound);
    void nextPlayer();

public:
    Catan();
    std::string loadGameState(const std::string fileName); // Board is set here
    std::string loadBoardOnly(const std::string fileName);
    void loadBoardOnlyFromStr(const std::string layoutStr);
    std::string loadRandom();

    void swapDice(const DiceType type);
    void save(const std::string fileName = "backup.sv");

    void status() const;
    void trade(std::string colour, std::string give, std::string take);
    void steal();

    void buildRes(int vertexNum, Builder *builder);
    void improveRes(int vertexNum, Builder *builder);
    void buildRoad(int edgeNum, Builder *builder);

    void nextTurn();
    Colour checkWinner() const;

    void initialSetup();

    void playTurn();

    ~Catan();
};

#endif
