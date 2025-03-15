#pragma once
#include <cstdio>

#include "./lemlib/api.hpp"  // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "liblvgl/extra/layouts/flex/lv_flex.h"  // IWYU pragma:  keep
#include "pros/adi.hpp"
#include "pros/device.hpp"  // IWYU pragma:  keep
#include "pros/misc.h"      // IWYU pragma:  keep
#include "pros/motor_group.hpp"
#include "pros/motors.h"  // IWYU pragma:  keep
#include "pros/motors.hpp"
#include "pros/optical.hpp"  // IWYU pragma:  keep
#include "pros/rotation.hpp"

namespace my_robot {

extern pros::Motor intake;
extern pros::adi::DigitalOut mogo;
extern pros::adi::DigitalOut doinker;
extern pros::Optical color_sort;
extern pros::Motor wallStake;

// left motors
extern pros::MotorGroup left_motors;
// right motors
extern pros::MotorGroup right_motors;
// drivetrain
extern lemlib::Drivetrain drivetrain;

// inertial
extern pros::Imu imu;
// create an optical shaft encoder connected to ports 'A' and 'B'
extern pros::Rotation vertical_encoder;
extern pros::Rotation horizontal_encoder;
// vertical tracking wheel
extern lemlib::TrackingWheel vertical_tracking_wheel;
extern lemlib::TrackingWheel horizontal_tracking_wheel;
// setup odom
extern lemlib::OdomSensors sensors;

// PIDs
// lateral PID controller
extern lemlib::ControllerSettings lateral_controller;

// angular PID controller
extern lemlib::ControllerSettings angular_controller;
// create the chassis
extern lemlib::Chassis chassis;

}  // namespace my_robot