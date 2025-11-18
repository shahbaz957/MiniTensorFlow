#ifndef Header_H
#define Header_H
double* alloc_array(int size);
double** alloc_2d(int row,int col);
void free_2d(double** arr,int row);
void free_1d(double* arr);
#endif