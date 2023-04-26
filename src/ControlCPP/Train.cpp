#include "roboconfig.h"

//DRIVE HELPER FUNCTIONS
void Train::setVel(double Right, double Left){
  right_back_motor.move_velocity(Right);
  right_front_motor.move_velocity(Right);
  right_top_motor.move_velocity(Right);
  left_back_motor.move_velocity(Left);
  left_front_motor.move_velocity(Left);
  left_top_motor.move_velocity(Left);
}

void Train::setVolt(double Right, double Left){
  right_back_motor.move(Right);
  right_front_motor.move(Right);
  right_top_motor.move(Right);
  left_back_motor.move(Left);
  left_front_motor.move(Left);
  left_top_motor.move(Left);
}

void Train::setStop(pros::motor_brake_mode_e mode){
  right_back_motor.set_brake_mode(mode);
  right_front_motor.set_brake_mode(mode);
  right_top_motor.set_brake_mode(mode);
  left_back_motor.set_brake_mode(mode);
  left_front_motor.set_brake_mode(mode);
  left_top_motor.set_brake_mode(mode);
}

double Train::getRightVolt(){
  return (right_back_motor.get_voltage() + right_front_motor.get_voltage() + right_top_motor.get_voltage()) / 3.0;
}

double Train::getLeftVolt(){
  return (left_back_motor.get_voltage() + left_front_motor.get_voltage() + left_top_motor.get_voltage()) / 3.0;
}

//DRIVER CONTROL FUNCTIONS
double prevLeftPower = 0;
double prevRightPower = 0;

double maxVoltperTime = 8000000000;
double dt = 0.01;
double currentRightPower = 0;
double currentLeftPower = 0;

void Train::robotCentric(){
  int controllerY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int controllerX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

  //Deadzone
  if(abs(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) < 5) {controllerY = 0;}
  if(abs(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) < 5) {controllerX = 0;}

  double desiredLeftPower = controllerY - controllerX; desiredLeftPower = desiredLeftPower > 127 ? 127 : desiredLeftPower < -127 ? -127 : desiredLeftPower; //BOUNDING STATEMENT
  double desiredRightPower = controllerY + controllerX; desiredRightPower = desiredRightPower > 127 ? 127 : desiredRightPower < -127 ? -127 : desiredRightPower;

  currentLeftPower = desiredLeftPower;//CONVERTS mV TO POWER
  currentRightPower = desiredRightPower;

  double leftVoltperTime = (currentLeftPower - prevLeftPower ) / dt; leftVoltperTime = leftVoltperTime > maxVoltperTime ? maxVoltperTime : leftVoltperTime < -maxVoltperTime ? -maxVoltperTime : leftVoltperTime;
  double rightVoltperTime = (currentRightPower - prevRightPower) / dt; rightVoltperTime = rightVoltperTime > maxVoltperTime ? maxVoltperTime : rightVoltperTime < -maxVoltperTime ? -maxVoltperTime : rightVoltperTime;

  double leftPower = prevLeftPower + (leftVoltperTime * dt);
  double rightPower = prevRightPower + (rightVoltperTime * dt);

  prevLeftPower = getLeftVolt() / 100;
  prevRightPower = getRightVolt() / 100;
  
  setVolt(leftPower, rightPower);
  pros::lcd::print(7, "Right: %f", currentLeftPower);
  pros::lcd::print(8, "Left: %f", currentRightPower);
}