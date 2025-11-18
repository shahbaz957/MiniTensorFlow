#ifndef UTILS_H
#define UTILS_H
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iostream>


double sigmoid(double x);
double sigmoid_derivative(double x);
double random_weight();

double mean_squared_error(double predicted, double target);

void shuffle_data(double* &x, double* &y, int size);

void print_sample(double x, double y);


#endif