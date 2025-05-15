/*
Update Notes:
[ Aiden July 18 2:46 ] : 1) Added updateRes(...)

[ Aiden July 19 00:46 ] : created all public methods

[ Aiden July 19 22:10 ] : Fixed an bug in notfiy()

[ Aiden July 24 21:22 ] : 1) added setTile()

[ July 24 22:53 ] : 1) change param name in setColour()
                    2) change something in notify()

Fix Requirement:


*/
#include <vector>
#include "tile.h"
#include "vertex.h"
#include "builder.h"
#include <iostream>
using namespace std;


Vertex::Vertex(int num) : num{num}, colour{Colour::NoColour}, res{Residence::NoRes} {}

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^    Aiden Begin    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void Vertex::updateRes()
{
    if (res == Residence::NoRes)
    {
        res = Residence::B;
    }
    else if (res == Residence::B)
    {
        res = Residence::H;
    }
    else if (res == Residence::H)
    {
        res = Residence::T;
    }
    else
    {
    }
}

void Vertex::setColour(Colour colour)
{
    this->colour = colour;
}

void Vertex::setBuilder(Builder *b)
{
    this->builder = b;
}

vector<Edge *> Vertex::getAdjacentRoad()
{
    return adjacentRoad;
}

Colour Vertex::getColour() const
{
    return colour;
}

Residence Vertex::getResidence() const
{
    return res;
}

void Vertex::notify(Subject &whoFrom)
{
    if (colour == Colour::NoColour) // builder would be nullptr
    {
        return;
    }
    Resource resource = whoFrom.getResourceType();
    builder->updateInventory(resource, res);
}

void Vertex::setEdge(Edge *e) {
    adjacentRoad.emplace_back(e);
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^    Aiden End    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void Vertex::setRes(Residence res) {
    this->res = res;
}
