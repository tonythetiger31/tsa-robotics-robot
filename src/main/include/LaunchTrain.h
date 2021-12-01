#include "RobotMap.h"
#include <frc/PWM.h>
#include <frc/PWMVictorSPX.h>

class LaunchTrain {
    const int RollerMotorID = 1;
    const int RollerMotor2ID = 6;

    frc::PWM* RollerMotor;
    frc::PWMVictorSPX* RollerMotor2;
    frc::PWMVictorSPX* RollerMotor3; const int RollerMotor3ID = 4;
    //frc::Talon* Vector1;
    public:
    LaunchTrain(); //Used to initiate motors
    void Rotate(bool right);
};