#include "roboconfig.h"


int Intake::roll() {
  int vel = 0;
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    vel = -intakevolt;
    }
  else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && !master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    vel = intakevolt;
  }
  else {
    vel = 0;
  }
  
  Intakemotor.move(vel);
  
  return 1;
}