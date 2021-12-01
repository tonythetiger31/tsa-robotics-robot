#include "DriveTrain.h"
//#include "DriveWithJoystick.h"
//#include <rev/CANSparkMaxLowLevel.h>
#include "CANBoomMax.h"
#include "Navigation/Nav.h"
#include <iostream>

DriveTrain::DriveTrain(NavControlSystem* NewNavSystem) { //: frc::Subsystem("DriveTrain") {
	FrontRightSparkMax = new BoomMax(RobotMap::FrontRightSparkMaxID, false);
	FrontLeftSparkMax  = new BoomMax(RobotMap::FrontLeftSparkMaxID, true);
	BackRightSparkMax  = new BoomMax(RobotMap::BackRightSparkMaxID, false);
	BackLeftSparkMax   = new BoomMax(RobotMap::BackLeftSparkMaxID, true);
	//Should work without this, but I'm at a loss.
	//rev::CANSparkMax* Motors[4] = {FrontRightSparkMax, FrontLeftSparkMax, BackRightSparkMax, BackLeftSparkMax};
	Drive = new TerminatorDrive(FrontRightSparkMax, FrontLeftSparkMax, BackRightSparkMax, BackLeftSparkMax);
	Launcher = new LaunchTrain();
	BoomController = new frc::XboxController(RobotMap::XBoxControllerDrivePort);
	BoomJoystick = new frc::Joystick(RobotMap::XBoxControllerDrivePort);

	Limelight = nt::NetworkTableInstance::GetDefault().GetTable("limelight"); //init limelight for autonomous controls

	TerminatorNavigation = NewNavSystem;

	//BackRightSparkMax->Set(1);

	//Drive->SetMode(0);
	//Drive->DriveStandard(1,1);
	std::cout << "go";
	std::cout << "3: Drivetrain::DriveTrain()";
}

void DriveTrain::AutoPeriodic(){
	std::cout << "Auto Periodic  ";
	//FollowObject();
	TerminatorNavigation->FollowPathTick();
}

void DriveTrain::ControlPeriodic(){
	if (BoomController->GetAButtonPressed())
		Drive->SetTurbo(true);
	if (BoomController->GetAButtonReleased())
		Drive->SetTurbo(false);

	if(BoomController->GetStartButton()){
		Drive->ForceStop();
		return;
	}

	if (BoomController->GetTriggerAxis(frc::XboxController::kLeftHand) || BoomController->GetTriggerAxis(frc::XboxController::kRightHand)){
		Drive->DriveSideways(BoomController->GetTriggerAxis(frc::XboxController::kLeftHand), BoomController->GetTriggerAxis(frc::XboxController::kRightHand));
	}
	else{
		std::cout << "Controller: " << BoomController->GetX(frc::XboxController::kLeftHand);
		if (BoomJoystick->GetX(frc::Joystick::kLeftHand) && BoomJoystick->GetY(frc::Joystick::kLeftHand)){
			Drive->DriveStandard(BoomJoystick->GetX(frc::Joystick::kLeftHand), BoomJoystick->GetY(frc::Joystick::kLeftHand));
		}		
	}
	//Welp, abandoning this system entirely. OR NOT!
	if (BoomJoystick->GetX(frc::Joystick::kRightHand)){
		if (BoomJoystick->GetX(frc::Joystick::kRightHand) > 0)
			Launcher->Rotate(true);
		else
			Launcher->Rotate(false);
	}
}

void DriveTrain::FollowObject(){
		if (Limelight->GetNumber("tv", 0.0)){
		if (Limelight->GetNumber("tx", 0.0) > 10){
			Drive->Rotate(Limelight->GetNumber("tx", 0.0));
		}
		else if (Limelight->GetNumber("tx", 0.0) < -10 ){
			Drive->Rotate(Limelight->GetNumber("tx", 0.0));
		}
		else if (Limelight->GetNumber("ta", 0.0) < 15) {
			SetMotorSpeed(.2-(Limelight->GetNumber("ta", 0.0)*.002));
		}
	}
}

void DriveTrain::SetMotorSpeed(float Speed){

	for(int i = 0; i <= 3; i++){
		Drive->SparkMaxes[i]->Set(static_cast<double>(Speed));
	}

}