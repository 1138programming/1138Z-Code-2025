#ifndef DRIVETRAIN_HPP
#define DRIVETRAIN_HPP

#include "vex.h"
#include "constants.hpp"

class Drivetrain {
    private:
        vex::motor* leftMotor;
        vex::motor* rightMotor;

    public:
        Drivetrain(vex::motor* leftMotor, vex::motor* rightMotor) {
            this->leftMotor = leftMotor;
            this->rightMotor = rightMotor;
            
            this->leftMotor->setStopping(vex::brake);
            this->rightMotor->setStopping(vex::brake);
        }

        void updateSplitArcade(int leftStickPct, int rightStickPct) {
            leftStickPct = (int)((float)leftStickPct * Constants::splitDriveMult);
            rightStickPct = (int)((float)rightStickPct * Constants::splitTurnMult);

            this->leftMotor->spin(vex::forward, (leftStickPct + rightStickPct), vex::pct);
            this->rightMotor->spin(vex::forward, (leftStickPct - rightStickPct), vex::pct);
        }
};

#endif