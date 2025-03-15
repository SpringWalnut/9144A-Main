#include "devices.h"
#include "main.h"  // IWYU pragma: keep
#include "pros/rtos.hpp"
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
  wallStake.move_absolute(45.25,127);
  intake.move(127);
  pros::delay(1000);
  wallStake.move_absolute(200,80);
  chassis.moveToPose(-5,-5, 0, 1000,{.forwards = false, .earlyExitRange = .2});
  

  

  chassis.waitUntilDone();

  chassis.waitUntilDone();

  chassis.waitUntilDone();

  chassis.waitUntilDone();

  chassis.waitUntilDone();

  chassis.waitUntilDone();

  chassis.waitUntilDone();

  chassis.waitUntilDone();

  chassis.waitUntilDone();

  chassis.waitUntilDone();

  chassis.waitUntilDone();

  chassis.waitUntilDone();

  chassis.waitUntilDone();
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
chassis.setPose(0,0,0);
red_side = true;
const int waitTime = 150;
const int stopTime = 500;
const int forwardPower = 127;   // Forward motor power (0-127)
const int reversePower = -127;  // Reverse motor power (0-127)
const int reversetimeMS = 300;


pros::Task motorTask([&](){
  handleMotorStall(intake, forwardPower, reversePower,reversetimeMS);
});
pros::Task cs([&]() {
  colorSort(waitTime, stopTime, red_side);
});


    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    chassis.moveToPoint(0,-9,600, {.forwards = false, .earlyExitRange = .2});
    chassis.turnToHeading(-22, 300);
    chassis.moveToPose(7.59,-34,-22, 1100, {.forwards = false, .earlyExitRange = .2});
    chassis.waitUntil(38);
    mogo.set_value(true);
    pros::delay(250);
    chassis.turnToHeading(135, 550);
    pros::delay(150);
    intake.move(-127);
    chassis.moveToPose(17.24,-39.7,131, 1100);
    chassis.moveToPose(36.28,-52,108.25, 1300);
    chassis.moveToPose(52.5,-49.5,89, 1400);
    chassis.moveToPose(23.31,-44.36,118, 1300,{.forwards = false, .earlyExitRange = .2});
    chassis.moveToPose(33.55,-36.84,45.32, 1200);
    chassis.moveToPose(26.5,-40.5,28, 1000,{.forwards = false, .earlyExitRange = .2});
    chassis.moveToPose(56.40,8.50,47.8, 3000);
    chassis.moveToPose(50,2.00,-90, 800,{.forwards = false, .earlyExitRange = .2});
    //chassis.moveToPose(-6,-9,-88.45, 3200);
  chassis.moveToPose(-2.54,-25,-75.70, 2600);



    //chassis.moveToPose(-64.55,-6,-85.16, 2600);
    //chassis.moveToPoint(0,-15,1000, {.forwards = false, .earlyExitRange = .2});
    //chassis.moveToPose(6.29, -30.2, -30.8, 1200, {.forwards = false, .earlyExitRange = .2});
    /*chassis.waitUntil(34);
    mogo.set_value(true);
    pros::delay(250);
    chassis.turnToHeading(135, 450);
    intake.move(-127);
    pros::delay(100);*/
    /*chassis.moveToPoint(18.24,-43.93, 1500);
    chassis.moveToPose(41.00, -46.86, 90 , 2000);
    chassis.moveToPoint(11.23,-36.50, 1000, {.forwards = false});
    chassis.moveToPose(28.9, -33.70, 47.45 , 1000);
    chassis.moveToPose(32.65, 5.86, 56.45 , 2000);
    chassis.moveToPose(45.13, 9.5, 83.35 , 1100);
    chassis.moveToPoint(36.35,8.8, 500);
    chassis.moveToPose(-2.05, -22.6, -80.25 , 3000);
*/







    chassis.waitUntilDone();
}

void BlueNegativeElims(){
  /*red_side = false;
  doinker.set_value(false);
  const int forwardPower = 127;   // Forward motor power (0-127)
  const int reversePower = -127;  // Reverse motor power (0-127)
  const int waitTime = 150;
  const int stopTime = 500;

pros::Task cs([&]() {
  colorSort(waitTime, stopTime, red_side);
});*/


  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
  chassis.setPose(0, 0, 0);
  const int forwardPower = 127;   // Forward motor power (0-127)
const int reversePower = -127;  // Reverse motor power (0-127)
const int reversetimeMS = 300;


pros::Task motorTask([&](){
  handleMotorStall(intake, forwardPower, reversePower,reversetimeMS);
});
  chassis.moveToPose(-7.43, -28.39, 34.5, 1300, {.forwards = false});
  chassis.waitUntil(38);
  mogo.set_value(true);
  pros::delay(250);
  chassis.turnToHeading(-135, 550);
  pros::delay(180);
  intake.move(-127);
  chassis.moveToPose(-25.72, -53.87, -115.08, 1500);
  chassis.moveToPose(-45.89, -56.52, -86.90, 1300);
  chassis.moveToPose(-18.13, -48.61, -118.52, 1000, {.forwards = false});
  chassis.turnToHeading(-57.8,500);
  chassis.moveToPose(-35.00, -40.85, -57.00, 1300);
  chassis.moveToPose(-30.9, -47.2, -47.25, 900, {.forwards = false});
  chassis.moveToPose(-52.27, 3.80, -36.2, 4000);
  chassis.moveToPose(-41.37, -11.85, -37.50, 900, {.forwards = false});
  chassis.turnToHeading(75,500);
  chassis.moveToPose(10.50, -8.61, 90, 500);
  intake.move(0);
  chassis.moveToPose(55.50, -8.61, 90, 5500);
  //chassis.moveToPose(-3.52, -9.60, 90, 1700);
  







}

void BluePositive(){

}

void BluePositiveElims(){
  
}

void RedPositive(){
  
}

void RedPositiveElims(){
  
    chassis.setPose(0,0,0);
    red_side = true;
    const int waitTime = 150;
    const int stopTime = 500;
    const int forwardPower = 127;   // Forward motor power (0-127)
    const int reversePower = -127;  // Reverse motor power (0-127)
    const int reversetimeMS = 300;
    
    
    pros::Task motorTask([&](){
      handleMotorStall(intake, forwardPower, reversePower,reversetimeMS);
    });
    pros::Task cs([&]() {
      colorSort(waitTime, stopTime, red_side);
    });
    chassis.moveToPose(-6.76, -26.21, 32.2, 1400, {.forwards = false});
    chassis.waitUntil(40);
    mogo.set_value(true);
    pros::delay(250);
    pros::delay(180);
    intake.move(-127);
    chassis.moveToPose(-31.59, -36.49, -112.2, 1600);
    
  
  
  
}

void Nothing(){
  chassis.setPose(0, 0, 0);
  chassis.cancelAllMotions();
  red_side = true;
  const int waitTime = 140;
  const int stopTime = 490;



  pros::Task cs([&]() {
    colorSort(waitTime, stopTime, red_side);
  });
  intake.move(-127);
}

void tuning() {
  
  chassis.setPose(0, 0, 0);
   
  chassis.turnToHeading(90, 100000);
}






void Skills() {
  red_side = true;
  doinker.set_value(false);
  const int forwardPower = 127;   // Forward motor power (0-127)
  const int reversePower = -127;  // Reverse motor power (0-127)
  const int reverseTimeMs = 300;  // Reverse duration in ms
  const int waitTime = 150;
  const int stopTime = 500;



  pros::Task cs([&]() {
    colorSort(waitTime, stopTime, red_side);
  });


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