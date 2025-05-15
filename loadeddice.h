/*
Update Notes:
[ Yi Bo July 21 15:52 ] Added public Dice

[ Aiden July 22 2:27 ] Added #include "dice.h"

Fix Requirement:
[ Aiden July 19 00:48 ] : Missing public Dice after class name

*/

#ifndef LOADEDDICE_H
#define LOADEDDICE_H
#include "dice.h"

class LoadedDice : public Dice {
    public:
        LoadedDice();
        int getNumber() const override;
};

#endif
