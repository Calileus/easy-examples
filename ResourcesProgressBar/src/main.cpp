#include <windows.h>
#include <commctrl.h>
#include "../resource.h"

#define IDC_PROGRESS 1001
#define IDT_PROGRESS_TIMER 2001

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
