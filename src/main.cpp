#include "roboconfig.h"

//mactest

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}


void screen() {
    // loop forever
    while (true) {
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(3, "x: %f", pose.x); // print the x position
        pros::lcd::print(4, "y: %f", pose.y); // print the y position
        pros::lcd::print(5, "heading: %f", pose.theta); // print the heading
        pros::delay(10);
    }
}



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	pros::lcd::register_btn1_cb(on_center_button);
	chassis.calibrate();
	chassis.setPose(12, -59, 46.75);
	pros::Task screenTask(screen);
	sylib::initialize();
}
//15.1 -57.5 0 `
// Next angled coordiate ( mupp is  a monkey)
// 14.56 -60.16 46.75
/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	flywheel.set_velocity_custom_controller(2260);
	Intake::fwdspin();
	chassis.follow("path-18.txt", 1500,10);
	pros::delay(350);
	Intake::intstop();
	Train::setVolt(-120,-90);
	pros::delay(200);
	Train::setVel(0,0);
	chassis.turnTo(54,48,2000,true);
	Indexer::pushsingle();
	pros::delay(220);
	Indexer::pushsingle();
	pros::delay(220);
	Indexer::pushsingle();
	pros::delay(200);
	Indexer::pushtriple();
	chassis.turnTo(25,-57,1500,false);
	chassis.moveTo(25,-57,5000);
	Train::setVolt(-127,127);
	pros::delay(40);
	Train::setVolt(0,0);
	Intake::revspin();
	Train::setVolt(127,127);
	pros::delay(450);
	Train::setVolt(-127,-127);
	pros::delay(50);
	Train::setVolt(0,0);
	flywheel.set_velocity_custom_controller(2175);
	chassis.turnTo(18,-43,5000,true);
	chassis.moveTo(18,-43,5000);
	Intake::fwdspin();
	chassis.turnTo(0,-24,5000);
	chassis.follow("path-24.txt",10000,10);
	chassis.turnTo(58,47,3000,true);
	pros::delay(550);
	indexer2.set_value(true);
	pros::delay(60);
	indexer2.set_value(false);
	pros::delay(50);
	indexer2.set_value(true);
	pros::delay(60);
	indexer2.set_value(false);
	pros::delay(50);
	Indexer::pushsingle();
	pros::delay(240);
	Indexer::pushsingle();
	pros::delay(260);
	Indexer::pushsingle();
	pros::delay(100);
	Indexer::pushtriple();
	// then the angle is
	chassis.moveTo(-18,-8,5000);
	chassis.turnTo(-20.3,-19,5000, false);
	flywheel.set_velocity_custom_controller(2375);
	Intake::fwdspin();
	Train::setVolt(90,90);
	pros::delay(1600);
	Train::setVolt(0,0);
	pros::delay(100);
	Train::setVolt(-90,-90);
	pros::delay(850);
	chassis.turnTo(55,46,3000,true);
	indexer2.set_value(true);
	pros::delay(60);
	indexer2.set_value(false);
	pros::delay(50);
	Indexer::pushsingle();
	pros::delay(240);
	Indexer::pushsingle();
	pros::delay(240);
	Indexer::pushsingle();
	Indexer::pushtriple();
}
//54.4 19.8 -88
//56.7 14.34 -37.73 ( this is the pointa for the angl before shooting)

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		
		Shooter::shoot(1725, 2075, 2075, 1725);
		Intake::roll();
		Train::setStop(pros::E_MOTOR_BRAKE_COAST);
		Train::robotCentric();
		// Indexer::push();
		Indexer::selectShooter();
		// Indexer::rapidFire();
		Expansion::launch();
		Expansion::launch_blocker();
		Indexer::angle();
		pros::delay(20);
	}
}
