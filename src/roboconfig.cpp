#include "roboconfig.h"






// drivetrain motors
pros::Motor left_back_motor(16,pros::E_MOTOR_GEAR_600, true); // port 1, not reversed
pros::Motor left_front_motor(14,pros::E_MOTOR_GEAR_600, false); // port 2, not reversed
pros::Motor left_top_motor(15,pros::E_MOTOR_GEAR_600, true); // port 4, reversed
pros::Motor right_front_motor(13,pros::E_MOTOR_GEAR_600, true); // port 3, reversed
pros::Motor right_back_motor(12,pros::E_MOTOR_GEAR_600, false); // port 4, reversed.
pros::Motor right_top_motor(11,pros::E_MOTOR_GEAR_600, false); // port 4, reversed
 
// drivetrain motor groups
pros::MotorGroup left_side_motors({left_front_motor, left_back_motor, left_top_motor});
pros::MotorGroup right_side_motors({right_front_motor, right_back_motor, right_top_motor});
 
lemlib::Drivetrain_t drivetrain {
    &left_side_motors, // left drivetrain motors
    &right_side_motors, // right drivetrain motors
    13.9375, // track width
    3.25, // wheel diameter
    360 // wheel rpm
};
 
// left tracking wheel encoder
pros::ADIEncoder left_enc('G', 'H', true); // ports A and B, reversed
// back tracking wheel encoder
pros::ADIEncoder back_enc('E', 'F', false); // ports C and D, not reversed
 
// left tracking wheel
lemlib::TrackingWheel left_tracking_wheel(&left_enc, 2.75, -2.75); // 2.75" wheel diameter, -4.6" offset from tracking center
lemlib::TrackingWheel back_tracking_wheel(&back_enc, 2.75, -1); // 2.75" wheel diameter, 4.5" offset from tracking center
 
// inertial sensor
pros::Imu inertial_sensor(17); // port 2
 
// odometry struct
lemlib::OdomSensors_t sensors {
    &left_tracking_wheel, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    &back_tracking_wheel, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};
 
// forward/backward PID
lemlib::ChassisController_t lateralController {
    15, // kP
    20, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0.8// slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    5,
    25,// 12,
    // 85, // kP // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};
 
 
// create the chassis
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);



sylib::SpeedControllerInfo flywheelController(
    [](double rpm) {
      return std::pow(M_E, (-0.001 * rpm * 3600 / 3600 + 1)) + 3.065;
    },     // kV function
    10,    // kP
    0.001, // kI00097
    0,     // kD
    0,     // kH
    true,  // anti-windup enabled
    50,    // anti-windup range
    true,  // p controller bounds threshold enabled
    50,    // p controller bounds cutoff enabled
    0.01,  // kP2 for when over threshold
    50,    // range to target to apply max voltage
    false, // coast down enabled
    0,     // coast down theshhold
    1     // coast down constant
);

// Create a motor object on port 17, with a purple cart, set as reversed, and
// with motor_speed_controller as a custom velocity controller
sylib::Motor flywheel(1, 3600, true, flywheelController);


//ALL OTHER MOTORS
pros::Motor Intakemotor(10,pros::E_MOTOR_GEAR_600,true);

//ALL PNEUMATICS
pros::ADIDigitalOut indexer1 ('A');
pros::ADIDigitalOut expansion ('C');
pros::ADIDigitalOut expansionblocker('B');

pros::Controller master(pros::E_CONTROLLER_MASTER);

