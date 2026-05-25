/// \file main.cpp
/// \brief Simplest Windows GUI example using Win32 API.
///
/// Demonstrates basic Windows programming with a simple message box.
/// This is the minimal starting point for Win32 GUI applications.
///
/// \author Easy Examples
/// \version 1.0

#include <windows.h>
#include <iostream>

/// \brief Program entry point demonstrating basic Win32 MessageBox.
/// \return Exit code (always 0).
int main() {
    MessageBox(NULL, "Hello, Windows!", "Greetings", MB_OK);
    std::cout << "This is a console output." << std::endl;
    return 0;
}
