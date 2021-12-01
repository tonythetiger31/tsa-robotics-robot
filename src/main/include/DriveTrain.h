//! A subsystem that interfaces with the drivebase on the robot
#ifndef _DRIVETRAIN_HG_
#define _DRIVETRAIN_HG_

#include "Delegate.h"
#include "TERMINATORDRIVE.h"
#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include <frc/Commands/Subsystem.h>
#include <frc/WPILib.h>
#include <rev/CANSparkMax.h>
#include <frc/XboxController.h>
#include <frc/Joystick.h>
#include "Navigation/Nav.h"
#include <frc/Drive/DifferentialDrive.h>
#include "LaunchTrain.h"
#include "RobotMap.h"
//#include <frc/Commands/DriveWithJoystick.h>

class DriveTrain{ //: public frc::Subsystem {
 public:
	DriveTrain(NavControlSystem* NewNavSystem); //!< Class constructor
	void ControlPeriodic();
	void AutoPeriodic();
	void FollowObject();

	void SetMotorSpeed(float Speed); //Required by FollowObject() and the A* pathfinding system

	NavControlSystem* TerminatorNavigation;

	rev::CANSparkMax* FrontRightSparkMax;
	rev::CANSparkMax* FrontLeftSparkMax;
	rev::CANSparkMax* BackRightSparkMax;
	rev::CANSparkMax* BackLeftSparkMax;
	//rev::CANSparkMax *Motors[4] = {FrontRightSparkMax, FrontLeftSparkMax, BackRightSparkMax, BackLeftSparkMax};
	std::shared_ptr<NetworkTable> Limelight;

	TerminatorDrive* Drive;
	LaunchTrain* Launcher;
protected:
	frc::XboxController* BoomController;
	frc::Joystick* BoomJoystick;
};

#endif // _DRIVETRAIN_HG_