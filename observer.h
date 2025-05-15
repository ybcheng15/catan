/*
Update Notes:
[ July 25 0:22 ] : 1) added getColour()

*/

#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Subject;

class Observer
{
public:
    virtual void notify(Subject &whoFrom) = 0;
    virtual Colour getColour() const = 0;
    virtual ~Observer() = default;
};

#endif
