/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       rishinalem                                                */
/*    Created:      2/24/2024, 12:25:35 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;
motor LF = vex::motor(PORT13, vex::gearSetting::ratio6_1, false);
motor LB = vex::motor(PORT15, vex::gearSetting::ratio6_1, true);
motor_group left = motor_group(LF, LB);
motor_group right = motor_group(RF, RB);
motor_group all = motor_group(LF, LB, RF, RB);
motor RF = vex::motor(PORT20, vex::gearSetting::ratio6_1, true);
motor RB = vex::motor(PORT16, vex::gearSetting::ratio6_1, false);
vex::rotation rotationSensor = vex::rotation(PORT10);
int currentDegree = rotationSensor.position(degrees);
int targetDegree = 90;
motor Intake = vex::motor(PORT18, vex::gearSetting::ratio6_1, true);
motor Outtake = vex::motor(PORT11, vex::gearSetting::ratio36_1, true);
digital_out solenoid_right = digital_out(Brain.ThreeWirePort.H);
digital_out solenoid_left = digital_out(Brain.ThreeWirePort.G);


// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
// Define constants
const double WHEEL_DIAMETER = 4.125; // inches
const double WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * 3.14159265358979323846; // inches

// Autonomous function for the first use case
void autonomousCase1() {
    solenoid_right.set(true); // Toggle solenoid right

    // Move forward for approximately 24 inches
    double targetDistanceDegrees = (24.0 / WHEEL_CIRCUMFERENCE) * 360.0;

    // Move forward for a calculated duration (empirically determined)
    // Adjust the value as needed based on testing
    LF.spin(forward, 50, percent);
    LB.spin(forward, 50, percent);
    RF.spin(forward, 50, percent);
    RB.spin(forward, 50, percent);
    wait(2000, msec); // Adjust duration for desired distance
    LF.stop();
    LB.stop();
    RF.stop();
    RB.stop();
}

// Autonomous function for the second use case
void autonomousCase2() {
    solenoid_left.set(true); // Toggle solenoid left

    // Move forward for approximately 24 inches
    double targetDistanceDegrees = (24.0 / WHEEL_CIRCUMFERENCE) * 360.0;

    // Move forward for a calculated duration (empirically determined)
    // Adjust the value as needed based on testing
    LF.spin(forward, 50, percent);
    LB.spin(forward, 50, percent);
    RF.spin(forward, 50, percent);
    RB.spin(forward, 50, percent);
    wait(2000, msec); // Adjust duration for desired distance
    LF.stop();
    LB.stop();
    RF.stop();
    RB.stop();
}

// Autonomous function that selects the appropriate case based on user input
void autonomous() {
    // Check the value of a brain touch screen button to determine the case
    while (true) {
        if (Brain.Screen.pressing()) {
            // Get the touch coordinates
            int x = Brain.Screen.xPosition();
            int y = Brain.Screen.yPosition();

            // Check if the touch is within a specific area to trigger case 1
            if (Controller.Button/* Condition for case 1 */) {
                autonomousCase1(); // Execute case 1
            }
            // Check if the touch is within a specific area to trigger case 2
            else if (/* Condition for case 2 */) {
                autonomousCase2(); // Execute case 2
            }

            // Wait for release to avoid multiple detections for a single touch
            while (Brain.Screen.pressing()) {
                wait(20, msec);
            }
        }

        wait(20, msec);
    }
}
