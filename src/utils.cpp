#include "include/utils.h"
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

double sigmoid(double x)
{
    return (1 / 1 + exp(-x));
}

double derivative_sigmoid(double x)
{
    double s1 = sigmoid(x);
    return (s1 * (1 - s1));
}

// Used for the initialization of Random Weights for start of the training of neural Networks
double random_weight()
{
    return ((double)rand() / RAND_MAX) * 2 - 1; // Initialize the weights from values between -1 to 1
}

void print_datapoint(double x, double y)
{
    cout << "Input : " << x << " Target : " << y << endl;
}

void shuffle_data(double *inputs, double *targets, int size)
{
    for (int i = 0; i < size; i++)
    {
        int j = rand() % size;
        swap(inputs[i], inputs[j]);
        swap(targets[i], targets[j]);
    }
}

double mean_squared_error(double predicted, double target)
{
    return ((target - predicted) * (target - predicted));
}
