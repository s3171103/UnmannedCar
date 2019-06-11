#include"ControlMotor.h"

ControlMotor motor1;

void setup() {
  // put your setup code here, to run once:
  attachInterrupt(0, rightEncoderEventTest, FALLING);
  Serial.begin(115200);
}

void loop() {
  motor1.MotorGo();

}

void rightEncoderEventTest(){
  motor1.rightEncoderEvent();
}

