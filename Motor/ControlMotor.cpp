#include "ControlMotor.h"
// variables to store the number of encoder pulses
// for each motor

unsigned char IN1 = 6; // 馬達B 的正反轉接腳編號
unsigned char IN2 = 5;
unsigned char ENA = 7; // 馬達B 的 P

unsigned char IN3 = 8; // 馬達B 的正反轉接腳編號
unsigned char IN4 = 9;
unsigned char ENB = 11;

float Kp = 0.04; // PID proportional control Gain
float Ki = 0.004;
float Kd = 0.014;

PidControl PidControlInstance;

ControlMotor::ControlMotor()
{
  unsigned long lastMilli = 0; // loop timing
  unsigned long lastMilliPrint = 0;
  volatile long motorCountL = 0;
  volatile long motorCountR = 0;
  float speedActR = 0;
  float speedActL = 0;
  float speedReqR = 0;
  float speedReqL = 0;
  float pwmVal_R = 0;
  float pwmVal_L = 0;
  MotorInital();
  
  


}
ControlMotor::~ControlMotor(){
}

void ControlMotor::MotorInital(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(LH_ENCODER_A, INPUT);
  pinMode(LH_ENCODER_B, INPUT);
  pinMode(RH_ENCODER_A, INPUT);
  pinMode(RH_ENCODER_B, INPUT);
  PidControlInstance.setPid(0.04,Ki,Kd);
}


void ControlMotor::MotorGo()
{
  getParam();
  if ((millis() - lastMilli) >= LOOPTIME)
  { // enter tmed loop
    lastMilli = millis();
    printMotorInfo();
    getMotorData();                                       // calculate speed, volts and Amps
    pwmVal_R = PidControlInstance.updatePid(speedReqR, speedActR); // compute PWM value
    // pwmVal_L = updatePid(pwmVal_L, speedReqL, speedActL);
  }
  analogWrite(ENA, pwmVal_R + 30.0);
  analogWrite(ENB, pwmVal_L);
}

void ControlMotor::printMotorInfo()
{ // display data
  if ((millis() - lastMilliPrint) >= 50)
  {
    lastMilliPrint = millis();

//    Serial.print(speedActR);
//    Serial.print(",");
//    Serial.println(speedReqR);
  }
}

void ControlMotor::getMotorData()
{                             // calculate speed, volts and Amps
  static long countAnt_R = 0; // last count
  static long countAnt_L = 0;
  speedActR = ((motorCountR - countAnt_R) * (60 * (1000 / LOOPTIME))) / (16 * 29); // 16 pulses X 29 gear ratio = 464 counts per output shaft rev
  countAnt_R = motorCountR;
  speedActL = ((motorCountL - countAnt_L) * (60 * (1000 / LOOPTIME))) / (16 * 29); // 16 pulses X 29 gear ratio = 464 counts per output shaft rev
  countAnt_L = motorCountL;
}

void ControlMotor::motorControll(bool switch1, bool switch2, bool switch3, bool switch4)
{
  digitalWrite(IN1, switch1);
  digitalWrite(IN2, switch2);
  digitalWrite(IN3, switch3);
  digitalWrite(IN4, switch4);
}
void ControlMotor::motorControllForward()
{
  motorControll(LOW, HIGH, LOW, HIGH);
}
void ControlMotor::motorControllBackward()
{
  motorControll(HIGH, LOW, HIGH, LOW);
}
void ControlMotor::motorControllTurnRight()
{
  motorControll(HIGH, LOW, LOW, HIGH);
}
void ControlMotor::motorControllTurnLeft()
{
  motorControll(LOW, HIGH, HIGH, LOW);
}
void ControlMotor::motorControllStop()
{
  motorControll(LOW, LOW, HIGH, LOW);
}

int ControlMotor::getParam()
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
      motorControllForward();
    }
    if (cmd == '-')
    {
      motorControllBackward();
    }
    break;
  case 'o': // user should type "oo"
    motorControllStop();
    speedReqR = 0;
    speedReqL = 0;
    break;
  default:
    Serial.println("???");
  }
}

void ControlMotor::rightEncoderEvent()
{
  if (digitalRead(RH_ENCODER_B) == LOW)
  {
    motorCountR++;
  }
  else
  {
    motorCountR--;
  }
}
void ControlMotor::leftEncoderEvent()
{
  if (digitalRead(LH_ENCODER_B) == LOW)
  {
    motorCountL++;
  }
  else
  {
    motorCountL--;
  }
}
