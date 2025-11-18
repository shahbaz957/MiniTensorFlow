# Mini TensorFlow

Mini TensorFlow is a lightweight, C++ based neural network framework designed for learning and experimenting with basic deep learning concepts. It supports multiple datasets including XOR, sine, and polynomial functions, and allows users to train, save, load, and predict using fully-connected feedforward networks.

---

## Features

- **Multiple datasets**: XOR, sin(x), x², x³, and custom datasets.
- **Flexible network architecture**: Users can define number of hidden layers and neurons per layer.
- **Activation functions**:
  - Sigmoid for XOR and classification tasks.
  - ReLU for polynomial regression tasks.
  - Linear output for regression tasks.
- **Model persistence**: Save and load trained models to binary files.
- **Command-line interface (CLI)** for easy interaction.
- **Forward and backward propagation** implemented from scratch in C++. Using Mathematical Functions

---

## Project Structure

MiniTensorFlow/
├── include/                → Header files
├── src/                    → Source implementation
├── datasets/               → Training data
│   ├── XOR.txt
│   ├── sine.txt
│   ├── x_square.txt
│   └── x_cube.txt
├── model/                  → Saved models
│   └── model.bin
├── main.cpp                → Entry point
├── README.md               → This file

---

## To Run Locally 
```bash
g++ -std=c++11 -O2 -Iinclude src/*.cpp main.cpp -o mini_tf
```
---

## Author Names 
* Mirza Shahbaz Ali Baig (BCSF24M005)
* Ali Hamza Maqsood (BCSF24M010)

