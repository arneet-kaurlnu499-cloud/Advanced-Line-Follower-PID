#include "pid.h"

void PID_Init(PID_Controller *pid, float kp, float ki, float kd)
{
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;
    pid->prev_error = 0.0f;
    pid->integral = 0.0f;
}

float PID_Compute(PID_Controller *pid, float error)
{
    float derivative = error - pid->prev_error;
    pid->integral += error;

    float output = (pid->Kp * error) +
                   (pid->Ki * pid->integral) +
                   (pid->Kd * derivative);

    pid->prev_error = error;
    return output;
}
