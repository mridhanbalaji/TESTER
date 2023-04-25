#include "roboconfig.h"

using namespace pros;


bool expansionOn = false;
bool buttonRegistered_pneumatic = false;
void Expansion::launch() {
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
      if(!buttonRegistered_pneumatic) {
        //HAPPENS ONCE BUTTON IS PRESSED
        expansionOn = !expansionOn;
        buttonRegistered_pneumatic = true;
        pros::lcd::print(4, "EXPAND!!!!!!");
      }
    }
    else {
      buttonRegistered_pneumatic = false;
    }
    expansion.set_value(expansionOn);
}

bool expansion_blockOn = false;
bool buttonRegistered_pneumatic2 = false;
void Expansion::launch_blocker() {
    if(master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
      if(!buttonRegistered_pneumatic2) {
        //HAPPENS ONCE BUTTON IS PRESSED
        expansion_blockOn = !expansion_blockOn;
        buttonRegistered_pneumatic2 = true;
        pros::lcd::print(4, "BLOCK!!!!!!");
      }
    }
    else {
      buttonRegistered_pneumatic2 = false;
    }
    expansionblocker.set_value(expansion_blockOn);
}