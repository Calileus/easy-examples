/// \file main.cpp
/// \brief Windows modeless dialog box example with buttons and input validation.
///
/// Demonstrates:
/// - Creating a custom window class with dialog-like behavior
/// - Button controls and event handling
/// - Edit controls for text input
/// - Input validation
/// - Message box dialogs
/// - Window message handling
///
/// \author Easy Examples
/// \version 1.0

#include <windows.h>
#include <sstream>
#include <string>

#define IDC_EDIT_NAME 1001      ///< Edit control ID for name input.
#define IDC_EDIT_AGE 1002       ///< Edit control ID for age input.
#define IDC_BUTTON_OK 1003      ///< OK button ID.
#define IDC_BUTTON_CLEAR 1004   ///< Clear button ID.
#define IDC_STATIC_OUTPUT 1005  ///< Static text control for output.

/// \brief Forward declaration of window procedure.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/// \brief Helper function to get text from an edit control.
/// \param hwnd Window handle.
/// \param id Control ID.
/// \return The text from the control.
std::string GetEditText(HWND hwnd, int id) {
    HWND hEdit = GetDlgItem(hwnd, id);
    char buffer[256] = {0};
    GetWindowTextA(hEdit, buffer, sizeof(buffer));
    return std::string(buffer);
}

/// \brief Helper function to set text in a static control.
/// \param hwnd Window handle.
/// \param id Control ID.
/// \param text Text to display.
void SetStaticText(HWND hwnd, int id, const std::string& text) {
    HWND hStatic = GetDlgItem(hwnd, id);
    SetWindowTextA(hStatic, text.c_str());
}

/// \brief Validate user input and display results.
/// \param hwnd Main window handle.
void ValidateAndDisplay(HWND hwnd) {
    std::string name = GetEditText(hwnd, IDC_EDIT_NAME);
    std::string ageStr = GetEditText(hwnd, IDC_EDIT_AGE);
    
    // Validate name
    if (name.empty()) {
        MessageBoxA(hwnd, "Please enter a name.", "Validation Error", MB_OK | MB_ICONWARNING);
        return;
    }
    
    // Validate age
    int age = 0;
    try {
        age = std::stoi(ageStr);
        if (age < 0 || age > 150) {
            MessageBoxA(hwnd, "Age must be between 0 and 150.", "Validation Error", MB_OK | MB_ICONWARNING);
            return;
        }
    } catch (...) {
        MessageBoxA(hwnd, "Age must be a valid number.", "Validation Error", MB_OK | MB_ICONWARNING);
        return;
    }
    
    // Display results
    std::stringstream ss;
    ss << "Hello, " << name << "!\nYou are " << age << " years old.";
    
    SetStaticText(hwnd, IDC_STATIC_OUTPUT, ss.str());
    MessageBoxA(hwnd, ss.str().c_str(), "Input Received", MB_OK | MB_ICONINFORMATION);
}

/// \brief Window message handler for the dialog window.
/// \param hwnd Window handle.
/// \param uMsg Message identifier.
/// \param wParam Message-specific word parameter.
/// \param lParam Message-specific long parameter.
/// \return Message-dependent result.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        // Create label for name
        CreateWindowA("STATIC", "Name:",
            WS_CHILD | WS_VISIBLE,
            20, 20, 50, 25,
            hwnd, (HMENU)-1, GetModuleHandle(NULL), NULL);
        
        // Create edit control for name
        CreateWindowA("EDIT", "",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            80, 20, 200, 25,
            hwnd, (HMENU)IDC_EDIT_NAME, GetModuleHandle(NULL), NULL);
        
        // Create label for age
        CreateWindowA("STATIC", "Age:",
            WS_CHILD | WS_VISIBLE,
            20, 60, 50, 25,
            hwnd, (HMENU)-1, GetModuleHandle(NULL), NULL);
        
        // Create edit control for age
        CreateWindowA("EDIT", "",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            80, 60, 200, 25,
            hwnd, (HMENU)IDC_EDIT_AGE, GetModuleHandle(NULL), NULL);
        
        // Create OK button
        CreateWindowA("BUTTON", "Submit",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            80, 100, 90, 30,
            hwnd, (HMENU)IDC_BUTTON_OK, GetModuleHandle(NULL), NULL);
        
        // Create Clear button
        CreateWindowA("BUTTON", "Clear",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            190, 100, 90, 30,
            hwnd, (HMENU)IDC_BUTTON_CLEAR, GetModuleHandle(NULL), NULL);
        
        // Create output static text
        CreateWindowA("STATIC", "Results will appear here",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            20, 150, 260, 60,
            hwnd, (HMENU)IDC_STATIC_OUTPUT, GetModuleHandle(NULL), NULL);
        
        return 0;
    }
    
    case WM_COMMAND: {
        int id = LOWORD(wParam);
        int code = HIWORD(wParam);
        
        if (code == BN_CLICKED) {
            if (id == IDC_BUTTON_OK) {
                ValidateAndDisplay(hwnd);
            } else if (id == IDC_BUTTON_CLEAR) {
                // Clear edit controls
                SetWindowTextA(GetDlgItem(hwnd, IDC_EDIT_NAME), "");
                SetWindowTextA(GetDlgItem(hwnd, IDC_EDIT_AGE), "");
                SetStaticText(hwnd, IDC_STATIC_OUTPUT, "Results will appear here");
                SetFocus(GetDlgItem(hwnd, IDC_EDIT_NAME));
            }
        }
        return 0;
    }
    
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    
    return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

/// \brief Entry point for Windows dialog application.
/// \param hInstance Current instance handle.
/// \param nShowCmd Window display mode.
/// \return Exit code.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nShowCmd) {
    const char CLASS_NAME[] = "DialogExampleWindowClass";
    
    WNDCLASSA wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
    
    RegisterClassA(&wc);
    
    HWND hwnd = CreateWindowExA(
        0,
        CLASS_NAME,
        "Dialog Example - Input Validation",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 330, 270,
        NULL,
        NULL,
        hInstance,
        NULL);
    
    if (!hwnd) {
        return 1;
    }
    
    ShowWindow(hwnd, nShowCmd);
    
    MSG msg = {};
    while (GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    
    return (int)msg.wParam;
}
