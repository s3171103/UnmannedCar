#include"ControlMotor.h"

float speedReqR,speedReqL;
unsigned long lastMillitest = 0;
bool start = true;
float pid_p = 0.08;
float pid_i = 0.13;
float pid_d = 0.0003; //0.0003
// ControlMotor motor1(6,7,5,0.06,0.005,0.014);
ControlMotor motor1(8,9,4,pid_p,pid_i,pid_d);
ControlMotor motor2(11,10,5,pid_p,pid_i,pid_d);
ControlMotor motor3(12,13,6,pid_p,pid_i,pid_d);
void setup() {
  // put your setup code here, to run once:

  attachInterrupt(0, rightEncoderEventTest, FALLING);
  attachInterrupt(1, rightEncoderEventTest2, FALLING);
  attachInterrupt(2, rightEncoderEventTest3, FALLING);
  Serial.begin(115200);
  motor1.motorControlForward();
  motor2.motorControlForward();
  motor3.motorControlForward();
}

void loop() {
  getParam();
  motor1.MotorGo(speedReqR);
  motor2.MotorGo(speedReqR);
  motor3.MotorGo(speedReqR);
  if((millis()-lastMillitest)>100){
    Serial.print(speedReqR);
    Serial.print(",");
    Serial.print(motor1.speedAct);
    Serial.print(",");
    Serial.print(motor2.speedAct);
    Serial.print(",");
    Serial.println(motor3.speedAct);
    lastMillitest = millis();
  }
  // if((millis()-lastMillitest)>2000){
  //   if(start){
  //     speedReqR +=500;
  //     motor1.setMotorSpeed(speedReqR);
  //     motor2.setMotorSpeed(speedReqR);
  //     motor3.setMotorSpeed(speedReqR);
  //     lastMillitest = millis();
  //   }
  // }

}

void rightEncoderEventTest(){
  motor1.rightEncoderEvent();
}
void rightEncoderEventTest2(){
  motor2.rightEncoderEvent();
}
void rightEncoderEventTest3(){
  motor3.rightEncoderEvent();
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
    if (cmd =='h')start = true;
    if (cmd == 'u')
    {
      speedReqR += CHANGESPEED;
      if (speedReqR > 5500)
        speedReqR = 5500;
    }
    if (cmd == 'd')
    {
      speedReqR -= CHANGESPEED;
      if (speedReqR < 0)
        speedReqR = 0;
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
    motor2.motorControlStop();
    motor3.motorControlStop();
    speedReqR = 0;
    speedReqL = 0;
    start = false;
    break;
  default:
    Serial.println("???");
  }
  motor1.setMotorSpeed(speedReqR);
  motor2.setMotorSpeed(speedReqR);
  motor3.setMotorSpeed(speedReqR);
}
