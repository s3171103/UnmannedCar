#include "PIDControl.h"
PidControl::PidControl()
{
  last_error = 0;
  errorAccmu = 0;


}
PidControl::~PidControl(){
}

void PidControl::setPid(float kp, float ki, float kd){
  pidP = kp;
  pidI = ki;
  pidD = kd;
}

float PidControl::updatePid(float targetValue, float currentValue, unsigned int dt)
{
  float pidTerm = 0;
  float error = 0;
  error = abs(targetValue) - abs(currentValue);
  errorAccmu += error;
  if(errorAccmu>15000.0) errorAccmu = 15000.0;

  //  errorAccmu = constrain(errorAccmu,0,)
  // pidTerm = (pidP * error) + (pidD * errorAccmu);
if(targetValue>6500) {
  pidI = 0.2;
  pidP = 0.12;
  }
 pidTerm = (pidP * error) - abs((pidD * 1000 / dt)* (error - last_error)) + ((pidI* dt / 1000) * errorAccmu) ;

  // Serial.print(pidTerm);
  // Serial.print(",");
  // Serial.print(errorAccmu);
  // Serial.print(",");
  // Serial.print(targetValue);
  // Serial.print(",");
  // Serial.print(currentValue);
  // Serial.println(",");
  // Serial.println(error);
  last_error = error;
  return constrain(pidTerm, -30, 225.0);
}
