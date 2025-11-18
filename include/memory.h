#ifndef MEMORY_H
#define MEMORY_H
#pragma once


double* alloc_array(int size);

double** alloc_2d(int rows, int cols);

void free_2d(double** arr, int rows);
void free_1d(double *arr);




#endif