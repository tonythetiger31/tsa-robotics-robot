#ifndef SQUARE_H
#define SQUARE_H

#include <frc/timer.h>
#include "Node.h"

//Stores basic control systems required by the robot. Kept virtual so that they may 
//be implemented later with the system
class NavControlSystem{
    protected:
    NavControlSystem(float NewUnit);
    float Unit = 1;
    public:
    virtual void Turn(int Amount);
    virtual void ForwardOneUnit(float units);
    virtual void FollowPathTick();
    virtual void FollowPath(NodePath* PathToFollow);
};

#endif