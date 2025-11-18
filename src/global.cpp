#include "global.h"


int total_layers = 0;
int input_size = 1;
int output_size = 1;

double*** weights = nullptr;
double** biases = nullptr;

double** activations = nullptr;
double** deltas = nullptr;

int hidden_layers = 0;
int* layer_sizes = nullptr;
