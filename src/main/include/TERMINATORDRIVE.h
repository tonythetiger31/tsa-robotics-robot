#include "Delegate.h"
#include <rev/CANSparkMax.h>
#include "RobotMap.h"
#include <math.h>

//Allows for simple use of the human-friendly to access the motor array
enum MotorID_1 {FrontLeft, FrontRight, BackLeft, BackRight};
template<MotorID_1 MotorID_2> struct MotorID {
    const int Motor = 0;
};
template<> struct MotorID<FrontLeft>{
    static const int Motor = 1;
};
template<> struct MotorID<FrontRight>{
    static const int Motor = 0;
};
template<> struct MotorID<BackLeft>{
    static const int Motor = 3;
};
template<> struct MotorID<BackRight>{
    static const int Motor = 2;
};

class TerminatorDrive { //: public Delegate<TerminatorDrive, void, int, int> {
    public:
    //FunctionType<TerminatorDrive, void, int, int>::Function Delegate;

    rev::CANSparkMax *SparkMaxes[4];
    TerminatorDrive(rev::CANSparkMax* SparkMaxes_Input1, rev::CANSparkMax* SparkMaxes_Input2, rev::CANSparkMax* SparkMaxes_Input3 ,rev::CANSparkMax* SparkMaxes_Input4); //Constructor

    void SetTurbo(bool Turbo);

    void SetMode(int NewMode); //Binds correct functions for sideways driving
    
    void ForceStop(); //Stops all motors
    void ForceStop(int WhichMotor);

    //protected:
    int Mode;
    void DriveStandard(double Speedx, double Speedy);
    void DriveSideways(double Speedx, double Speedy);
    void Rotate(double AngleDifference);

    private:
	float RobotSpeed = static_cast<float>(RobotMap::MaxSpeed);
};

