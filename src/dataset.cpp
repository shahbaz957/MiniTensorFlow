#include "dataset.h"
#include "memory.h"
#include <fstream>
#include <iostream>
using namespace std;

// Load dataset into already allocated arrays
void load_Dataset(const char* filename, double* &input, double* &output) {
    ifstream in(filename, ios::in);
    if (!in) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    string title;
    int size;
    getline(in, title);
    in >> size;

    for (int i = 0; i < size; i++) {
        in >> input[i] >> output[i];
    }
    in.close();
}

// Initialize and load 1D dataset
Dataset initialize_load_data(const char* filename) {
    Dataset d;
    ifstream in(filename, ios::in);
    if (!in) {
        cout << "Error: Cannot open file " << filename << endl;
        d.size = 0;
        d.input = nullptr;
        d.output = nullptr;
        return d;
    }

    string title;
    getline(in, title);
    in >> d.size;
    in.close();

    d.input = alloc_array(d.size);
    d.output = alloc_array(d.size);
    load_Dataset(filename, d.input, d.output);
    return d;
}

// For XOR dataset
void load_Xor_Dataset(const char* filename, double** &input, double* &output) {
    ifstream in(filename, ios::in);
    if (!in) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    string title;
    int size;
    getline(in, title);
    in >> size;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 2; j++) {
            in >> input[i][j];
        }
        in >> output[i];
    }
    in.close();
}

// Initialize and load XOR dataset
XorDataset load_Xor_Dataset(const char* filename) {
    XorDataset d;
    ifstream in(filename, ios::in);
    if (!in) {
        cout << "Error: Cannot open file " << filename << endl;
        d.size = 0;
        d.input = nullptr;
        d.output = nullptr;
        return d;
    }

    string title;
    getline(in, title);
    in >> d.size;
    in.close();

    d.input = alloc_2d(d.size, 2);
    d.output = alloc_array(d.size);

    load_Xor_Dataset(filename, d.input, d.output);
    return d;
}

// Print helper
void print_sample(double x, double y) {
    cout << "Input: " << x << " Output: " << y << endl;
}

// Print entire 1D dataset
void Print_whole_data(const Dataset &d) {
    for (int i = 0; i < d.size; i++) {
        print_sample(d.input[i], d.output[i]);
    }
}

// Print entire XOR dataset
void Print_whole_Xor_data(const XorDataset &d) {
    for (int i = 0; i < d.size; i++) {
        for (int j = 0; j < 2; j++) {
            cout << d.input[i][j] << " ";
        }
        cout << d.output[i] << endl;
    }
}
