/*
Update Notes:
[ Yi Bo July 18 20:08 ] : 1) Added ctor and dtor (following example from lecture)

[ Aiden July 19 00: 46 ] : 1) changed ctor to default

[ Yi Bo July 19 14:02 ] added std::vector<Observer *> getObservers();

[ July 25 0:48 ] 1) added getResourceType()

Fix Requirement:


*/
#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "enum.h"
class Observer;

class Subject
{
    std::vector<Observer *> observers;

public:
    Subject() = default;
    void notifyObservers();
    void attach(Observer *ob);
    std::vector<Observer *> getObservers();
    virtual Resource getResourceType() const = 0;
    virtual ~Subject() = 0;
};

#endif
