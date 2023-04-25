#include "roboconfig.h"

void Indexer::pushsingle() {
      indexer1.set_value(true);
      pros::delay(95);
      indexer1.set_value(false);
      pros::delay(95);
}

void Indexer::pushtriple() {
      indexer2.set_value(true);
      pros::delay(150);
      indexer2.set_value(false);
      pros::delay(150);
}

void Indexer::singleDouble(){
  angler.set_value(true);
  indexer1.set_value(true);
  pros::delay(125);
  indexer1.set_value(false);
  pros::delay(125);
  angler.set_value(false);
  indexer2.set_value(true);
  pros::delay(150);
  indexer2.set_value(false);
  pros::delay(150);
}

bool anglerOn = false;
bool buttonRegistered_angler = false;

void Indexer::angle() {
  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
    if(!buttonRegistered_angler) {
      anglerOn = !anglerOn; 
      buttonRegistered_angler = true;
    }
  }
  else {
    buttonRegistered_angler = false;
  }
  angler.set_value(anglerOn);
  pros::lcd::print(4,"Angle");
}

void toggle(pros::controller_digital_e_t button, std::function<void()> function) {
  bool registered = false;
  if(master.get_digital(button)) {
    if(!registered) {
      registered = true;
      function();
    }
  }
  else {
    registered = false;
  }
}


void Indexer::selectShooter() {
  //SINGLE SHOT NO ANGLER
  toggle(pros::E_CONTROLLER_DIGITAL_L2, Indexer::pushsingle);

  //TRIPLE SHOT NO ANGLER
  toggle(pros::E_CONTROLLER_DIGITAL_L1, Indexer::pushtriple);
}

