#include "main.h"

//Controller Setup
extern okapi::Controller controller;
extern okapi::ControllerButton intakeBtn;
extern okapi::ControllerButton outtakeBtn;
extern okapi::ControllerButton trayBtn;
extern okapi::ControllerButton liftUpBtn;
extern okapi::ControllerButton liftDownBtn;

//Motors
extern okapi::MotorGroup intakeMotors;
extern okapi::Motor lift;
extern okapi::Motor tray;

//Chassis Controller
extern std::shared_ptr<okapi::ChassisController> chassis;
extern std::shared_ptr<okapi::OdomChassisController> odomChassis;
extern std::shared_ptr<okapi::ChassisModel> chassisModel;
extern std::shared_ptr<okapi::AsyncMotionProfileController> motionProfiler;

extern bool trayToggle;
