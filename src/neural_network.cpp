#include "neural_network.h"
#include "memory.h"
#include "utils.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "global.h"
using namespace std;

void init_weights(double **w, int in, int out)
{
    double scale = sqrt(6.0 / (in + out));
    for (int i = 0; i < in; i++)
    {
        for (int j = 0; j < out; j++)
        {
            w[i][j] = ((rand() % 2000) - 1000) / 1000.0 * scale;
        }
    }
}

void init_biases(double *b, int size)
{
    for (int i = 0; i < size; i++)
    {
        b[i] = 0.0;
    }
}

void print_architecture()
{
    cout << "Network Architecture:\n";
    cout << "Input Layer: " << layer_sizes[0] << " neurons\n";
    for (int i = 1; i < total_layers - 1; i++)
    {
        cout << "Hidden Layer " << i << ": " << layer_sizes[i] << " neurons\n";
    }
    cout << "Output Layer: " << layer_sizes[total_layers - 1] << " neuron\n";
}

void init_network(int input_sz, int hidden_cnt, int *hidden_sizes, int output_sz)
{
    input_size = input_sz;
    output_size = output_sz;
    hidden_layers = hidden_cnt;
    total_layers = hidden_layers + 2;

    layer_sizes = new int[total_layers];
    layer_sizes[0] = input_sz;

    for (int i = 0; i < hidden_cnt; i++)
        layer_sizes[i + 1] = hidden_sizes[i];

    layer_sizes[total_layers - 1] = output_sz;

    weights = new double **[total_layers - 1];
    biases = new double *[total_layers];
    activations = new double *[total_layers];
    deltas = new double *[total_layers];

    biases[0] = nullptr;

    for (int l = 0; l < total_layers; l++)
    {
        int neurons = layer_sizes[l];

        activations[l] = alloc_array(neurons);
        deltas[l] = alloc_array(neurons);

        if (l > 0)
        {
            biases[l] = alloc_array(neurons);
            init_biases(biases[l], neurons);
        }

        if (l < total_layers - 1)
        {
            int prev = layer_sizes[l];
            int next = layer_sizes[l + 1];
            weights[l] = alloc_2d(prev, next);
            init_weights(weights[l], prev, next);
        }
    }

    print_architecture();
}
