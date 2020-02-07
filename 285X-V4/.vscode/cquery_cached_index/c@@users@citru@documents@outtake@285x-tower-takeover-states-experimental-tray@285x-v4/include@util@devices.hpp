#include "main.h"

//Controller Setup
extern okapi::Controller master;
extern okapi::ControllerButton intakeBtn;
extern okapi::ControllerButton outtakeBtn;
extern okapi::ControllerButton trayBtn;
extern okapi::ControllerButton liftUpBtn;
extern okapi::ControllerButton liftDownBtn;
extern okapi::ControllerButton outtakeMacroBtn;
extern okapi::ControllerButton trayDeployBtn;

//Motors
extern okapi::MotorGroup intakeMotors;
extern okapi::Motor lift;
extern okapi::Motor tray;

//Chassis Controller
extern std::shared_ptr<okapi::ChassisController> drive;
extern std::shared_ptr<okapi::OdomChassisController> odomChassis;
extern std::shared_ptr<okapi::ChassisModel> chassisModel;
extern std::shared_ptr<okapi::AsyncMotionProfileController> profileController;

extern bool trayToggle;
extern bool trayIsUp;

void outtakeMacro();
void trayControl();
