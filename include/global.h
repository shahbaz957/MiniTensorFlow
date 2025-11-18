#ifndef GLOBAL_H
#define GLOBAL_H

extern int total_layers;
extern int input_size;
extern int output_size;

extern int hidden_layers;
extern int* layer_sizes;

extern double*** weights;
extern double** biases;

extern double** activations;
extern double** deltas;

#endif
