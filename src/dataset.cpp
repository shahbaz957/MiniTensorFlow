#include"include/datasets.h"
#include"include/memory.h"
#include<fstream>
#include<iostream>
using namespace std;

void load_Dataset(const char* filename,double* &input,double* &output){
    ifstream in(filename,ios::in);
    string title;
    int size;
    getline(in,title);
    in>>size;
    for (int i = 0; i <size; i++)
    {
        in>>input[i]>>output[i];
    }
    in.close();
}

Dataset initialize_load_data(const char* filename){
    Dataset d;
    ifstream in(filename,ios::in);
    string title;
    getline(in,title);
    in>>d.size;
     in.close();
    d.input=alloc_array(d.size);
    d.output=alloc_array(d.size);
    load_Dataset(filename,d.input,d.output);
    return d;
}



// For xor data
XorDataset initialize_load_Xordata(const char* filename){
    XorDataset d;
    ifstream in(filename,ios::in);
    string title;
    getline(in,title);
    in>>d.size;
     in.close();
    d.input=alloc_2d(d.size,2);
    d.output=alloc_array(d.size);
    load_Xor_Dataset(filename,d.input,d.output);
    return d;
}
void load_Xor_Dataset(const char* filename,double** &input,double* &output){
    ifstream in(filename,ios::in);
    string title;
    int size;
    getline(in,title);
    in>>size;
    for (int i = 0; i <size; i++)
    {
       for (int j = 0; j <2; j++)
       {
          in>>input[i][j];
       }
       in>>output[i];
    }
    in.close();
}
void print_data(double x, double y){
    cout<<"Input: "<<x<<" "<<"Output: "<<y<<endl;
}

void Print_whole_data(Dataset d){
    for (int i = 0; i <d.size; i++)
    {
       print_data(d.input[i],d.output[i]);
    }
}
void Print_whole_Xor_data(XorDataset d){
    for (int i = 0; i <d.size; i++)
    {
        for (int j = 0; j <2; j++)
        {
            cout<<d.input[i][j]<<" ";
        }
        cout<<d.output[i]<<endl;
    }
    
}