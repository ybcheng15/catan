/*
Update Notes:
[ Aiden July 19 00:46 ] : Created all methods
*/

#include "edge.h"
using namespace std;

Edge::Edge(int num) : num{num} {}

vector<Vertex *> Edge::getVertices() const
{
    return twoVertices;
}

void Edge::setColour(Colour colour)
{
    this->colour = colour;
}

Colour Edge::getColour() const
{
    return colour;
}

void Edge::setVertex(Vertex *v) {
    twoVertices.emplace_back(v);
}
