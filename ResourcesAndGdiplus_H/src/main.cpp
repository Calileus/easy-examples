/// \file main.cpp
/// \brief Windows GUI combining resource files with GDI+ graphics.
///
/// Demonstrates loading resources (icons, strings) from compiled resource files
/// (.rc) and using them alongside GDI+ graphics rendering.
/// Shows the integration of resource management with graphics APIs.
///
/// \author Easy Examples
/// \version 1.0

#include <windows.h>
#include <commctrl.h>
#include <gdiplus.h>
#include "../resource.h"

using namespace Gdiplus;

/// \brief Entry point for resource-based graphics application.
///
/// Loads resources from the compiled resource file and initializes
/// GDI+ for graphics rendering.
///
/// \param hInstance Handle to current instance (used for resource loading).
/// \param hPrevInstance Reserved; always NULL.
/// \param lpCmdLine Command line arguments.
/// \param nShowCmd Window display mode.
/// \return Exit code (0 on success).
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
