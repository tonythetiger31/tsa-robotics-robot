#include "LaunchTrain.h"
#include <iostream>

LaunchTrain::LaunchTrain(){
    RollerMotor = new frc::PWM(RollerMotorID);
    RollerMotor->SetSafetyEnabled(false);
    //We're fucking hardcoding this I am sick of the robot map being so big
    RollerMotor2 = new frc::PWMVictorSPX(RollerMotor2ID);
    RollerMotor3 = new frc::PWMVictorSPX(RollerMotor3ID);
    RollerMotor3->SetExpiration(10);
    RollerMotor2->SetExpiration(999);
   // RollerMotor->SetSpeed(1);
   //RollerMotor2->SetSpeed(.65);
    //We're hardcoding this to keep it less confusing
    //Vector1 = new frc::Talon(8);
}

void LaunchTrain::Rotate(bool right){
    RollerMotor3->SetSpeed(.3*right);
}