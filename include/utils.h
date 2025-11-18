#ifndef UTILS_H
#define UTILS_H
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iostream>
#pragma once

double sigmoid(double x);
double sigmoid_derivative(double x);
double random_weight();
void print_datapoint(double x, double y);
void shuffle_data(double* x, double* y, int n);
double mean_squared_error(double predicted, double target);



#endif