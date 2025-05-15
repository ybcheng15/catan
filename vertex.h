/*
Update Notes:
[ Aiden July 18 2:46 ] : 1) Added setBuilder(...)

[ Yi Bo July 18 19:57 ] : removed virtual keyword from notify()

[ Aiden July 19 00:46 ] : 1) removed roadTest() which has been implemented as a helper fn in board.cc

[ Aiden July 24 21:22 ] : 1) added setTile()

[ Yi Bo July 24 23:25 ] 1) added new ctor

[ July 25 0:22 ] : 1) change getCoulor() to override
                    2) change the param of notify


Fix Requirement:


*/

#ifndef _VERTEX_H_
#define _VERTEX_H_
#include <vector>
#include "observer.h"
#include "enum.h"
class Builder;
class Edge;
class Tile;
class Vertex : public Observer
{
    int num;
    Builder *builder;
    Colour colour;
    Residence res;
    std::vector<Edge *> adjacentRoad;

public:
    Vertex(int num);
    void setBuilder(Builder *b);
    std::vector<Edge *> getAdjacentRoad();
    Residence getResidence() const;
    void setColour(Colour colour);
    void setEdge(Edge *);
    void setRes(Residence res);
    void updateRes();
    Colour getColour() const override;
    void notify(Subject &whoFrom) override;
    ~Vertex() = default;
};
#endif
