/*
Update Notes:
[ Aiden July 18 2:46 ] : 1) REMOVED updateVertex() and updateRoad() which are redundant to colourVertex() and colourEdge();
                         2) Added ';' after class def
                         3) Changed colourVertex() and colourEdge() signature

[Yi Bo July 18 21:20] :  1) May change Geese to a Geese* for encapsulation puposes

[ Aiden July 19 00:46 ] : 1) Changed colourEdge() and findTile()'s return type from bool to void
                          2) Deleted const befreo int tileNum

[ Yi Bo July 19 15:43 ] 1) updated findTile(int) to return a Tile*

[ Frances July 19 16:35 ] : 1) Added getTileList()

[ Aiden July 19 22:10 ] : 1) removed findTile(); Changed to updateResOnTile()

[ Frances July 22 10:20 ] : 1) Added save(fileName)

[ Yi Bo July 23 16:37 ] 1) added loadWithLayout() load() loadRandomBoard()

[ Yi Bo July 24 13:54 ] 1) added loadFromFile() 
                        2) chanaged param of load() to layoutStr
                        3) added void setGeese(Geese geese);

[ Yi Bo July 24 23:25 ] 1) fixed loadWithLayout param error

*/
#ifndef _BOARD_H
#define _BOARD_H
#include "tile.h"
#include "vertex.h"
#include "edge.h"
#include "geese.h"
#include <vector>
#include <string>

class Board
{
    std::vector<Tile> tileList;
    std::vector<Vertex> vertexList;
    std::vector<Edge> edgeList;
    Geese geese;

    void loadWithLayout(std::vector<std::pair<Resource, int>> layoutVector);
    std::string checkResidence(int) const;
    std::string checkRoad(int) const;
    std::string checkResourceName(int) const;
    std::string checkResourceNum(int) const;
    void observerListInit();
    void verEdgInit();
    void verEdgInitHelper(int, int, int = 1);

public:
    Board();
    void updateResOnTile(int tileNum); // checks if the matching tile has geese on it. Send presents if not, otherwise does nothing.
    void display() const;
    Geese &getGeese();
    void setGeese(Geese geese);
    std::vector<Tile> getTileList() const;
    void colourVertex(int vertexNum, Builder *builder, bool start);
    void upgradeVertex(int vertexNum, Builder *builder);
    void colourEdge(int edgeNum, Builder *builder);
    void save(const std::string fileName);
    std::string loadFromFile(const std::string fileName);
    void load(std::string layoutStr);
    std::string loadRandomBoard();
    std::vector<Vertex> &getVertexList();
    std::vector<Edge> &getEdgeList();
    ~Board() = default;
};

#endif

