#include <windows.h>
#include <commctrl.h>
#include <iostream>

// Entry point for the program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Initialize common controls
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icex);

    MessageBox(NULL, "Hello, Windows with Common Controls!", "Greetings", MB_OK);
    std::cout << "This is a console output." << std::endl;
    return 0;
}
