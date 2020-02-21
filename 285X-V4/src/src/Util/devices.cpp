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
  .withLimits({2, 1.0, 15.0})
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
ControllerButton outtakeMacroBtn(ControllerDigital::B);
ControllerButton trayDeployBtn(ControllerDigital::X);
Controller master;

// Motor Configuration
okapi::MotorGroup intakeMotors({8, -6});
okapi::Motor lift(9, true, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor tray(21);
okapi::MotorGroup driveR({-12,-14});
okapi::MotorGroup driveL({15,13});

//Sensors
pros::ADILineSensor lineSensor = pros::ADILineSensor('A');
pros::Imu imuSensor(4);

bool trayToggle = false;
bool trayIsUp = false;


void outtakeMacro(){
  intakeMotors.moveVelocity(-75);
  pros::delay(300);
  drive->setMaxVelocity(50);
  drive->moveDistanceAsync(-1_ft);
  pros::delay(500);
  trayIsUp = false;
  drive->setMaxVelocity(200);
  //intakeMotors.moveVelocity(100);
};

void trayControl(void){
	while(true){
		if(trayIsUp){
		tray.moveVelocity(0.075*(4350-tray.getPosition()));
    intakeMotors.setBrakeMode(AbstractMotor::brakeMode::coast);
			}
	else if(!(trayIsUp))
  {
		tray.moveAbsolute(0,200);
    intakeMotors.setBrakeMode(AbstractMotor::brakeMode::hold);
	}
		std::cout << tray.getPosition();
		pros::delay(20);

			}
}
void outtakeToScore(){
 while(lineSensor.get_value_calibrated() > 2000) {
    std::cout << lineSensor.get_value() << std::endl;
  intakeMotors.moveVelocity(-50);
    pros::delay(50);
  }
  intakeMotors.moveVelocity(0);
}

const double kP = 0.85;//0.90
const double kI = 0;
const double kD = 0.35;

double deg = 0;
bool absolute = true;

void turn(double degrees){
  driveL.setBrakeMode(AbstractMotor::brakeMode::brake);
  driveR.setBrakeMode(AbstractMotor::brakeMode::brake);
  double thetaI = imuSensor.get_heading();
  double thetaF = degrees;

  double sensorValue = thetaI;
  double turnTarget = thetaF;

  double deltaI = abs(thetaF - thetaI);

  if (deltaI > 180){
    if (thetaF > 180) {
      turnTarget = thetaF - 360;
    } else {
      turnTarget = thetaF;
    }

    if (thetaI > 180) {
      sensorValue = thetaI - 360;
    } else {
      sensorValue = thetaI;
    }
  }

  double error = turnTarget - sensorValue;
  double oldError = error;
  double sumError = 0;

  bool TURN_NOT_FINISH = true;
  while (TURN_NOT_FINISH) {
    sensorValue = imuSensor.get_heading();
    printf("TARGET: %.4f\n", turnTarget);
    printf("IMU: %.4f\n", sensorValue);

    if (deltaI > 180){
      if (sensorValue > 180) {
        sensorValue = sensorValue - 360;
      }
    }

    //PROPORTIONAL
    error = turnTarget - sensorValue;
    printf("ERROR: %.4f\n", error);
    //DERIVATIVE
    double changeInError = error - oldError;
    //INTEGRAL
    if (abs(error) < 50) {
      sumError += error;
    } else {
      sumError = 0; //might be += 0?
    }

    //P, I, D
    double P = kP * error;
    double I = kI * sumError;
    double D = kD * changeInError;

    double sum = P + I + D;


    driveL.moveVelocity(sum);
    driveR.moveVelocity(-sum);

    oldError = error;
    double errorThreshold = 5;
    double velocityThreshold = 5;

    TURN_NOT_FINISH = !((abs(error) < errorThreshold) && (abs(changeInError) < velocityThreshold));
  }
  driveL.moveVelocity(0);
  driveR.moveVelocity(0);
}
