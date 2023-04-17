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

//DRIVER CONTROL FUNCTIONS
double preRVEL = 0;
double preLVEL = 0;
double preRACCEL = 0;
double preLACCEL = 0;
const double dt = 0.000166667; //in mins
const double maxACCEL = 10;
const double maxJERK = 10;

void Train::robotCentric(){
  int controllerY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int controllerX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

  //Deadzone
  if(abs(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) < 5) {controllerY = 0;}
  if(abs(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) < 5) {controllerX = 0;}

  double LeftVel = -(controllerY + controllerX);
  double RightVel = -(controllerY - controllerX);


  double RVEL = 5* RightVel;
  double LVEL = 5* LeftVel;

  double RACCEL = (RVEL - preRVEL) / dt; RACCEL = abs(RACCEL) > maxACCEL ? maxACCEL : RACCEL;
  double LACCEL = (LVEL - preLVEL) / dt; LACCEL = abs(LACCEL) > maxACCEL ? maxACCEL : LACCEL;

  double RJERK = (RACCEL - preRACCEL) / dt; RJERK = abs(RJERK) > maxJERK ? maxJERK : RJERK;
  double LJERK = (LACCEL - preLACCEL) / dt; LJERK = abs(LJERK) > maxJERK ? maxJERK : LJERK;

  double RACCEL_limited = (RJERK * dt) + preRACCEL;
  double LACCEL_limited = (LJERK * dt) + preLACCEL;

  double RVEL_limited = (RACCEL * dt) + preRVEL;
  double LVEL_limited = (LACCEL * dt) + preLVEL;
  
  preRVEL = RVEL;
  preLVEL = LVEL;
  
  preRACCEL = RACCEL;
  preLACCEL = LACCEL;

  if (RVEL > 600) {
		RVEL = 600;
	} 
  else if (RVEL < -600){ 
      RVEL = -600;
  }

  if (LVEL > 600) {
		LVEL = 600;
	} 
  else if (LVEL < -600){
    LVEL = -600;
  }

  

  if (RVEL > PREVEL){
    pros::lcd::print(2,"%d",PREVEL);
  }
  
  setVolt(RVEL, LVEL);
}