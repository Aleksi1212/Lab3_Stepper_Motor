#ifndef MOTOR_H
#define MOTOR_H

int calibrate_motor(int *current_step);
void run(const int steps, int *current_step);

#endif