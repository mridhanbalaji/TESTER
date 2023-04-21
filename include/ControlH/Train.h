#include "pros/motors.hpp"
class Train {
  public:
    //DRIVE HELPER FUNCTIONS
    static void setVel(double Right, double Left);
    static void setVolt(double Right, double Left);
    static void setStop(pros::motor_brake_mode_e mode);
    static double getRightVolt();
    static double getLeftVolt();

    //DRIVER CONTROL FUNCTIONS
    static void robotCentric();
};