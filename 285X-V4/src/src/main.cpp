#include "main.h"
#include "Util/devices.hpp"
#include "auton/smallZone.hpp"
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
 std::shared_ptr<AsyncPositionController<double, double>> liftController =
   AsyncPosControllerBuilder().withMotor(-9).build();
//okapi::AbstractMotor::GearRatioPair pair(okapi::AbstractMotor::gearset::red, 0.2);
//auto liftControllerIntegrated = AsyncPosIntegratedController(lift, pair,100,okapi::TimeUtilFactory::createDefault());
const int heightCount = 3;
const int heights[heightCount] = {0,400,1800};
int heightIndex = 0;

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");


	pros::Task trayTask(trayControl,"Tray Task");
	//pros::Task liftUpTask(liftUp,"Lift Up");
	profileController->generatePath(
			{{0_ft, 0_ft, 0_deg},
			 {0.5_ft, 0_ft, 0_deg}},
			"nudge");
	imuSensor.reset();

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
imuSensor.reset();
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
	drive->setMaxVelocity(100);
	profileController->setTarget("nudge");
//	intakeMotors.moveVelocity(-200);
	pros::delay(250);
	liftController->setTarget(heights[1]);
	liftController->waitUntilSettled();
	profileController->setTarget("nudge",true);
	liftController->setTarget(heights[0]);
	intakeMotors.moveVelocity(200);
	liftController->waitUntilSettled();
	//drive->waitUntilSettled();
	//drive->moveDistance(-0.5_ft);
	drive->setMaxVelocity(200);

blueLarge();

}


void intakeControl(void);
void trayBtnControl(void);
void liftControl(void);

void intakeControl(void)
{
	if(intakeBtn.isPressed())
    intakeMotors.moveVelocity(200);
  else if(outtakeBtn.isPressed())
    intakeMotors.moveVelocity(-200);
	else if(intakeBtn.isPressed() && outtakeBtn.isPressed()){
		intakeMotors.moveVelocity(-200);
	}
  else
    intakeMotors.moveVelocity(0);
		intakeMotors.setBrakeMode(AbstractMotor::brakeMode::hold);

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
	if(outtakeMacroBtn.changedToPressed())
	{
		//turn(45);
		outtakeMacro();
	}
	/*if(trayUpManualBtn.isPressed()){
		tray.moveVelocity(100);
	}
	if(trayDownManualBtn.isPressed()){
		tray.moveVelocity(-100);
	}
	*/
}

void trayDeploy() {
	if(trayDeployBtn.changedToPressed())
		{
		intakeMotors.moveVelocity(-100);
		pros::delay(1000);
  	}
}

void liftControl(void)
{




if(liftUpBtn.isPressed()){

	lift.moveVelocity(200);
} else if(liftDownBtn.isPressed()){
	lift.moveVelocity(-200);
} else if(upArrow.isPressed()){
	intakeMotors.moveVelocity(-25);
	lift.moveAbsolute(400,200);
	//intakeMotors.moveRelative(-360,200);
}
	else {
	lift.setBrakeMode(AbstractMotor::brakeMode::hold);
	lift.moveVelocity(0);

}

}

void opcontrol()
{

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
