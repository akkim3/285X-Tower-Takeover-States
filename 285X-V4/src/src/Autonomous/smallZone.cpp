#include "main.h"
#include "util/devices.hpp"
#include "auton/smallZone.hpp"

void deploy(){
	intakeMotors.moveVelocity(-200);
	pros::delay(500);
	intakeMotors.moveVelocity(0);
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
    "A");

    profileController->generatePath(
    {{0_ft, 0_ft, 0_deg},
     {4_ft, 0_ft, 0_deg}},
    "B");

    profileController->generatePath(
    {{0_in, 48_in, 0_deg},
     {-48_in, 0_in, 0_deg}},
    "C");

    intakeMotors.moveVoltage(12000);

    profileController->setTarget("A");
    profileController->waitUntilSettled();
    // profileController->removePath("A");
    intakeMotors.moveVoltage(0);

    profileController->setTarget("B", true);
    profileController->waitUntilSettled();
    // profileController->removePath("B");

    profileController->setTarget("C", true);
    profileController->waitUntilSettled();
    // profileController->removePath("C");

    intakeMotors.moveVoltage(12000);

    profileController->setTarget("A");
    profileController->waitUntilSettled();

    intakeMotors.moveVoltage(0);

    profileController->setTarget("B", true);
    profileController->waitUntilSettled();

  drive->turnAngle(135_deg);

    profileController->setTarget("B");
    profileController->waitUntilSettled();

    tray.moveAbsolute(100,100);
    tray.moveAbsolute(0, 100);
//Tune this value
outtakeToScore();
//DEPLOY THE STACK
	trayIsUp = true;
	pros::delay(3000);
	outtakeMacro();

    profileController->setTarget("B", true);
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
    "A");

    profileController->generatePath(
    {{0_ft, 0_ft, 0_deg},
     {4_ft, 0_ft, 0_deg}},
    "B");

    profileController->generatePath(
    {{0_in, 0_in, 0_deg},
     {2_in, 0_in, 0_deg}},
    "C");

    intakeMotors.moveVoltage(12000);

    profileController->setTarget("A");
    profileController->waitUntilSettled();
    profileController->removePath("A");

    profileController->setTarget("B", true);
    profileController->waitUntilSettled();

    drive->turnAngle(-90_deg);

    profileController->setTarget("B");
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

