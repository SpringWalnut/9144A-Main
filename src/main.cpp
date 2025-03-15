#include "includes.h"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"

using namespace my_robot;

void initialize() {
  pros::lcd::initialize();                          // Initialize brain screen
  chassis.calibrate();                              // Calibrate sensors
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);  // Set brake mode for chassis motors
  wallStake.set_brake_mode(MOTOR_BRAKE_HOLD);      // Set brake mode for wall stake motor

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
      {"PID Tuning\n", tuning},
      {"Red Solo Win Point\n", RedSWP},
      {"Blue Solo Win Point\n", BlueSWP},
      {"Red Negative\n", RedNegative},
      {"Red Negative Elims\n", RedNegativeElims},
      {"Blue Negative\n", BlueNegative},
      {"Blue Negative Elims\n", BlueNegativeElims},
      {"Blue Positive\n", BluePositive},
      {"Blue Positive Elims\n", BluePositiveElims},
      {"Red Positive\n", RedPositive},
      {"Red Positive Elims\n", RedPositiveElims},
      {"Nothing\n", Nothing},
      {"Skills\n", Skills},
      
  });

  ez::as::initialize();  // Initialize autonomous selector

  // Print position to brain screen
  pros::Task screen_task([&]() {
    while (true) {
      // Print robot location to the brain screen
      pros::lcd::print(2, "X: %f", chassis.getPose().x);          // X-coordinate
      pros::lcd::print(3, "Y: %f", chassis.getPose().y);          // Y-coordinate
      pros::lcd::print(4, "Theta: %f", chassis.getPose().theta);  // Heading
      pros::delay(20);                                            // Delay to save resources
    }
  });
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
 ez::as::auton_selector.selected_auton_call();  // Calls selected autonomous routine from autonomous selector
}

// OPERATOR CONTROL

void opcontrol() {
    pros::Controller master(pros::E_CONTROLLER_MASTER);

    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
bool prevButtonLEFTState = false;
bool doinkerDown = false;

    while (true) {
      if (!pros::competition::get_status() &&
          (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) &&
          master.get_digital(pros::E_CONTROLLER_DIGITAL_UP))) {
       autonomous();
      }

        // Get left Y and right X positions
        int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // Move the robot and set velocity
        chassis.arcade(leftY, (rightX * 0.95));

        // Mobile Goal Clamp
        if (master.get_digital(DIGITAL_L2)) {
            mogo.set_value(true);
        }
        if (master.get_digital(DIGITAL_L1)) {
            mogo.set_value(false);
        }

        // Intake Code
        if (master.get_digital(DIGITAL_R1)) {
            intake.move(-127);
        } else if (master.get_digital(DIGITAL_R2)) {
            intake.move(127);
        } else {
            intake.move(0);
        }

        // WallStake Code
        wallStake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

        // Button-Controlled WallStake Positions
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
            wallStake.move_absolute(372, 127); // Move to 170 degrees
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
            wallStake.move_absolute(1450, 127); // Move to 700 degrees
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
            wallStake.move_absolute(0, 127); // Move to 0 degrees
        }
        
        bool currentButtonLEFTState = master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
    if (currentButtonLEFTState && !prevButtonLEFTState) {
        doinkerDown = !doinkerDown; // Toggle the state
        doinker.set_value(doinkerDown); // Directly set the value
    }

    // Update the previous state after checking the button press
    prevButtonLEFTState = currentButtonLEFTState;

        // Delay to save resources
        pros::delay(25);
    }
}
