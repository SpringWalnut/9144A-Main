#include "devices.h"  // Include the header file where the intake_sensor is declared

#include <cstdio>

#include "./lemlib/api.hpp"  // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "liblvgl/extra/layouts/flex/lv_flex.h"  // IWYU pragma:  keep
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/device.hpp"  // IWYU pragma:  keep
#include "pros/misc.h"      // IWYU pragma:  keep
#include "pros/motor_group.hpp"
#include "pros/motors.h"  // IWYU pragma:  keep
#include "pros/motors.hpp"
#include "pros/optical.hpp"  // IWYU pragma:  keep

namespace my_robot {

// Define motor groups and individual motors
pros::Rotation horizontal_encoder(7);
pros::Rotation vertical_encoder(-16);

pros::Motor intake(6,pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);  // First stage motor
pros::adi::DigitalOut mogo('A', false);                   // Mobile goal mechanism on port 'C'
pros::adi::DigitalOut doinker('B', false);                // Doinker mechanism on port 'D'
pros::adi::DigitalOut diddy('C', false);  
pros::Optical color_sort(11);

// Define wall stake motor
pros::Motor wallStake(-5, pros::v5::MotorGears::red, pros::v5::MotorUnits::degrees);  // Wall stake motor on port -1

// Define left and right motor groups for the drivetrain
pros::MotorGroup left_motors({-8, 9, -10}, pros::MotorGearset::blue);   // Left motors on ports -2, 3, -4
pros::MotorGroup right_motors({1, -2, 3}, pros::MotorGearset::blue);  // Right motors on ports 7, -9, 10

// Define the drivetrain
lemlib::Drivetrain drivetrain(&left_motors, &right_motors, 10.75, lemlib::Omniwheel::NEW_325, 400, 8);

// Define the inertial sensor
pros::Imu imu(20);  // Inertial sensor on port 16

// horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_2, -2.6);
// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, .5);
// Setup odometry sensors
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor

);

// Define PID controllers
lemlib::ControllerSettings lateral_controller(
    6.9,  // Proportional gain (kP)
    .05,  // Integral gain (kI)
    5.5,  // Derivative gain (kD)
    3,    // Anti windup
    .25,  // Small error range, in inches
    25,   // Small error range timeout, in milliseconds
    0,    // Large error range, in inches
    0,    // Large error range timeout, in milliseconds
    17    // Maximum acceleration (slew)
);

lemlib::ControllerSettings angular_controller(2.754, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              20.09, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// Create the chassis
lemlib::Chassis chassis(
    drivetrain,          // Drivetrain settings
    lateral_controller,  // Lateral PID settings
    angular_controller,  // Angular PID settings
    sensors              // Odometry sensors
);
}