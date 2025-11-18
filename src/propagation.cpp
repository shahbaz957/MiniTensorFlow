#include "propagation.h"
#include "neural_network.h"
#include "global.h"
#include "utils.h"
#include <cmath>
using namespace std;


void forward(double* input) {
    // Copy input to first layer
    for (int i = 0; i < layer_sizes[0]; i++)
        activations[0][i] = input[i];

    // Propagate through each layer
    for (int l = 0; l < total_layers - 1; l++) {
        int prev = layer_sizes[l];
        int curr = layer_sizes[l + 1];

        for (int j = 0; j < curr; j++) {
            double z = biases[l + 1][j]; // bias

            for (int i = 0; i < prev; i++)
                z += weights[l][i][j] * activations[l][i];

            if (l == total_layers - 2)  // Output layer
                activations[l + 1][j] = z;  // Linear activation
            else
                activations[l + 1][j] = sigmoid(z); // Hidden layers
        }
    }
}


void compute_output_error(double target) {
    int out_layer = total_layers - 1;
    double pred = activations[out_layer][0];

    deltas[out_layer][0] = pred - target;
}

void backward() {
    for (int l = total_layers - 2; l >= 0; l--) {
        int prev = layer_sizes[l];
        int curr = layer_sizes[l + 1];

        for (int i = 0; i < prev; i++) {
            double sum = 0.0;
            for (int j = 0; j < curr; j++)
                sum += weights[l][i][j] * deltas[l + 1][j];

            if (l == total_layers - 2)   
                deltas[l][i] = sum;          
            else
                deltas[l][i] = sum * activations[l][i] * (1 - activations[l][i]);
        }
    }
}

void update_weights(double learning_rate) {
    for (int l = 0; l < total_layers - 1; l++) {
        int prev = layer_sizes[l];
        int curr = layer_sizes[l + 1];

        for (int i = 0; i < prev; i++) {
            for (int j = 0; j < curr; j++) {
                weights[l][i][j] -= learning_rate * deltas[l + 1][j] * activations[l][i];
            }
        }

        for (int j = 0; j < curr; j++) {
            biases[l + 1][j] -= learning_rate * deltas[l + 1][j];
        }
    }
}

double predict(double x) {
    double input[1] = {x};
    forward(input);
    return activations[total_layers - 1][0];
}
