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

bool buttonX_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_X);
bool buttonA_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_A);
bool buttonB_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_B);
bool buttonY_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_Y);
bool buttonL2_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_L2);
bool buttonRegistered_shooter = false;




void Shooter::shoot(int X, int A, int B, int Y, int L2) {
  buttonX_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_X);
  buttonA_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_A);
  buttonB_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_B);
  buttonY_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_Y);
  buttonL2_pressed = master.get_digital( pros::E_CONTROLLER_DIGITAL_L2);
  
  if(buttonX_pressed && !buttonRegistered_shooter) {
    toggleShoot(X);
    buttonRegistered_shooter = true;
  }
  else if(buttonA_pressed && !buttonRegistered_shooter) {
    toggleShoot(A);
    buttonRegistered_shooter = true;
  }
  else if(buttonB_pressed && !buttonRegistered_shooter) {
    toggleShoot(B);
    buttonRegistered_shooter = true;
  }
  else if(buttonY_pressed && !buttonRegistered_shooter) {
    toggleShoot(Y);
    buttonRegistered_shooter = true;
  }
  else if(buttonL2_pressed && !buttonRegistered_shooter) {
    toggleShoot(L2);
    buttonRegistered_shooter = true;
  }
  else {
    buttonRegistered_shooter = false;
  }
    flywheel.set_velocity_custom_controller(shooterVel);
}