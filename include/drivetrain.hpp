#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP

#include "vex.h"

class Drivetrain {
    private:
        vex::motor_group* leftMotors;
        vex::motor_group* rightMotors;
        const float splitDriveMult = 1.0;
        const float splitTurnMult = 0.6;

    public:
        Drivetrain(vex::motor_group* leftMotors, vex::motor_group* rightMotors) {
            this->leftMotors = leftMotors;
            this->rightMotors = rightMotors;
        }

        void updateSplitArcade(int leftStickPct, int rightStickPct) {
            leftStickPct = (int)((float)leftStickPct * splitDriveMult);
            rightStickPct = (int)((float)rightStickPct * splitTurnMult);

            this->leftMotors->spin(vex::forward, (leftStickPct + rightStickPct), vex::pct);

            this->rightMotors->spin(vex::forward, (leftStickPct - rightStickPct), vex::pct);
        }
        
        void setStoppingBrake() {
            this->leftMotors->setStopping(vex::brake);
            this->rightMotors->setStopping(vex::brake);
        }
};

#endif