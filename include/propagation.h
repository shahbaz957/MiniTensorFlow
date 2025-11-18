#ifndef PROPAGATION_H
#define PROPAGATION_H
#pragma once

void forward(double* input);
void compute_output_error(double target);
void backward();
void update_weights(double learning_rate);
double predict(double x);
#endif