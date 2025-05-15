/*
Update Notes:
[ Aiden July 18 2:46 ] : ADDED ';' AFTER CLASS DEFINITION

Fix Requirement:


*/

#ifndef _DICE_H
#define _DICE_H
#include "enum.h"
class Dice {
    public:
        virtual int getNumber() const = 0;
        virtual ~Dice() = 0;
};

#endif
