#ifndef TRAINING_H
#define TRAINING_H
#pragma once

void train(double* x, double* y, int size, int epochs, double lr);
double evaluate_loss(double* x, double* y, int size);
void train_menu();

#endif
