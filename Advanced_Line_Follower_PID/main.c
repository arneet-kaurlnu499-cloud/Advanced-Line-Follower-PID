/*****************************************************************************
*
* Copyright (C) 2013 - 2017 Texas Instruments Incorporated - http://www.ti.com/
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* * Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the
*   distribution.
*
* * Neither the name of Texas Instruments Incorporated nor the names of
*   its contributors may be used to endorse or promote products derived
*   from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*
* MSP432 empty main.c template
*
******************************************************************************/

#include "msp.h"
#include "pid.h"

PID_Controller pid;

int clamp(int value, int min, int max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

int calculate_error(int s0, int s1, int s2, int s3, int s4)
{
    int weights[5] = {-2, -1, 0, 1, 2};
    int sensors[5] = {s0, s1, s2, s3, s4};
    int i;
    int sum = 0;
    int count = 0;

    for (i = 0; i < 5; i++)
    {
        if (sensors[i])
        {
            sum += weights[i];
            count++;
        }
    }

    if (count == 0) return 0;
    return sum / count;
}

void set_motor_speed(int left_speed, int right_speed)
{
    left_speed = clamp(left_speed, 0, 1000);
    right_speed = clamp(right_speed, 0, 1000);

    // Replace this with your real PWM motor code
    // Example:
    // MOTOR_LEFT_PWM = left_speed;
    // MOTOR_RIGHT_PWM = right_speed;
}

int main(void)
{
    int s0, s1, s2, s3, s4;
    int error;
    float correction;
    int base_speed = 600;
    int left_speed, right_speed;

    PID_Init(&pid, 120.0f, 0.0f, 40.0f);

    while (1)
    {
        // Replace these with real sensor readings from your line follower
        s0 = 0;
        s1 = 0;
        s2 = 1;
        s3 = 0;
        s4 = 0;

        error = calculate_error(s0, s1, s2, s3, s4);
        correction = PID_Compute(&pid, (float)error);

        left_speed = base_speed + (int)correction;
        right_speed = base_speed - (int)correction;

        set_motor_speed(left_speed, right_speed);
    }
}
