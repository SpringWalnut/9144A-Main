#include "devices.h"
#include "main.h"  // IWYU pragma: keep
#include "subroutines.h"

using namespace my_robot;
bool red_side;
// AUTONOMOUS ROUTINES
void RedSWP() {
  red_side = true;
  doinker.set_value(false);
  const int forwardPower = 127;   // Forward motor power (0-127)
  const int reversePower = -127;  // Reverse motor power (0-127)
  const int reverseTimeMs = 300;  // Reverse duration in ms


  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
  chassis.setPose(0, 0, 0);

  // Start route
  chassis.moveToPose(-13.25, -28.5, 31, 1500,
                     {.forwards = false});  // Move to first mogo
  chassis.waitUntilDone();
  mogo.set_value(true);  // Clamp mogo
  pros::delay(250);
  intake.move(127);
  chassis.moveToPose(3, -26, 86.5, 1750);
  chassis.waitUntilDone();
  chassis.moveToPose(-25.25, -0.85, -90, 2500);
  chassis.waitUntilDone();
  mogo.set_value(false);
  //pros::Task stop(stopIntakeOnSecondPress);
  intake.move(127);
  chassis.moveToPose(-40, -6.85, -90, 1000);
  chassis.waitUntilDone();
  chassis.moveToPose(-61, -26, 27.3, 2200,
                     {.forwards = false});  // Move to second mogo
  chassis.waitUntilDone();
  mogo.set_value(true);
  pros::delay(250);
  intake.move(127);
  chassis.turnToHeading(-90, 500);
  chassis.waitUntilDone();
  chassis.moveToPose(-80, -26, -90, 1750);
  chassis.waitUntilDone();
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
  chassis.moveToPose(-45, -26, -270, 3000);
  chassis.waitUntilDone();
  intake.move(0);
}

void BlueSWP() {
  red_side = false;
  doinker.set_value(false);
  const int forwardPower = 127;   // Forward motor power (0-127)
  const int reversePower = -127;  // Reverse motor power (0-127)
  const int reverseTimeMs = 300;  // Reverse duration in ms


  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
  chassis.setPose(0, 0, 0);

  // Start route
  chassis.moveToPose(13.25, -28.5, 329, 1500,
                     {.forwards = false});  // Move to first mogo
  chassis.waitUntilDone();
  mogo.set_value(true);  // Clamp mogo
  pros::delay(250);
  intake.move(127);
  chassis.moveToPose(3, -26, 273.5, 1750);
  chassis.waitUntilDone();
  chassis.moveToPose(25.25, -0.85, 90, 2500);
  chassis.waitUntilDone();
  mogo.set_value(false);
  //pros::Task stop(stopIntakeOnSecondPress);
  intake.move(127);
  chassis.moveToPose(40, -6.85, 90, 1000);
  chassis.waitUntilDone();
  chassis.moveToPose(61, -26, 332.7, 2200,
                     {.forwards = false});  // Move to second mogo
  chassis.waitUntilDone();
  mogo.set_value(true);
  pros::delay(250);
  intake.move(127);
  chassis.turnToHeading(-90, 500);
  chassis.waitUntilDone();
  chassis.moveToPose(80, -26, 90, 1750);
  chassis.waitUntilDone();
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
  chassis.moveToPose(45, -26, 270, 3000);
  chassis.waitUntilDone();
  intake.move(0);
}

void RedNegative() {
  red_side = true;
  doinker.set_value(false);
  const int forwardPower = 600;   // Forward motor power (0-127)
  const int reversePower = -600;  // Reverse motor power (0-127)
  const int reverseTimeMs = 300;  // Reverse duration in ms


  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
  chassis.setPose(0, 0, 0);

  // Start route
  chassis.moveToPose(-11.5, -27.5, 36.33, 1750,
                     {.forwards = false});  // Move to first mogo
  chassis.waitUntilDone();
  mogo.set_value(true);  // Clamp mogo
  pros::delay(250);
  intake.move(600);
  chassis.moveToPose(9.37, -28.99, 88.44, 1750);
  chassis.waitUntilDone();
  chassis.moveToPose(11.53, -40, 177.66, 3000);
  chassis.waitUntilDone();
  chassis.moveToPose(9.20, -8.45, 177.66, 1500, {.forwards = false});
  chassis.waitUntilDone();
  chassis.turnToHeading(268, 500);
  chassis.waitUntilDone();
  //pros::Task top(intakeAutomation);
  chassis.moveToPose(44.15, -11.21, 268.1, 5000);
}

