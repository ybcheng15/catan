/*
Update Notes:
[ Frances July 18 20:54 ]: 1) add PARK to enum class Resource

[ Aiden July 22 4:22 ] : created enum.cc to include those helper functions to convert enum class <-> string
*/

#ifndef _ENUM_H
#define _ENUM_H
#include <string>

extern unsigned seed;

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^    Aiden Begin    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
enum class Resource
{
    BRICK,
    ENERGY,
    GLASS,
    HEAT,
    WIFI,
    PARK
};
enum class Residence
{
    NoRes,
    B,
    H,
    T
};
enum class Colour
{
    NoColour,
    Blue,
    Red,
    Orange,
    Yellow
};
enum class DiceType
{
    Fair,
    Loaded
};

// Helper Functions:
Resource conv2Resource(std::string);

Colour conv2Colour(std::string);

std::string colour2Str(Colour);

std::string resource2Str(Resource);

std::string residence2Str(Residence);

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^    Aiden End    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#endif
