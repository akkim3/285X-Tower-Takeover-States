#include "main.h"

// OPCONTORL CHASSIS
auto drive =
ChassisControllerBuilder()
  .withMotors({15, 13},{-12, -14})
  .withDimensions(AbstractMotor::gearset::green, {{4.125_in, 10.5_in}, imev5GreenTPR})
  .build();


// ODOM CHASSIS
auto odomChassis =
ChassisControllerBuilder()
  .withMotors(1, -2) // left motor is 1, right motor is 2 (reversed)
  .withGains(
      {0.001, 0, 0.0001}, // Distance controller gains
      {0.001, 0, 0.0001}, // Turn controller gains
      {0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
  )
  // green gearset, 4 inch wheel diameter, 11.5 inch wheelbase
  .withDimensions(AbstractMotor::gearset::green, {{4.125_in, 10.5_in}, imev5GreenTPR})
  .withOdometry() // use the same scales as the chassis (above)
  .buildOdometry(); // build an odometry chassis

// MOTION PROFILE CHASSIS AUTON
auto profileChassis =
ChassisControllerBuilder()
  .withMotors({15, 13}, {-12, -14})
  // Green gearset, 4 in wheel diam, 11.5 in wheel track
  .withDimensions(AbstractMotor::gearset::green, {{4.125_in, 10.5_in}, imev5GreenTPR})
  .withMaxVelocity(100)
  .build();

// PROFILE CONTROLLER
auto profileController =
AsyncMotionProfileControllerBuilder()
  .withLimits({1.0, 2.0, 10.0})
  .withOutput(profileChassis)
  .buildMotionProfileController();


// Button Configuration
ControllerButton leftArrow(ControllerDigital::left);
ControllerButton rightArrow(ControllerDigital::right);
ControllerButton upArrow(ControllerDigital::up);
ControllerButton downArrow(ControllerDigital::down);
ControllerButton liftUpBtn(ControllerDigital::L1);
ControllerButton liftDownBtn(ControllerDigital::L2);
ControllerButton outtakeBtn(ControllerDigital::R1);
ControllerButton intakeBtn(ControllerDigital::R2);
ControllerButton trayBtn(ControllerDigital::A);
ControllerButton trayUpManualBtn(ControllerDigital::up);
ControllerButton trayDownManualBtn(ControllerDigital::down);
Controller master;

// Motor Configuration
okapi::MotorGroup intakeMotors({3, -7});
okapi::Motor lift(2, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor tray(21, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);

bool trayToggle = false;