void BlueNegative(){

}     

void RedNegativeElims(){

}

void BlueNegativeElims(){

}

void BluePositive(){

}

void BluePositiveElims(){
  
}

void RedPositive(){
  
}

void RedPositiveElims(){
  
}

void Nothing(){
  
}

void tuning() {
  // set position to x:0, y:0, heading:0
  chassis.setPose(0, 0, 0);
  // turn to face heading 90 with a very long timeout
  chassis.turnToHeading(90, 100000);
}






void Skills() {
  red_side = true;
  doinker.set_value(false);
  const int forwardPower = 127;   // Forward motor power (0-127)
  const int reversePower = -127;  // Reverse motor power (0-127)
  const int reverseTimeMs = 300;  // Reverse duration in ms


  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
  chassis.setPose(0, 0, 0);

  // Start route
  chassis.moveToPoint(0, -1, 200);
  chassis.waitUntilDone();
  wallThings(250);
  pros::delay(250);
  chassis.moveToPose(-25, -13.15, 35, 2000, {.forwards = false});
  chassis.waitUntilDone();
  mogo.set_value(true);
  intake.move(127);
  chassis.moveToPose(-47.5, -37.5, 210, 2000, {.earlyExitRange = 3});
  chassis.waitUntilDone();
  chassis.moveToPose(-59.125, -59, 210, 1250);
  chassis.waitUntilDone();
  chassis.moveToPose(-48, -30.75, 0, 1500);
  chassis.waitUntilDone();
  chassis.moveToPose(-48, 2, 0, 1000);
  chassis.waitUntilDone();
  chassis.moveToPose(-59.125, -12.25, 220, 1500);
  chassis.waitUntilDone();
  chassis.moveToPose(-60.75, 1, 160, 1500, {.forwards = false});
  chassis.waitUntilDone();
  mogo.set_value(false);
  //pros::Task first(stopIntakeOnFirstPress);
  intake.move(127);
  chassis.moveToPose(-24.75, -34.2, 135, 1500);
  chassis.waitUntilDone();
  chassis.moveToPose(22.8, -11.25, 270, 1500, {.forwards = false});
  chassis.waitUntilDone();
  mogo.set_value(true);
  pros::delay(250);
  intake.move(127);
  chassis.moveToPose(-23.5, -33.5, 180, 1000);
  chassis.waitUntilDone();
  chassis.moveToPose(47.2, -34.75, 90, 750);
  chassis.waitUntilDone();
  chassis.moveToPose(46.8, -2.5, 0, 400);
  chassis.waitUntilDone();
  chassis.moveToPose(52.8, -10.5, 125, 300);
  chassis.waitUntilDone();
  chassis.moveToPose(62, 0, 205, 1500, {.forwards = false});
  chassis.waitUntilDone();
  mogo.set_value(false);
  wallThings(73);
  chassis.moveToPose(58.75, -58.5, 90, 2000);
  chassis.waitUntilDone();
  wallThings(320);
  pros::delay(2000);
  //first.remove();
  //first.resume();
  chassis.moveToPose(46.8, -83, 208, 1000);
  chassis.waitUntilDone();
  chassis.moveToPose(23.25, -117.5, 35, 3000, {.forwards = false});
  chassis.waitUntilDone();
  mogo.set_value(true);
  pros::delay(300);
  intake.move(127);
  chassis.moveToPose(47.2, -118, 90, 750);
  chassis.waitUntilDone();
  chassis.moveToPose(60, -123, 290, 1000, {.forwards = false});
  chassis.waitUntilDone();
  mogo.set_value(false);
  //first.remove();
  //first.resume();
  chassis.moveToPose(45.75, -104.25, 320, 1500);
  chassis.waitUntilDone();
  chassis.moveToPose(0, -105.75, 90, 2000, {.forwards = false});
  chassis.waitUntilDone();
  mogo.set_value(true);
  chassis.moveToPose(23, -82.25, 45, 1500);
  intake.move(127);
  chassis.waitUntilDone();
  chassis.moveToPose(3, -62, 320, 1500);
  chassis.waitUntilDone();
  chassis.moveToPose(-20, -80, 235, 500);
  chassis.waitUntilDone();
  chassis.moveToPose(-48, -82, 265, 500);
  chassis.waitUntilDone();
  chassis.moveToPose(-47.5, -106.25, 180, 1000);
  chassis.waitUntilDone();
  mogo.set_value(false);

  chassis.waitUntilDone();
  pros::delay(1000000);  // Capture focus in auto
}