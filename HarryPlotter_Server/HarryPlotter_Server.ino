#include <AccelStepper.h>

// Debug defines
// =================================================
//#define DEBUG_COMMS

// Commands defines
// =================================================
#define READY_CMD "READY;"
#define RESEND_CMD "RESEND;"
#define DRAWING_CMD "DRAWING;"

// Messages defines
// =================================================
#define UNRECOGNISED_E_MSG "ERROR_UNRECOGNISED_COMMAND;"

// Consts
// =================================================
const int COMMAND_BUFFER_LENGHT = 50;
const char COMMAND_SEMICOLON = ';';
const int REBROADCAST_READY_INTERVAL = 5000;

// Motors
// =================================================
#define MOTOR_A_ENABLE_PIN 8
#define MOTOR_B_ENABLE_PIN 8
// The X Stepper pins
#define MOTOR_A_STEP_PIN 2 //X.STEP
#define MOTOR_A_DIR_PIN 5 // X.DIR
// The Y Stepper pins
#define MOTOR_B_STEP_PIN 3 //Y.STEP
#define MOTOR_B_DIR_PIN 6 // Y.DIR
#define STEP_PER_REV 200

static float maxMotorSpeed = 800.0;
static float motorAcceleration = 800.0;
boolean usingAcceleration = true;

AccelStepper motorA(AccelStepper::DRIVER, MOTOR_A_STEP_PIN, MOTOR_A_DIR_PIN); 
AccelStepper motorB(AccelStepper::DRIVER, MOTOR_B_STEP_PIN, MOTOR_B_DIR_PIN); 

// Globals
// =================================================
char commandBuffer[COMMAND_BUFFER_LENGHT];
boolean commandConfirmed = false;
int numberOfCommandParams = 0;

void setup() 
{
  Serial.begin(57600);
  MotorSetup();
  Serial.println("HARRY PLOTTER ready to do some magic!");
  SendCommandReady();
}

void loop()
{
  if (WaitForNextCommand(commandBuffer)) 
  {
#ifdef DEBUG_COMMS    
    Serial.print(F("Last comm: "));
    Serial.print(commandBuffer);
    Serial.println(F("..."));
#endif
    ParseAndExecuteCommand(commandBuffer);
  }
}
