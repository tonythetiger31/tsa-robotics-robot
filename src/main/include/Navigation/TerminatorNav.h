#ifndef TEAMTSA
#define TEAMTSA

#include "Nav.h"
#include "DriveTrain.h"
#include <vector>

class TerminatorNavControlSystem : public NavControlSystem {
public:
    TerminatorNavControlSystem();
    TerminatorNavControlSystem(float NewUnit);
private:
    bool Moving = true;

    frc2::Timer* MovementTimer;

    int RobotAngle = 0;
    int PathIndex = 0;

    NodePath* Path;

    bool turned = false;

public:
    void ForwardOneUnit(float units);
    //Amount is from -360 to 360
    void Turn(int Amount);
    DriveTrain* ControlledDriveTrain;

    void FollowPathTick();
    void FollowPath(NodePath* PathToFollow);
};

#endif