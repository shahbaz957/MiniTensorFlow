#include "utils.h"
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivative(double sigmoid_output) {
    return sigmoid_output * (1.0 - sigmoid_output);
}


void shuffle_data(double* inputs, double* targets, int size) {
    for (int i = size - 1; i > 0; --i) {
        int j = rand() % (i + 1);

        // Swap inputs
        std::swap(inputs[i], inputs[j]);
        // Swap targets
        std::swap(targets[i], targets[j]);
    }
}

void print_datapoint(double x, double y) {
    cout << "Input: " << x << " | Target: " << y << endl;
}


double mean_squared_error(double predicted, double target) {
    double error = predicted - target;
    return 0.5 * error * error;
}