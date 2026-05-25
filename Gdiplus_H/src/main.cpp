#include <windows.h>
#include <commctrl.h>
#include <gdiplus.h>

using namespace Gdiplus;

// Entry point for the program
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    // Initialize common controls
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icex);

    MessageBox(NULL, "Hello, Windows with GDI+!", "Greetings", MB_OK);
    
    // Cleanup GDI+
    GdiplusShutdown(gdiplusToken);

    return 0;
}
