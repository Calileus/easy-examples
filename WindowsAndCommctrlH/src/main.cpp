/// \file main.cpp
/// \brief Windows GUI example with common controls initialization.
///
/// Demonstrates using the Common Controls library (commctrl.h) which provides
/// standard UI controls like buttons, listboxes, and progress bars.
/// Shows proper initialization of the common controls before use.
///
/// \author Easy Examples
/// \version 1.0

#include <windows.h>
#include <commctrl.h>

/// \brief Entry point for Windows application with common controls.
///
/// Initializes the common controls library and displays a message box.
/// Common controls must be initialized before use via InitCommonControlsEx.
///
/// \param hInstance Handle to current instance.
/// \param hPrevInstance Reserved; always NULL.
/// \param lpCmdLine Command line arguments.
/// \param nShowCmd Window display mode.
/// \return Exit code (0 on success).
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // Initialize common controls
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icex);

    MessageBox(NULL, "Hello, Windows with Common Controls!", "Greetings", MB_OK);
    return 0;
}
