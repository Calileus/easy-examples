/// \file main.cpp
/// \brief Windows GUI demonstrating a progress bar control.
///
/// Shows how to create a window with a progress bar control that updates
/// over time using a timer. Demonstrates common controls usage patterns.
///
/// \author Easy Examples
/// \version 1.0

#include <windows.h>
#include <commctrl.h>
#include "../resource.h"

#define IDC_PROGRESS 1001  ///< Progress control ID.
#define IDT_PROGRESS_TIMER 2001  ///< Timer ID for progress updates.

/// \brief Window message handler for progress bar window.
///
/// Handles window creation, timer events for progress updates, and
/// destruction events.
///
/// \param hwnd Window handle.
/// \param uMsg Message identifier.
/// \param wParam Message-specific word parameter.
/// \param lParam Message-specific long parameter.
/// \return Message-dependent result.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hProgress = nullptr;
    static int progressValue = 0;

    switch (uMsg) {
    case WM_CREATE:
        hProgress = CreateWindowEx(
            0,
            PROGRESS_CLASS,
            nullptr,
            WS_CHILD | WS_VISIBLE,
            20, 30, 340, 30,
            hwnd,
            reinterpret_cast<HMENU>(IDC_PROGRESS),
            reinterpret_cast<LPCREATESTRUCT>(lParam)->hInstance,
            nullptr);

        SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
        SendMessage(hProgress, PBM_SETSTEP, 1, 0);
        SetTimer(hwnd, IDT_PROGRESS_TIMER, 40, nullptr);
        return 0;

    case WM_TIMER:
        if (wParam == IDT_PROGRESS_TIMER) {
            if (progressValue < 100) {
                ++progressValue;
                SendMessage(hProgress, PBM_SETPOS, progressValue, 0);
            } else {
                KillTimer(hwnd, IDT_PROGRESS_TIMER);
                MessageBox(hwnd, "Progress complete!", "ResourcesProgressBar", MB_OK | MB_ICONINFORMATION);
            }
        }
        return 0;

    case WM_DESTROY:
        KillTimer(hwnd, IDT_PROGRESS_TIMER);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nShowCmd) {
    /// \brief Entry point for progress bar demonstration application.
    ///
    /// Creates a window class, registers it, creates the window with a
    /// progress bar control, and runs the message loop.
    ///
    /// \param hInstance Application instance handle.
    /// \param nShowCmd Initial window show state.
    /// \return Exit code from message loop.
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_PROGRESS_CLASS;
    InitCommonControlsEx(&icex);

    const char CLASS_NAME[] = "ResourcesProgressBarWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Resources + Progress Bar",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 150,
        nullptr,
        nullptr,
        hInstance,
        nullptr);

    if (!hwnd) {
        return 0;
    }

    ShowWindow(hwnd, nShowCmd);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}
