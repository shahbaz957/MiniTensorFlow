#include <windows.h>
#include <string>
#include <sstream>
#include "propagation.h"  // Your forward() function
#include "neural_network.h"  // Your activations, total_layers, etc.
#include "global.h"

HWND hInput, hOutput, hButton;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_COMMAND:
        if ((HWND)lParam == hButton) {
            // Get input value
            char buffer[256];
            GetWindowTextA(hInput, buffer, 256);
            double x = atof(buffer);

            // Call your Mini TensorFlow prediction
            double input_val[1] = { x };
            forward(input_val);
            double pred = activations[total_layers - 1][0];

            // Display prediction
            std::ostringstream ss;
            ss << pred;
            SetWindowTextA(hOutput, ss.str().c_str());
        }
        break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    const char CLASS_NAME[] = "MiniTensorFlowWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Mini TensorFlow GUI",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
        nullptr, nullptr, hInstance, nullptr
    );

    // Input box
    hInput = CreateWindowEx(0, "EDIT", "",
                            WS_CHILD | WS_VISIBLE | WS_BORDER,
                            50, 20, 100, 25,
                            hwnd, nullptr, hInstance, nullptr);

    // Button
    hButton = CreateWindowEx(0, "BUTTON", "Predict",
                             WS_CHILD | WS_VISIBLE,
                             170, 20, 80, 25,
                             hwnd, nullptr, hInstance, nullptr);

    // Output box (readonly)
    hOutput = CreateWindowEx(0, "EDIT", "",
                             WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
                             50, 60, 200, 25,
                             hwnd, nullptr, hInstance, nullptr);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
