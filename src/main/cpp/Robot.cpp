// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
  //This was included a while back, not useful
  //MyPowerDistributionPanel = new frc::PowerDistributionPanel();
  //MyPowerDistributionPanel->ClearStickyFaults();

  //This was here before, so maybe it's useful? IDK.
  //frc::SmartDashboard::PutData(&m_aSubsystem);
  //What the heck is &m_aSubsystem? This gives an error...
  
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  
  std::cout << "1: RobotInit()";
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 * 
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
    if (!TestTrain){
      std::cout << "2: Drive Train constructed";
      TerminatorNavControlSystem* TestNavSystem = new TerminatorNavControlSystem(1.0);
      TestTrain = new DriveTrain(TestNavSystem);

    //Create custom path for robot to follow
    Node* Node1 = new Node(0, 0);
    Node* Node2 = new Node(3, 0);
    Node* Node3 = new Node(1, 0);

    NodePath* RobotPath = new NodePath();

    RobotPath->AddNode(Node1);
    RobotPath->AddNode(Node2);
    RobotPath->AddNode(Node3);

    TestNavSystem->ControlledDriveTrain = TestTrain;
    TestNavSystem->FollowPath(RobotPath);

    }
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  //if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  //} else {
    // Default Auto goes here
  //}
  TestTrain->AutoPeriodic();
}

void Robot::TeleopInit() {
    if (!TestTrain){
      std::cout << "2: Drive Train constructed";
      TerminatorNavControlSystem* TestNavSystem = new TerminatorNavControlSystem(1.0);
      TestTrain = new DriveTrain(TestNavSystem);
      TestNavSystem->ControlledDriveTrain = TestTrain;
    }
}

void Robot::TeleopPeriodic() {
    TestTrain->ControlPeriodic();
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {
  //if (!TestTrain){
    //TestTrain = new DriveTrain();
 // }
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
