#include "PIDControl.h"
PidControl::PidControl()
{
  last_error = 0;
  errorAccmu = 0;
  pidP = 0;
  pidI = 0;
  pidD = 0;


}
PidControl::~PidControl(){
}

void PidControl::setPid(float kp, float ki, float kd){
  pidP = kp;
  pidI = ki;
  pidD = kd;
}

float PidControl::updatePid(float targetValue, float currentValue)
{
  float pidTerm = 0;
  float error = 0;
  error = abs(targetValue) - abs(currentValue);
  
  errorAccmu += error;
  //  errorAccmu = constrain(errorAccmu,0,)
  pidTerm = (pidP * error) - abs(pidI * (error - last_error)) + (pidD * errorAccmu);
  last_error = error;
  return constrain(pidTerm, -30, 225.0);
}
