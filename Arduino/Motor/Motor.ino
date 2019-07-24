#include"ControlMotor.h"

ControlMotor motor1;
float speedReqR,speedReqL;

void setup() {
  // put your setup code here, to run once:
  attachInterrupt(0, rightEncoderEventTest, FALLING);
  Serial.begin(115200);
}

void loop() {
  getParam();
  motor1.setMotorSpeed(speedReqR);
  motor1.MotorGo();

}

void rightEncoderEventTest(){
  motor1.rightEncoderEvent();
}

int getParam()
{
  char param, cmd;
  if (!Serial.available())
    return 0;
  delay(10);
  param = Serial.read(); // get parameter byte
  if (!Serial.available())
    return 0;
  cmd = Serial.read(); // get command byte
  Serial.flush();
  switch (param)
  {
  case 'v': // adjust speed
    if (cmd == '+')
    {
      speedReqR += CHANGESPEED;
      speedReqL += CHANGESPEED;
      if (speedReqR > 10000)
        speedReqR = 10000;
      if (speedReqL > 10000)
        speedReqL = 10000;
    }
    if (cmd == '-')
    {
      speedReqR -= CHANGESPEED;
      speedReqL -= CHANGESPEED;
      if (speedReqR < 0)
        speedReqR = 0;
      if (speedReqL < 0)
        speedReqL = 0;
    }
    break;
  case 's': // adjust direction
    if (cmd == '+')
    {
      motor1.motorControlForward();
    }
    if (cmd == '-')
    {
      motor1.motorControlBackward();
    }
    break;
  case 'o': // user should type "oo"
    motor1.motorControlStop();
    speedReqR = 0;
    speedReqL = 0;
    break;
  default:
    Serial.println("???");
  }
}

