#include "main.h"

extern pros::Motor left_front_motor; // port 1, not reversed
extern pros::Motor left_back_motor; // port 2, not reversed
extern pros::Motor left_top_motor; // port 4, reversed
extern pros::Motor right_front_motor; // port 3, reversed
extern pros::Motor right_back_motor; // port 4, reversed
extern pros::Motor right_top_motor; // port 4, reversed
 
// drivetrain motor groups
extern pros::MotorGroup left_side_motors;
extern pros::MotorGroup right_side_motors;
 
extern lemlib::Drivetrain_t drivetrain;
 
// left tracking wheel encoder
extern pros::ADIEncoder left_enc;
// back tracking wheel encoder
extern pros::ADIEncoder back_enc;
 
// left tracking wheel
extern lemlib::TrackingWheel left_tracking_wheel;
extern lemlib::TrackingWheel back_tracking_wheel;
 
// inertial sensor
extern pros::Imu inertial_sensor;
 
// odometry struct
extern lemlib::OdomSensors_t sensors;
// forward/backward PID
extern lemlib::ChassisController_t lateralController;
 
// turning PID
extern lemlib::ChassisController_t angularController;
 
 
// create the chassis
extern lemlib::Chassis chassis;


extern sylib::SpeedControllerInfo flywheelController;

// Create a motor object on port 17, with a purple cart, set as reversed, and
// with motor_speed_controller as a custom velocity controller
extern sylib::Motor flywheel;

extern pros::Motor Intakemotor;

extern pros::Controller master;

extern pros::ADIDigitalOut indexer1;
extern pros::ADIDigitalOut expansion;
extern pros::ADIDigitalOut expansionblocker;