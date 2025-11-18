#include "model.h"
#include "neural_network.h"
#include "memory.h"
#include "propagation.h"
#include <fstream>
#include "global.h"
#include <iostream>
#include <iomanip>
using namespace std;

void cleanup_network() {
    int layers = total_layers;

    if (weights) {
        for (int l = 0; l < layers - 1; ++l) {
            if (weights[l]) free_2d(weights[l], layer_sizes[l]);
        }
        delete[] weights;
        weights = nullptr;
    }

    if (biases) {
        for (int l = 1; l < layers; ++l) {
            if (biases[l]) free_1d(biases[l]);
        }
        delete[] biases;
        biases = nullptr;
    }

    if (activations) {
        for (int l = 0; l < layers; ++l) {
            if (activations[l]) free_1d(activations[l]);
        }
        delete[] activations;
        activations = nullptr;
    }

    if (deltas) {
        for (int l = 0; l < layers; ++l) {
            if (deltas[l]) free_1d(deltas[l]);
        }
        delete[] deltas;
        deltas = nullptr;
    }

    if (layer_sizes) {
        delete[] layer_sizes;
        layer_sizes = nullptr;
    }

    total_layers = 0;
}

void save_model(const char* filename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }

    file.write((char*)&total_layers, sizeof(int));
    for (int i = 0; i < total_layers; i++)
        file.write((char*)&layer_sizes[i], sizeof(int));

    for (int l = 0; l < total_layers - 1; l++) {
        int from = layer_sizes[l];
        int to = layer_sizes[l + 1];

        for (int j = 0; j < from; j++)
            file.write((char*)weights[l][j], to * sizeof(double));

        file.write((char*)biases[l + 1], to * sizeof(double));
    }

    file.close();
    cout << "Model saved successfully to '" << filename << "'.\n";
}

void load_model(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Error: Could not open file for reading.\n";
        return;
    }

    cleanup_network();

    // Read total_layers
    file.read((char*)&total_layers, sizeof(int));

    // Read layer_sizes
    layer_sizes = new int[total_layers];
    for (int i = 0; i < total_layers; i++)
        file.read((char*)&layer_sizes[i], sizeof(int));

    // Allocate memory
    weights     = new double**[total_layers - 1];
    biases      = new double*[total_layers];
    activations = new double*[total_layers];
    deltas      = new double*[total_layers];
    biases[0]   = nullptr;  // input layer has no bias

    for (int l = 0; l < total_layers; l++) {
        activations[l] = alloc_array(layer_sizes[l]);
        deltas[l]      = alloc_array(layer_sizes[l]);
        if (l > 0) biases[l] = alloc_array(layer_sizes[l]);
    }

    for (int l = 0; l < total_layers - 1; l++) {
        int from = layer_sizes[l];
        int to   = layer_sizes[l + 1];
        weights[l] = alloc_2d(from, to);
    }

    for (int l = 0; l < total_layers - 1; l++) {
        int from = layer_sizes[l];
        int to   = layer_sizes[l + 1];

        for (int j = 0; j < from; j++)
            file.read((char*)weights[l][j], to * sizeof(double));

        file.read((char*)biases[l + 1], to * sizeof(double));
    }

    file.close();
    cout << "Model loaded successfully! You can now use 'Predict' from the main menu.\n";
}
