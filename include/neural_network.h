#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H
#pragma once
#include <iostream>


extern double ***weights;
extern double **biases;
extern double **activations;
extern double **deltas;


extern int hidden_layers;
extern int *layer_sizes;
extern int input_size;
extern int output_size;

void init_weights(double **weights, int rows, int cols);
void init_biases(double *biases, int size);
void print_architecture(int hidden_layers, int *layer_sizes);
void init_network(int input_size, int hidden_layers, int *layer_sizes, int output_size);

#endif