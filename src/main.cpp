/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       1138                                                      */
/*    Created:      9/23/2025, 4:18:53 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "drivetrain.hpp"

using namespace vex;

// A global instance of competition
competition Competition;

controller controller1;

motor intakeMotor(PORT16, false);

motor armLeft(PORT20, true);
motor armRight(PORT10, false);
motor_group fullArm(armLeft, armRight);

motor frontLeftMotor(PORT14, true);
motor backLeftMotor(PORT18, false);
motor_group leftMotors(frontLeftMotor, backLeftMotor);

motor frontRightMotor(PORT15, true);
motor backRightMotor(PORT17, false);
motor_group rightMotors(frontRightMotor, backRightMotor);

Drivetrain drivebase(&leftMotors, &rightMotors);

//left forwardback right turning

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  intakeMotor.setStopping(vex::hold);
  fullArm.setStopping(vex::hold);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // run arm motors 
    if (controller1.ButtonR1.pressing()) {
      fullArm.spin(vex::forward, 100, vex::pct);
    }
    else if (controller1.ButtonR2.pressing()){
      fullArm.spin(vex::forward, -100, vex::pct);
    }
    else {
      fullArm.spin(vex::forward, 0, vex::pct);
    }

    // run intake motors
    if (controller1.ButtonL1.pressing()) {
      intakeMotor.spin(vex::forward, 100, vex::pct);
    }
    else if (controller1.ButtonL2.pressing()){
      intakeMotor.spin(vex::forward, -100, vex::pct);
    }
    else {
      intakeMotor.spin(vex::forward, 0, vex::pct);
    }

    drivebase.updateSplitArcade(controller1.Axis3.position(), controller1.Axis1.position()); 

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
