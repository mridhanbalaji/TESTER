#include "roboconfig.h"
bool buttonRegistered_indexer = false;
void Indexer::push() {
    indexer1.set_value(true);
    pros::delay(125);
    indexer1.set_value(false);
    pros::delay(125);
    
}

// void Indexer::rapidFire(){
//   int i = 3;
//   if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && !buttonRegistered_indexer) {
//     while(i!= 0) {
//       indexer1.set_value(true);
//       pros::delay(125);
//       indexer1.set_value(false);
//       pros::delay(125);
//       i-= 1;
//     }
//     buttonRegistered_indexer = true;
//     i = 3;
//     pros::lcd::print(1, "1");
//   }
//   else {
//     buttonRegistered_indexer = false;
//   }
// }

bool anglerOn = false;
bool buttonRegistered_angler = false;

void Indexer::angle() {
  if(master.get_digital(DIGITAL_UP) && !buttonRegistered_angler){
    anglerOn = !anglerOn; 
    buttonRegistered_angler = true;
  }
  else {
    buttonRegistered_angler = false;
  }
  angler.set_value(anglerOn);
}






/*
tipleshot 
RPM1
anglerOn False


Single anglerOn
RPM2
anglerOn True

Single no anglerOn
RPM3
Anger False

CHACK ANGLER STATE, and then co vert if needed
Change rpm

switch

case[1]{

}
If in triple and need to go to single then click once for single then controller rumble, then next time single is clicked shoot
*/


int tripleShot = 0;
int anglerShot = 1;
int noAnglerShot = 2;

bool singleShotOn = false;
bool tripleShotOn = false;

int shooterMode;;

bool checkAngler(){
  if (anglerOn){
      shooterMode = 2;
    }
    else {
      shooterMode = 3;
    }
}

void Indexer::selectShooter(){
  if (master.get_digital(DIGITAL_L1) && !buttonRegistered_indexer && !singleShotOn){
    buttonRegistered_indexer = true; 
    Indexer::push();
  }
  else if (singleShotOn){
    buttonRegistered_indexer = true; 
    tripleShotOn = true;
    singleShotOn = false;
    master.rumble(".");
    shooterMode = 1;
    angler.set_value(false);

  }
  else {
    buttonRegistered_indexer = false;
  }

  if (master.get_digital(DIGITAL_L2) && !buttonRegistered_indexer && !tripleShotOn){
    buttonRegistered_indexer = true;
    checkAngler();
    Indexer::push();
  }
  else if (tripleShotOn){
    buttonRegistered_indexer = true; 
    tripleShotOn = false;
    singleShotOn = true;
    master.rumble(".");
    checkAngler();
  }

  switch (shooterMode) {
    //triple
    case 1:
      flywheel.set_velocity_custom_controller(2900);
      anglerOn = false;
    break;

    //single Angler
    case 2:
      flywheel.set_velocity_custom_controller(1400);
      anglerOn = true;
    break;

    //single no angler
    case 3:
      flywheel.set_velocity_custom_controller(1300);
      anglerOn = false;
    break;
  }
}


/*
  toggle: triple/single
  toggle: anglerOn/noangler

  when switching from single to tri 
*/
