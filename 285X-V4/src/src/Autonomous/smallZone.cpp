#include "main.h"
#include "util/devices.hpp"
#include "auton/smallZone.hpp"

void deploy(){
	lift.moveAbsolute(100,100);
	// intakeMotors.moveVelocity(-200);
	pros::delay(500);
	intakeMotors.moveVelocity(0);
	lift.moveAbsolute(0,100);

}
void oneCube(){
  deploy();
  drive->setMaxVelocity(100);
  drive->moveDistance(-1_ft);
  drive->moveDistance(2_ft);
}
void redSmall(){
	deploy();
 //SMALL SCORING ZONE ---------
    profileController->generatePath(
    {{0_ft, 0_ft, 0_deg},
     {8_ft, 0_ft, 0_deg}},
    "eight_feet");

    profileController->generatePath(
    {{0_ft, 0_ft, 0_deg},
     {4_ft, 0_ft, 0_deg}},
    "four_feet");

		profileController->generatePath(
    {{0_ft, 0_ft, 0_deg},
     {7_ft, 0_ft, 0_deg}},
    "sevenhalf_feet");

    profileController->generatePath(
    {{0_in, 48_in, 0_deg},
     {-48_in, 0_in, 0_deg}},
    "C");

    intakeMotors.moveVelocity(200);

    profileController->setTarget("eight_feet");

    profileController->waitUntilSettled();
    // profileController->removePath("eight_feet");
    //intakeMotors.moveVoltage(12000);

    profileController->setTarget("four_feet", true);
    profileController->waitUntilSettled();
    // profileController->removePath("four_feet");

    //profileController->setTarget("C", true);
    //profileController->waitUntilSettled();
    // profileController->removePath("C");

    //intakeMotors.moveVoltage(12000);

    //profileController->setTarget("eight_feet");
    //profileController->waitUntilSettled();


    intakeMotors.moveVelocity(0);

  //  profileController->setTarget("four_feet", true);
    //profileController->waitUntilSettled();

  drive->turnAngle(135_deg);
		drive->setMaxVelocity(70);
    drive->moveDistance(1.5_ft);
    //profileController->waitUntilSettled();
		drive->setMaxVelocity(200);
		drive->waitUntilSettled();
				intakeMotors.moveVelocity(0);
	//	intakeMotors.moveVoltage(-6000);
		//pros::delay(500);
		//intakeMotors.moveVoltage(0);



    //tray.moveAbsolute(100,100);
    //tray.moveAbsolute(0, 100);
//Tune this value
//outtakeToScore();
intakeMotors.moveVelocity(-200);
pros::delay(300);
intakeMotors.moveVelocity(0);
//DEPLOY THE STACK
	trayIsUp = true;
	pros::delay(3000);
	outtakeMacro();

    profileController->setTarget("eight_feet", true);
    profileController->waitUntilSettled();
}

void blueSmall(){


}

void redLarge(){
//LARGE SCORING ZONE ----------
deploy();
profileController->generatePath(
    {{0_ft, 0_ft, 0_deg},
     {6_ft, 0_ft, 0_deg}},
    "eight_feet");

    profileController->generatePath(
    {{0_ft, 0_ft, 0_deg},
     {4_ft, 0_ft, 0_deg}},
    "four_feet");

    profileController->generatePath(
    {{0_in, 0_in, 0_deg},
     {2_in, 0_in, 0_deg}},
    "C");

    intakeMotors.moveVoltage(12000);

    profileController->setTarget("eight_feet");
    profileController->waitUntilSettled();
    profileController->removePath("eight_feet");

    profileController->setTarget("four_feet", true);
    profileController->waitUntilSettled();

    drive->turnAngle(-90_deg);

    profileController->setTarget("four_feet");
    profileController->waitUntilSettled();

  drive->turnAngle(-45_deg);

    intakeMotors.moveVoltage(0);

    profileController->setTarget("C");
    profileController->waitUntilSettled();

    //DEPLOY THE STACK
	trayIsUp = true;
	pros::delay(3000);
	outtakeMacro();

    profileController->setTarget("C", true);
    profileController->waitUntilSettled();

}
