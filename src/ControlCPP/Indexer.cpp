#include "roboconfig.h"
bool buttonRegistered_indexer = false;
void Indexer::push() {
  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && !buttonRegistered_indexer) {
    indexer1.set_value(true);
    pros::delay(125);
    indexer1.set_value(false);
    buttonRegistered_indexer = true;
    pros::lcd::print(2,"1");
  }
  else {
    buttonRegistered_indexer = false;
  }
}

void Indexer::RapidFire(){
  int i = 3;
  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && !buttonRegistered_indexer) {
    while(i!= 0){
      indexer1.set_value(true);
      pros::delay(125);
      indexer1.set_value(false);
      pros::delay(50);;
      i-= 1;
    }
    buttonRegistered_indexer = true;
    i = 3;
    pros::lcd::print(2,"3");
  }
  else {
    buttonRegistered_indexer = false;
  }
}
