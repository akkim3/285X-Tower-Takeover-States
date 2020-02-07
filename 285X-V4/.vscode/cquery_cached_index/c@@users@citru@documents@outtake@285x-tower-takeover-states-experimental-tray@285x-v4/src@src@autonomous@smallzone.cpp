#include "main.h"
#include "util/devices.hpp"
#include "auton/smallZone.hpp"

void redSmall(){

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

void blueSmall(){

	
}