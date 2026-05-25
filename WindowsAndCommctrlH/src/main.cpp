#include <windows.h>
#include <commctrl.h>

// Entry point for the program
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // Initialize common controls
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icex);

    MessageBox(NULL, "Hello, Windows with Common Controls!", "Greetings", MB_OK);
    return 0;
}
