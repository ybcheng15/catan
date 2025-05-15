/*
Update Notes:
[ Frances July 18 20:54 ]: 1) change getState() to getResourceType
                     2) create getResourceNum()

[ Aiden July 19 00:46 ] :  1) removed dtor

[ Aiden July 19 22:10 ] : 1) added data field num and public method getNum()

[ Yi Bo July 24 12:55 ] : 1) changed ctor params

*/

#ifndef _TILE_H_
#define _TILE_H_
#include "subject.h"
#include "enum.h"
class Tile : public Subject
{
    int num;
    Resource resource;
    int value;

public:
    Tile(int num, Resource resource, int value);
    int getNum() const;
    Resource getResourceType() const override;
    int getResourceNum() const;
    void setState(Resource resource, int value);
};
#endif
