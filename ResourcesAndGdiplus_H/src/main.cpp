#include <windows.h>
#include <commctrl.h>
#include <gdiplus.h>
#include "../resource.h"  // Include the resource header

using namespace Gdiplus;

// Entry point for the program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    // Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    // Initialize common controls
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icex);

    // Load the icon from resources
    HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
    if (hIcon) {
        MessageBox(NULL, "Hello, Windows with Resources!", "Greetings", MB_OK | MB_ICONINFORMATION);
        DestroyIcon(hIcon);
    }

    // Cleanup GDI+
    GdiplusShutdown(gdiplusToken);
    return 0;
}
