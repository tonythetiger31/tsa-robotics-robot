#include "Navigation/TerminatorNav.h"
#include <iostream>
#include "RobotMap.h"

TerminatorNavControlSystem::TerminatorNavControlSystem() :
    NavControlSystem(1) { }

TerminatorNavControlSystem::TerminatorNavControlSystem (float NewUnit) : 
    NavControlSystem(NewUnit) {
    MovementTimer = new frc2::Timer();
}

void TerminatorNavControlSystem::ForwardOneUnit(float units){
    std::cout << "Forward One Unit" << std::endl;
    if (!Moving){
        ControlledDriveTrain->SetMotorSpeed(0);
        return;
    }
    if (!MovementTimer->Get()){
        MovementTimer->Start();
        std::cout << "Timer Starting" << std::endl;
    }
    else if (MovementTimer->Get().to<double>() >= RobotMap::TimeToGoOneFoot*units*Unit){
        MovementTimer->Stop();
        MovementTimer->Reset();
        //Moving = false;

        std::cout << "Timer done" << std::endl;
        turned = false;
        PathIndex++;
        return;
    }
    std::cout << "Timer Continuing" << std::endl;
    ControlledDriveTrain->SetMotorSpeed(.25);
}

void TerminatorNavControlSystem::Turn(int Amount){
     std::cout << "Forward One Unit" << std::endl;

    int AmountPositive = Amount;
    if (Amount < 0)
        AmountPositive*=-1;
    int Multiplier = AmountPositive/Amount;

    if (!Moving){
        ControlledDriveTrain->SetMotorSpeed(0);
        return;
    }
    if (!MovementTimer->Get()){
        MovementTimer->Start();
        std::cout << "Timer Starting" << std::endl;
    }
    else if (MovementTimer->Get().to<double>() >= (static_cast<float>(AmountPositive)/360)*RobotMap::TimeToGoOneFoot*16.1){
        MovementTimer->Stop();
        MovementTimer->Reset();
        //Moving = false;

        std::cout << "Timer done" << std::endl;
        RobotAngle += Amount;

        turned = true;
        return;
    }
    std::cout << "Timer Continuing" << std::endl;
    ControlledDriveTrain->Drive->Rotate(Multiplier*160*.25); 
}

void TerminatorNavControlSystem::FollowPathTick(){
    if (PathIndex >= Path->Path.size()) {
        Moving = false;
        ControlledDriveTrain->SetMotorSpeed(0);
        return;
    }

    if (!turned) {
        std::cout << "Turning Angle" << Path->Path[PathIndex]->Angle - RobotAngle << std::endl;
        Turn(Path->Path[PathIndex]->Angle - RobotAngle);
    }
    else {
        ForwardOneUnit(Path->Path[PathIndex]->Distance);
    }
    return;
}

void TerminatorNavControlSystem::FollowPath(NodePath* PathToFollow){
    Path = PathToFollow;
    PathIndex=1;
    Moving = true;
    return;
}