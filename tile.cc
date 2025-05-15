/*
Update Notes:
[ Aiden July 19 00:46 ] : 1) Created all public methods

[ Aiden July 19 22:10 ] : 1) Created getNum()
Fix Requirement:


*/

#include "tile.h"

Tile::Tile(int num, Resource resource, int value) : num{num}, resource{resource}, value{value} {}

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^    Aiden Begin    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
int Tile::getNum() const
{
    return num;
}

Resource Tile::getResourceType() const
{
    return resource;
}

int Tile::getResourceNum() const
{
    return value;
}

void Tile::setState(Resource resource, int value)
{
    this->resource = resource;
    this->value = value;
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^    Aiden End    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
