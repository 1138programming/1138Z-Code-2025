/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       1138                                                      */
/*    Created:      9/23/2025, 4:18:53 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "constants.hpp"
#include "drivetrain.hpp"

using namespace vex;

// A global instance of competition
competition Competition;

controller baseController;
controller armsController;

motor intakeMotor(Constants::intakePort);
motor beltMotor(Constants::beltPort);
motor_group fullIntake(intakeMotor, beltMotor);

motor leftMotor(Constants::leftBasePort);
motor rightMotor(Constants::rightBasePort);
Drivetrain drivebase(&leftMotor, &rightMotor);

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
    // run intake motors 
    if (armsController.ButtonL1.pressing()) {
      fullIntake.spin(vex::forward, 100, vex::pct);
    }
    else if (armsController.ButtonR2.pressing()){
      fullIntake.spin(vex::forward, -100, vex::pct);
    }
    else {
      fullIntake.spin(vex::forward, 0, vex::pct);
    }

    drivebase.updateSplitArcade(baseController.Axis3.position(), baseController.Axis1.position()); 

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
