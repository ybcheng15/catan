/*
Update Notes:
[ Yi Bo July 18 19:05 ] : added ; after class definition

[ Frances July 22 10:20 ] : 1) added save(fileName)

[ Yi Bo July 23 13:16 ] 1) added param data type for save()

Fix Requirement:


*/
#ifndef _GEESE_H
#define _GEESE_H

#include <string>

class Geese {
    int tileNumber;

    public:
        Geese();
        void moveGeese();
        void setTileNumber(const int tileNum);
        int getTileNumber() const;
        void save(const std::string fileName);
        ~Geese();
};

#endif
