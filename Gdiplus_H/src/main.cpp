/// \file main.cpp
/// \brief Windows GUI example with GDI+ graphics library.
///
/// Demonstrates using GDI+ (Graphics Device Interface Plus) for
/// high-quality 2D graphics and image rendering on Windows.
/// Shows proper initialization and cleanup of GDI+.
///
/// \author Easy Examples
/// \version 1.0

#include <windows.h>
#include <commctrl.h>
#include <gdiplus.h>

using namespace Gdiplus;

/// \brief Entry point for GDI+ graphics application.
///
/// Initializes GDI+ library before use and ensures proper cleanup
/// via GdiplusShutdown to free graphics resources.
///
/// \param hInstance Handle to current instance.
/// \param hPrevInstance Reserved; always NULL.
/// \param lpCmdLine Command line arguments.
/// \param nShowCmd Window display mode.
/// \return Exit code (0 on success).
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
