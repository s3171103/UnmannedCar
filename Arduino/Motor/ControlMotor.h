#include <Arduino.h>
#include "PidControl.h"

// pins for the encoder inputs
#define LOOPTIME 50
#define CHANGESPEED 500

class ControlMotor
{
public:
    ControlMotor(unsigned char IN1, 
                unsigned char IN2, 
                unsigned char ENA, 
                float Kp,
                float Ki,
                float Kd);
    ~ControlMotor();
    void printMotorInfo();
    void getMotorData();
    void motorControl(bool switch1, bool switch2);
    void motorControlForward();
    void motorControlBackward();
    void motorControlStop();
    float updatePid(float command, float targetValue, float currentValue);
    void rightEncoderEvent();
    void MotorGo(float motorSp);
    void setMotorSpeed(float motorSp);

    unsigned long lastMilli = 0; // loop timing
    unsigned long lastMilliPrint = 0;
    volatile long motorCount = 0;
    float speedAct = 0;
    float motorSpeed = 0;
    float pwmVal = 0;
    float errorAccmu;
    uint8_t in1;
    uint8_t in2;
    uint8_t ena;
    long countAnt = 0;
    PidControl PidControlInstance;

};
