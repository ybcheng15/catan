/*
Update Notes:
[ Aiden July 19 00:46 ] : 1) combined data members a and b to twoVertices
                          2) added getVertices()
                          3) added parameter Colour colour to setColour()
                          4) Changed ctor's paramter accordingly

[ Yi Bo July 24 23:25 ] 1) added ctor
]

Fix Requirement:


*/

#ifndef _EDGE_H_
#define _EDGE_H_

#include <vector>
#include "enum.h"
class Vertex;

class Edge
{
    int num;
    std::vector<Vertex *> twoVertices;
    Colour colour;

public:
    Edge(int num);
    //Edge(Colour colour = Colour::NoColour);
    std::vector<Vertex *> getVertices() const;
    void setColour(Colour colour);
    Colour getColour() const;
    void setVertex(Vertex *);
    ~Edge() = default;
};
#endif
