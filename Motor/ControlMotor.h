#include <Arduino.h>
#include "PidControl.h"

// pins for the encoder inputs
#define RH_ENCODER_A 2
#define RH_ENCODER_B 3
#define LH_ENCODER_A 4
#define LH_ENCODER_B 5
#define LOOPTIME 100
#define CHANGESPEED 500

class ControlMotor
{
public:
    ControlMotor();
    ~ControlMotor();
    void printMotorInfo();
    void getMotorData();
    void motorControll(bool switch1, bool switch2, bool switch3, bool switch4);
    void motorControllForward();
    void motorControllBackward();
    void motorControllTurnRight();
    void motorControllTurnLeft();
    void motorControllStop();
    int getParam();
    float updatePid(float command, float targetValue, float currentValue);
    void rightEncoderEvent();
    void leftEncoderEvent();
    void MotorInital();
    void MotorGo();

    unsigned long lastMilli; // loop timing
    unsigned long lastMilliPrint;
    volatile long motorCountL;
    volatile long motorCountR;
    float speedActR;
    float speedActL;
    float speedReqR;
    float speedReqL;
    float pwmVal_R;
    float pwmVal_L;
    float errorAccmu;
};
