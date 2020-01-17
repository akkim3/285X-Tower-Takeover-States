#include "devices.hpp"
#include "main.h"

okapi::Controller controller;

okapi::ControllerButton intakeBtn = okapi::ControllerDigital::R2;
okapi::ControllerButton outtakeBtn = okapi::ControllerDigital::R1;
okapi::ControllerButton trayBtn = okapi::ControllerDigital::A;
okapi::ControllerButton liftUpBtn = okapi::ControllerDigital::L1;
okapi::ControllerButton liftDownBtn = okapi::ControllerDigital::L2;

okapi::MotorGroup intakeMotors = MotorGroup({5,-6});
okapi::Motor tray = 8;
okapi::Motor lift(2, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);
okapi::ChassisScales scales
{
	{4.125_in, 10.2_in},
	imev5GreenTPR
};
std::shared_ptr<okapi::ChassisController> chassis = okapi::ChassisControllerBuilder()
										.withMotors({ 15, 13 }, { -2, -14 })
										.withDimensions(okapi::AbstractMotor::gearset::green, scales)
										.build();

// TODO: tune max velocity
std::shared_ptr<okapi::OdomChassisController> odomChassis = okapi::ChassisControllerBuilder()
										.withMotors({ 15, 13 }, { -2, -14 })
										.withDimensions(okapi::AbstractMotor::gearset::green, scales)
										.withMaxVelocity(100)
										.withOdometry(okapi::StateMode::FRAME_TRANSFORMATION, 0_mm, 0_deg)
										.buildOdometry();
std::shared_ptr<okapi::ChassisModel> chassisModel = std::dynamic_pointer_cast<okapi::ChassisModel>(chassis->getModel());

std::shared_ptr<okapi::AsyncMotionProfileController> motionProfiler = okapi::AsyncMotionProfileControllerBuilder()
										.withOutput(chassis)
										.withLimits({1.0, 2.0, 10.0}) // TODO: tune these
										.buildMotionProfileController();

bool trayToggle = false;
