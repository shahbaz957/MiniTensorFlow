#ifndef MEMORY_H
#define MEMORY_H



double* alloc_array(int size);

double** alloc_2d(int rows, int cols);

void free_2d(double** arr, int rows);




#endif