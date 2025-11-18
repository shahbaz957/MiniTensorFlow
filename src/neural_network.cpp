#include <iostream>
#include "include/neural_network.h"
#include "utils.cpp"
using namespace std;

void init_weights(double **weights, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            weights[i][j] = random_weight();
        }
    }
}

void init_biases(double *biases, int size)
{
    for (int i = 0; i < size; i++)
    {
        biases[i] = random_weight();
    }
}

void print_architecture(int hidden_layers, int *layer_sizes)
{
    for (int i = 0; i < hidden_layers; i++)
    {
        cout << "Layer " << i + 1 << " has " << layer_sizes[i] << " neurons" << endl;
    }
}

void init_network(int input_size, int hidden_layers, int* layer_sizes, int output_size){
    
}