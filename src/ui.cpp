#include "ui.h"
#include "training.h"
#include "model.h"
#include "neural_network.h"
#include "propagation.h"
#include "memory.h"    
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "global.h"
using namespace std;

void menu() {
    int choice;
    while (true) {
        cout << "\n============================\n";
        cout << "     MINI TENSORFLOW        \n";
        cout << "============================\n";
        cout << "1. Train model\n";
        cout << "2. Load model\n";
        cout << "3. Predict\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            train_menu();
            cout << "\nSave trained model? (y/n): ";
            char save_choice;
            cin >> save_choice;
            if (save_choice == 'y' || save_choice == 'Y') {
                save_model("model/model.bin");
            }
        } 
        else if (choice == 2) {
            load_model("model/model.bin");
        } 
        else if (choice == 3) {
            print_prediction_demo();
        } 
        else if (choice == 4) {
            cout << "Goodbye! See you next time!\n";
            break;
        } 
        else {
            cout << "Invalid choice! Please try again.\n";
        }
    }
}

void print_prediction_demo() {
    if (total_layers <= 0 || layer_sizes == nullptr || activations == nullptr) {
        cout << "Error: No model is loaded or trained yet!\n";
        cout << "Please train a model or load one first.\n";
        return;
    }

    cout << "\nEnter " << input_size << " input value(s) separated by space: ";
    
    double* user_input = alloc_array(input_size);
    for (int i = 0; i < input_size; i++) {
        while (!(cin >> user_input[i])) {
            cout << "Invalid input! Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    forward(user_input);

    double prediction = activations[total_layers - 1][0];
    cout << fixed << setprecision(8);
    cout << "\nPrediction: " << prediction << endl;

    free_1d(user_input);  
}