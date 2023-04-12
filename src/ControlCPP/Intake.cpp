#include "roboconfig.h"


int Intake::roll() {
  int vel = 0;
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    vel = intakeVelocity;
    }
  else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && !master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    vel = -intakeVelocity;
  }
  else {
    vel = 0;
  }
  
  Intakemotor.move_velocity(6*vel);
  
  return 1;
}