#include "training.h"
#include "propagation.h"
#include "neural_network.h"
#include "dataset.h"
#include "utils.h"
#include "global.h"   
#include <iostream>
#include <string>
using namespace std;


void train(double* x, double* y, int size, int epochs, double lr)
{
    for (int e = 1; e <= epochs; e++)
    {
        shuffle_data(x, y, size);

        double total_loss = 0.0;

        for (int i = 0; i < size; i++)
        {
            double input_val[1] = { x[i] };

            // 2. Forward pass
            forward(input_val);

            // 3. Compute output error
            compute_output_error(y[i]);

            // 4. Backward pass
            backward();

            // 5. Update weights
            update_weights(lr);

            // 6. Accumulate loss (MSE)
            double pred = activations[total_layers - 1][0];
            total_loss += 0.5 * (pred - y[i]) * (pred - y[i]);

            if (i == 0 && e <= 5)
                cout << "  ep " << e << "  pred=" << pred
                     << "  target=" << y[i] << '\n';
        }

        cout << "Epoch " << e 
             << " | Loss: " << total_loss / size << endl;
    }

    cout << "\nTraining Completed Successfully!\n";
}

// Evaluate loss on entire 1D dataset
double evaluate_loss(double* x, double* y, int size)
{
    double total_loss = 0.0;

    for (int i = 0; i < size; i++)
    {
        double input_val[1] = { x[i] };
        forward(input_val);
        double pred = activations[total_layers - 1][0];
        total_loss += 0.5 * (pred - y[i]) * (pred - y[i]);
    }

    return total_loss / size;
}

// Menu for training
void train_menu()
{
    cout << "\n============================\n";
    cout << "     MINI TENSORFLOW        \n";
    cout << "============================\n";

    cout << "\nChoose dataset to train on:\n";
    cout << "1. XOR\n";
    cout << "2. sin(x)\n";
    cout << "3. x^2\n";
    cout << "4. x^3\n";
    cout << "5. Custom file\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    if (choice < 1 || choice > 5)
    {
        cout << "Invalid choice!\n";
        return;
    }

    string filename;
    int input_dim = 1;

    if (choice == 1)
    {
        filename = "datasets/XOR.txt";
        input_dim = 2;
    }
    else if (choice == 2)
        filename = "datasets/sine.txt";
    else if (choice == 3)
        filename = "datasets/x_square.txt";
    else if (choice == 4)
        filename = "datasets/x_cube.txt";
    else
    {
        char temp_filename[100];
        cout << "Enter filename: ";
        cin >> temp_filename;
        filename = temp_filename;
    }

    int hidden_layers;
    cout << "Enter number of hidden layers: ";
    cin >> hidden_layers;

    int* hidden_neurons = new int[hidden_layers];

    for (int i = 0; i < hidden_layers; i++)
    {
        cout << "Neurons in layer " << i + 1 << ": ";
        cin >> hidden_neurons[i];
    }

    total_layers = hidden_layers + 2;

    init_network(input_dim, hidden_layers, hidden_neurons, 1);

    int epochs;
    double lr;

    cout << "Enter number of epochs: ";
    cin >> epochs;

    cout << "Enter learning rate: ";
    cin >> lr;

    cout << "\nTraining started...\n";

    if (choice == 1)
    {

        XorDataset xd = load_Xor_Dataset(filename.c_str());
        int size = xd.size;

        for (int e = 1; e <= epochs; e++)
        {
            double epoch_loss = 0.0;

            for (int i = 0; i < size; i++)
            {
                double input_val[2];
                input_val[0] = xd.input[i][0];
                input_val[1] = xd.input[i][1];

                forward(input_val);
                compute_output_error(xd.output[i]);
                backward();
                update_weights(lr);

                double pred = activations[total_layers - 1][0];
                epoch_loss += 0.5 * (pred - xd.output[i]) * (pred - xd.output[i]);
            }

            if (e % 50 == 0 || e == 1)
            {
                cout << "Epoch " << e 
                     << " | Loss: " << epoch_loss / size << endl;
            }
        }

        cout << "\n🎉 Training Completed Successfully!\n";

        double final_loss = 0.0;
        for (int i = 0; i < size; i++)
        {
            double input_val[2];
            input_val[0] = xd.input[i][0];
            input_val[1] = xd.input[i][1];
            forward(input_val);
            double pred = activations[total_layers - 1][0];
            final_loss += 0.5 * (pred - xd.output[i]) * (pred - xd.output[i]);
        }
        final_loss /= size;
        cout << "\nFinal Loss: " << final_loss << endl;
    }
    else
    {
        Dataset d = initialize_load_data(filename.c_str());
        int size = d.size;
        double* x = d.input;
        double* y = d.output;

        train(x, y, size, epochs, lr);

        cout << "\nFinal Loss: " << evaluate_loss(x, y, size) << endl;
    }

    delete[] hidden_neurons;
}
