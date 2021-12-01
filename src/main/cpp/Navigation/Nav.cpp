#include "Navigation/Nav.h"

//This class only serves as a parent for the structure of terminator nav.
//Each function is virtual so that the blank functions may be overwritten there.
//This is necessary as to not cause an infinite loop of header requirements.

NavControlSystem::NavControlSystem(float NewUnit){
    Unit = NewUnit;
}

void NavControlSystem::Turn(int Amount){
    return;
}

void NavControlSystem::ForwardOneUnit(float units){
    return;
}

void NavControlSystem::FollowPathTick(){

    return;
}

void NavControlSystem::FollowPath(NodePath* PathToFollow){
    return;
}