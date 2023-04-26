#include "roboconfig.h"

#include "pros/misc.h"

// using namespace pros;

bool shooterOn = false;
int shooterVel = 0;


void Shooter::toggleShoot(int buttonVel) {
  shooterOn = !shooterOn;
  if(shooterOn)
    shooterVel = buttonVel;
  else
    shooterVel = 0;
}

void Shooter::changeShoot(int changeVel) {
  shooterOn = !shooterOn;
  if(shooterOn)
    shooterVel += changeVel;
}

bool buttonX_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_X);
bool buttonA_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_A);
bool buttonB_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_B);
bool buttonY_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_Y);
bool buttonL2_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_L2);
bool buttonRegistered_shooter = false;




void Shooter::shoot(int X, int A, int B, int Y) {
  buttonX_pressed = master.get_digital(pros::E_CONTROLLER_DIGITAL_X);
  buttonA_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_A);
  buttonB_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_B);
  buttonY_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_Y);

  
  if(buttonX_pressed) {
    if (!buttonRegistered_shooter){ 
      changeShoot(100);
      buttonRegistered_shooter = true;
    }
  }
  else if(buttonA_pressed) {
    if (!buttonRegistered_shooter){
      toggleShoot(A);
      buttonRegistered_shooter = true;
    }
  }
  else if(buttonB_pressed) {
    if (!buttonRegistered_shooter){
      changeShoot(-100);
      buttonRegistered_shooter = true;
    }
  }
  else if(buttonY_pressed) {
    if (!buttonRegistered_shooter){
      toggleShoot(Y);
      buttonRegistered_shooter = true;
    }
  }
  else {
    buttonRegistered_shooter = false;
  }
    flywheel.set_velocity_custom_controller(shooterVel);\
    master.print(1, 1, "Shooter RPM: %f", flywheel.get_velocity());
    master.print(2, 1, "Target RPM: %f", shooterVel);
}