#include "TERMINATORDRIVE.h"
#include <iostream>
//#include <algorithm>
#include <cmath>

//Add sparkmaxes to TerminatorDrive
TerminatorDrive::TerminatorDrive(rev::CANSparkMax* SparkMaxes_Input1, rev::CANSparkMax* SparkMaxes_Input2, rev::CANSparkMax* SparkMaxes_Input3 ,rev::CANSparkMax* SparkMaxes_Input4){
    SparkMaxes[0] = SparkMaxes_Input1;
    SparkMaxes[1] = SparkMaxes_Input2;
    SparkMaxes[2] = SparkMaxes_Input3;
    SparkMaxes[3] = SparkMaxes_Input4;
    std::cout << "4: TerminatorDrive::TerminatorDrive()";
}

void TerminatorDrive::SetTurbo(bool Turbo){
    if (Turbo){
        RobotSpeed = 1;
    }
    else{
        RobotSpeed = RobotMap::MaxSpeed;
    }
}

void TerminatorDrive::SetMode(int NewMode){
    //FIX
    //Currently just binds the standard drive functionality to the TerminatorDrive
    Mode = 0;
    //IAN. DO THIS. &CLASSNAME::FUNCTION NAME
    //Delegate = &TerminatorDrive::DriveStandard;

}

void TerminatorDrive::DriveStandard(double Speedx, double Speedy) {
    std::cout << "MOTORS WORKING";
    double FinalL;
    double FinalR;
    double Angle = std::sqrt(Speedx)/2 + Speedx/2;//(std::acos(Speedxa/std::sqrt(std::pow(Speedxa,2)+std::pow(Speedy,2)))/3.1416)-1;
    double r = std::sqrt(std::pow(Speedx,2)+std::pow(Speedy,2));
    double MaxSpeed = static_cast<double>(RobotSpeed);
    r = r/MaxSpeed;
    if (Speedy>0){
        r = -r;
    }

    
    double SpeedXDeadzone = (std::abs(Speedx) - (r*std::sin(Speedx/6.28))/2) * (std::abs(Speedx)/Speedx);

    double LeftMult;
    double RightMult;

    if (Speedx > 0){
        LeftMult = 1;
        RightMult = 2;
    }
    else{
        LeftMult = 2;
        RightMult = 1;
    }

    FinalL = r + LeftMult * (SpeedXDeadzone/MaxSpeed);
    FinalR = r - RightMult * (SpeedXDeadzone/MaxSpeed);

    /* Incase this is the cause of randomly going full speed; did not fix issue
    if (FinalL > 1)
        FinalL = 1;
    if (FinalL < -1)
        FinalL = -1;
    if (FinalR > 1)
        FinalR = 1;
    if (FinalR < -1)
        FinalR = -1;
        */

    SparkMaxes[MotorID<FrontLeft>::Motor]->Set(FinalL);
    SparkMaxes[MotorID<BackLeft>::Motor]->Set(FinalL);

    SparkMaxes[MotorID<FrontRight>::Motor]->Set(FinalR);
    SparkMaxes[MotorID<BackRight>::Motor]->Set(FinalR);
    /*
    (SparkMaxes+MotorID<BackRight>::Motor)->Set(1);
    for (int i = 0; i < 4; i++){
        if (SparkMaxes[i]){
        (SparkMaxes[i])->Set(1); //Set the speed. Something low for now so it doesn't break the wall
        }
    }
    */
}

void TerminatorDrive::DriveSideways(double Speedx, double Speedy) {

    double Speed = Speedy;
    if (Speedx > Speedy)
        Speed = -5*Speedx;

    SparkMaxes[MotorID<FrontLeft>::Motor]->Set(Speed);
    SparkMaxes[MotorID<BackLeft>::Motor]->Set(-Speed);

    SparkMaxes[MotorID<FrontRight>::Motor]->Set(-Speed);
    SparkMaxes[MotorID<BackRight>::Motor]->Set(Speed);
}

void TerminatorDrive::ForceStop(){
        SparkMaxes[MotorID<FrontLeft>::Motor]->StopMotor();
    SparkMaxes[MotorID<BackLeft>::Motor]->StopMotor();

    SparkMaxes[MotorID<FrontRight>::Motor]->StopMotor();
    SparkMaxes[MotorID<BackRight>::Motor]->StopMotor();
}
void TerminatorDrive::ForceStop(int WhichMotor){
    SparkMaxes[WhichMotor]->StopMotor();
}

void TerminatorDrive::Rotate(double AngleDifference){
    double Speed = (AngleDifference/160);

    SparkMaxes[MotorID<FrontLeft>::Motor]->Set(Speed);
    SparkMaxes[MotorID<BackLeft>::Motor]->Set(Speed);

    SparkMaxes[MotorID<FrontRight>::Motor]->Set(-Speed);
    SparkMaxes[MotorID<BackRight>::Motor]->Set(-Speed);
}

/*Spin mode
    std::cout << "MOTORS WORKING";
    double FinalL;
    double FinalR;
    double Angle = (std::acos(Speedx/std::sqrt(std::pow(Speedx,2)+std::pow(Speedy,2)))/3.1416)-1;
    double r = std::sqrt(std::pow(Speedx,2)+std::pow(Speedy,2));
    if (Speedy<0){
        r = -1*r;
    }

    //Determine direction, then adjust movement based on direction
    if(Speedx > 0){ //Further left you pull
        FinalL = r;
        FinalR = (Angle)*r;
    }
    else{
        FinalL = (-Angle)*r;
        FinalR = r;
    }

    SparkMaxes[MotorID<FrontLeft>::Motor]->Set(FinalL);
    SparkMaxes[MotorID<BackLeft>::Motor]->Set(FinalL);

    SparkMaxes[MotorID<FrontRight>::Motor]->Set(FinalR);
    SparkMaxes[MotorID<BackRight>::Motor]->Set(FinalR);
    */