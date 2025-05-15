/*
Update Notes:

[ Yi Bo July 21 15:52 ] Added public Dice

[ Aiden July 22 2:26 ] : added #include dice.h
Fix Requirement:
[ Aiden July 19 00:48 ] : Missing public Dice after class name
*/

#ifndef _FAIRDICE_H
#define _FAIRDICE_H
#include "dice.h"

class FairDice : public Dice {
    public:
        FairDice();
        int getNumber() const override;
};

#endif
