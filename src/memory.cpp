#include "memory.h"
#include <iostream>
using namespace std;
// Allocate 1D array
double *alloc_array(int size)
{
    double *arr = new double[size];
    return arr;
}
// Allocate 2D array
double **alloc_2d(int row, int col)
{
    double **arr = new double *[row];
    for (int i = 0; i < row; i++)
    {
        arr[i] = new double[col];
    }
    return arr;
}
// Free space of 1D array
void free_1d(double *arr)
{
    delete[] arr;
}
// Free space of 2D array
void free_2d(double **arr, int row)
{
    for (int i = 0; i < row; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}