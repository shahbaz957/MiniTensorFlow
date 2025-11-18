#ifndef Dataaset_H
#define Dataaset_H
struct Dataset {
    double* input;
    double* output;
    int size;
};
struct XorDataset {
    double** input;
    double* output;
    int size;
};
void load_Dataset(const char* filename,double* &input,double* &output);
Dataset initialize_load_data(const char* filename);
XorDataset initialize_load_Xordata(const char* filename);
void print_sample(double x, double y);



#endif;