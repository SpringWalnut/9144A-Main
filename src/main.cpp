#include "devices.h"
#include "includes.h"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"

using namespace my_robot;

void initialize() {
  pros::lcd::initialize();                          // Initialize brain screen
  chassis.calibrate();                              // Calibrate sensors
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);  // Set brake mode for chassis motors
  wallStake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);      // Set brake mode for wall stake motor

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
    {"Red Positive Elims\n", RedPositiveElims},
    {"Blue Negative Elims\n", BlueNegativeElims},
    {"Red Negative Elims\n", RedNegativeElims},
    
    
    
    
    {"Nothing\n", Nothing},
      {"PID Tuning\n", tuning},
      {"Red Solo Win Point\n", RedSWP},
      {"Blue Solo Win Point\n", BlueSWP},
      {"Red Negative\n", RedNegative},
      
      {"Blue Negative\n", BlueNegative},
      
      {"Blue Positive\n", BluePositive},
      {"Blue Positive Elims\n", BluePositiveElims},
      {"Red Positive\n", RedPositive},
      
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
    chassis.cancelAllMotions();
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
bool prevButtonLEFTState = false;
bool doinkerDown = false;
//const int POSITION_ONE = 220;
//const int POSITION_TWO = 160;
//const int MOTOR_SPEED = 100;
//int toggleState = POSITION_ONE;  // Change to integer to track position

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
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            mogo.set_value(true);
        }
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            mogo.set_value(false);
        }

        // Intake Code
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            intake.move(127);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            intake.move(-127);
        } else {
            intake.move(0);
        }

        // WallStake Code
        wallStake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

        
        
        // Button-Controlled WallStake Positions
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
            //toggleState = POSITION_ONE; // Reset toggleState to POSITION_ONE when button A is pressed
            wallStake.move_absolute(45.75, 127); // Move to 40 degrees
        } 
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
            //toggleState = POSITION_ONE; // Reset toggleState to POSITION_ONE when button B is pressed
            wallStake.move_absolute(0, 127); // Move to 0 degrees
        }

        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
            // Toggle between the two positions
            //toggleState = (toggleState == POSITION_ONE) ? POSITION_TWO : POSITION_ONE;  // Toggle position
            //wallStake.move_absolute(toggleState, MOTOR_SPEED);

            wallStake.move_absolute(75, 105);
            diddy.set_value(true);
            wallStake.move_absolute(220, 100);
        }
        
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            while (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
                wallStake.move(95);
            }
            wallStake.brake();
    
        }
        
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            while (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                wallStake.move(-95);
            }
            wallStake.brake();

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