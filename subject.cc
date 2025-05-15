/*
Update Notes:

[ Aiden July 19 00:46 ] : 1) created subject.cc
                          2) implemented all public methods

[ Yi Bo July 19 14:02 ] : 1) added *this to ob->notify(); since our notify() takes parameter

[ Aiden July 22 4:19 ] : 1) removed *this from ob->notify() due to an update in observer.h
                         2) added the missing Subject:: scope to getObservers()
Fix Requirement:


*/

#include <vector>
#include "subject.h"
#include "observer.h"
#include <iostream>
using namespace std;

Subject::~Subject() {}

void Subject::notifyObservers()
{
    for (auto ob : observers)
    {
        ob->notify(*this);
    }
}

void Subject::attach(Observer *ob)
{
    observers.emplace_back(ob);
}

std::vector<Observer *> Subject::getObservers()
{
    return observers;
}
