#include <Arduino.h>

class PidControl
{
public:
    PidControl();
    ~PidControl();
    float updatePid(float targetValue, float currentValue);
    void setPid(float kp, float ki, float kd);
    float pidP;
    float pidI;
    float pidD;
    float last_error;
    float errorAccmu;

};
