#include "subroutines.h"
#include <sys/_intsup.h>

#include "devices.h"  // IWYU pragma:  keep
#include "main.h"     // IWYU pragma:  keep

namespace my_robot {

void handleMotorStall(pros::Motor &motor, int forwardPower, int reversePower, int reverseTimeMs) {
  const int stallThreshold = 2000;    // Adjust based on your motor's typical stalled current (in mA)
  const int stallCheckInterval = 50;  // Interval to check motor status (ms)
  const int stallDurationMs = 500;    // Duration the motor must be stalled before reacting (ms)

  int stallCounter = 0;

  while (true) {
    // Check motor current draw
    int currentDraw = motor.get_current_draw();

    if (currentDraw > stallThreshold) {
      // Increment stall counter if current exceeds threshold
      stallCounter += stallCheckInterval;

      // If the motor has been stalled for the set duration
      if (stallCounter >= stallDurationMs) {
        // Reverse the motor briefly
        motor.move(reversePower);
        pros::delay(reverseTimeMs);

        // Resume forward motion
        motor.move(forwardPower);
        stallCounter = 0;  // Reset stall counter
      }
    } else {
      // Reset stall counter if motor is not stalled
      stallCounter = 0;
    }

    pros::delay(stallCheckInterval);  // Wait before the next check
  }
}



#include "pros/llemu.hpp" // IWYU pragma: keep
#include "pros/rtos.hpp"

// Adjustable values
const int SECOND_STAGE_ROTATION = 450;  // Degrees to spin secondStage
const int DELAY_AFTER_STAGE = 300;      // Delay before resuming intake (ms)
const int INTAKE_SPEED = 600;           // Intake motor speed
const int POSITION_TOLERANCE = 5;       // Allowed error in degrees


// Add your function definitions here

void wallThings(int number) {
  wallStake.move_absolute(number, 127);
  while (!((wallStake.get_position() < (number + 7)) &&
           (wallStake.get_position() > (number - 7)))) {
    // Continue running this loop as long as the motor is not within +-5 units
    // of its goal
    pros::delay(2);
  }
  //calibrateWallStake();
}



// Function to detect and react to rings
void colorSort(int waitTimeMs, int stopTimeMs, bool red_side) {
  color_sort.set_led_pwm(100);  // Ensure the sensor LED is on

  while (true) {
    pros::c::optical_rgb_s_t color_data = color_sort.get_rgb();
    int detected_hue = color_sort.get_hue();

    bool blue_detected = (detected_hue > 180 && detected_hue < 260);
    bool red_detected = (detected_hue > 0 && detected_hue < 60);

    if ((red_side && blue_detected) || (!red_side && red_detected)) {
      // Stop the intake for the designated time
      pros::delay(waitTimeMs);
      intake.move_velocity(0);
      pros::delay(stopTimeMs);
      intake.move_velocity(-600);  // Resume intake
    }

    pros::delay(20);  // Reduce CPU usage
  }
}

}  // namespace my_robot