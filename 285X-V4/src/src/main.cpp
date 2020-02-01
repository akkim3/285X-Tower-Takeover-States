#include "main.h"
#include "Util/devices.hpp"
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
}

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
void competition_initialize()
{

}

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

void autonomous()
{
	profileController->generatePath(
	{{0_ft, 0_ft, 0_deg},
	 {8_ft, 0_ft, 0_deg}},
	"A");

	profileController->generatePath(
	{{4_ft, 0_ft, 0_deg},
	 {8_ft, 0_ft, 0_deg}},
	"B");

	profileController->generatePath(
	{{0_in, 24_in, 0_deg},
	 {24_in, 0_in, 0_deg}},
	"C");

	profileController->generatePath(
	{{0_in, 24_in, 0_deg},
	 {52_in, -24_in, 0_deg}},
	"D");

	profileController->generatePath(
	{{24_in, -24_in, 0_deg},
	 {52_in, -24_in, 0_deg}},
	"E");

	profileController->generatePath(
	{{24_in, -24_in, 0_deg},
	 {24_in, -24_in, 135_deg}},
	"F");

	intakeMotors.moveVoltage(12000);

	profileController->setTarget("A");
	profileController->waitUntilSettled();
	profileController->removePath("A");
	intakeMotors.moveVoltage(0);

	profileController->setTarget("B", true);
	profileController->waitUntilSettled();
	profileController->removePath("B");

	intakeMotors.moveVoltage(12000);

	profileController->setTarget("C", true);
	profileController->waitUntilSettled();
	profileController->removePath("C");

	intakeMotors.moveVoltage(0);

	profileController->setTarget("D", true);
	profileController->waitUntilSettled();
	profileController->removePath("D");

	profileController->setTarget("E", true);
	profileController->waitUntilSettled();
	profileController->removePath("E");

	profileController->setTarget("F");
	profileController->waitUntilSettled();
	profileController->removePath("F");
}


void intakeControl(void);
void trayBtnControl(void);
void liftControl(void);




void intakeControl(void)
{
	if(intakeBtn.isPressed())
    intakeMotors.moveVelocity(200);
  else if(outtakeBtn.isPressed())
    intakeMotors.moveVelocity(-100);
  else
    intakeMotors.moveVelocity(0);
}


void trayUp()
{

	//var string = param;
	tray.setBrakeMode(AbstractMotor::brakeMode::hold);
	//tray.moveVelocity(100);
	//pros::delay(500);
	//tray.moveVelocity(20);
	//pros::delay(2000);
	//tray.moveVelocity(0);


}
bool trayIsUp = false;
void trayControl(void* trayActive){
	while(true){
		if(trayIsUp){
		tray.moveVelocity(0.07*(4350-tray.getPosition()));
			}
	else if(!(trayIsUp)){
		tray.moveAbsolute(0,200);
	}
		std::cout << tray.getPosition();
		std::cout << (bool*)trayActive;
		pros::delay(20);

			}


}


void trayDown(void)
{

		tray.moveAbsolute(0,100);

}

void trayBtnControl()
{
  if(trayBtn.changedToPressed())
		{
		trayIsUp = !trayIsUp;
  	}
	/*if(trayUpManualBtn.isPressed()){
		tray.moveVelocity(100);
	}
	if(trayDownManualBtn.isPressed()){
		tray.moveVelocity(-100);
	}
	*/
}

void liftControl(void)
{
	if(liftUpBtn.isPressed())
  	lift.moveVelocity(100);
  else if(liftDownBtn.isPressed())
     lift.moveVelocity(-90);
  else
  	lift.moveVelocity(0);

}

void opcontrol()
{
	pros::Task trayTask(trayControl,(void*)"sample","Tray Task");

	while (1)
	{
		// DRIVETRAIN
		drive->getModel()->arcade(master.getAnalog(ControllerAnalog::leftY),
														  master.getAnalog(ControllerAnalog::rightX));
		intakeControl();
		trayBtnControl();

		liftControl();
		// DELAY
		pros::delay(20);
	}
}
