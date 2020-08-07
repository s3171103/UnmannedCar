#include "ControlMotor.h"
// variables to store the number of encoder pulses
// for each motor


ControlMotor::ControlMotor(unsigned char IN1, 
                          unsigned char IN2, 
                          unsigned char ENA, 
                          float Kp,
                          float Ki,
                          float Kd)
{
  in1 = IN1;
  in2 = IN2;
  ena = ENA;
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  PidControlInstance.setPid(Kp,Ki,Kd);
}
ControlMotor::~ControlMotor(){
}



void ControlMotor::MotorGo(float motorSp)
{
  if ((millis() - lastMilli) >= LOOPTIME)
  { // enter tmed loop
    lastMilli = millis();
    // printMotorInfo();
    getMotorData();                                       // calculate speed, volts and Amps
    pwmVal = PidControlInstance.updatePid(motorSp, speedAct, LOOPTIME); // compute PWM value
    analogWrite(ena, pwmVal + 30.0);
  }
  // Serial.print(ena);
  // Serial.print(",");
  // Serial.print(pwmVal);
  // Serial.println(",");
  // analogWrite(ena, 100 + 30.0);
}

void ControlMotor::printMotorInfo()
{ // display data
  if ((millis() - lastMilliPrint) >= 50)
  {
    lastMilliPrint = millis();

//    Serial.print(speedAct);
//    Serial.print(",");
//    Serial.println(motorSpeed);
  }
}

void ControlMotor::getMotorData()
{                            
  // speedAct = ((motorCount - countAnt) * (60 * (1000 / LOOPTIME))) / (16 * 29); // 16 pulses X 29 gear ratio = 464 counts per output shaft rev
  speedAct = (motorCount - countAnt) * 129.31034 / LOOPTIME; // 16 pulses X 29 gear ratio = 464 counts per output shaft rev
  countAnt = motorCount;
}

void ControlMotor::motorControl(bool switch1, bool switch2)
{
  digitalWrite(in1, switch1);
  digitalWrite(in2, switch2);
}
void ControlMotor::motorControlForward()
{
  motorControl(LOW, HIGH);
}
void ControlMotor::motorControlBackward()
{
  motorControl(HIGH, LOW);
}
void ControlMotor::motorControlStop()
{
  motorControl(LOW, LOW);
}


void ControlMotor::rightEncoderEvent()
{
  // if (digitalRead(3) == LOW)
  // {
  //   motorCount++;
  // }
  // else
  // {
    motorCount++;
  // }
}

void ControlMotor::setMotorSpeed(float motorSp){
  motorSpeed = motorSp;
}
