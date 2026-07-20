/// \file main.cpp
/// \brief Windows modeless dialog box example with buttons and input validation.
///
/// Demonstrates:
/// - Creating a custom window class with dialog-like behavior
/// - Button controls and event handling
/// - Edit controls for text input
/// - Input validation
/// - Message box dialogs
/// - Window message handling
///
/// \author Easy Examples
/// \version 1.0

#include <windows.h>
#include <string>
#include "dialog_commands.h"
#include "dialog_layout.h"
#include "dialog_logic.h"
#include "dialog_submission.h"
#include "input_validation.h"

/// \brief Forward declaration of window procedure.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/// \brief Helper function to get text from an edit control.
/// \param hwnd Window handle.
/// \param id Control ID.
/// \return The text from the control.
std::string GetEditText(HWND hwnd, int id) {
    HWND hEdit = GetDlgItem(hwnd, id);
    char buffer[256] = {0};
    GetWindowTextA(hEdit, buffer, sizeof(buffer));
    return std::string(buffer);
}

/// \brief Helper function to set text in a static control.
/// \param hwnd Window handle.
/// \param id Control ID.
/// \param text Text to display.
void SetStaticText(HWND hwnd, int id, const std::string& text) {
    HWND hStatic = GetDlgItem(hwnd, id);
    SetWindowTextA(hStatic, text.c_str());
}

/// \brief Validate user input and display results.
/// \param hwnd Main window handle.
void ValidateAndDisplay(HWND hwnd) {
    std::string name = GetEditText(hwnd, kDialogEditNameId);
    std::string ageStr = GetEditText(hwnd, kDialogEditAgeId);

    const DialogSubmissionResult result = EvaluateDialogSubmission(name, ageStr);
    if (result.status == DialogSubmissionStatus::Success) {
        SetStaticText(hwnd, kDialogOutputStaticId, result.message);
        MessageBoxA(hwnd, result.message.c_str(), "Input Received", MB_OK | MB_ICONINFORMATION);
        return;
    }

    MessageBoxA(hwnd, result.message.c_str(), "Validation Error", MB_OK | MB_ICONWARNING);
}

/// \brief Window message handler for the dialog window.
/// \param hwnd Window handle.
/// \param uMsg Message identifier.
/// \param wParam Message-specific word parameter.
/// \param lParam Message-specific long parameter.
/// \return Message-dependent result.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        const DialogResetPolicy resetPolicy = GetDialogResetPolicy();
        const DialogControlLayout nameLabelLayout = GetDialogControlLayout(DialogControlKind::NameLabel);
        const DialogControlLayout nameEditLayout = GetDialogControlLayout(DialogControlKind::NameEdit);
        const DialogControlLayout ageLabelLayout = GetDialogControlLayout(DialogControlKind::AgeLabel);
        const DialogControlLayout ageEditLayout = GetDialogControlLayout(DialogControlKind::AgeEdit);
        const DialogControlLayout submitButtonLayout = GetDialogControlLayout(DialogControlKind::SubmitButton);
        const DialogControlLayout clearButtonLayout = GetDialogControlLayout(DialogControlKind::ClearButton);
        const DialogControlLayout outputStaticLayout = GetDialogControlLayout(DialogControlKind::OutputStatic);

        // Create label for name
        CreateWindowA("STATIC", nameLabelLayout.caption,
            WS_CHILD | WS_VISIBLE,
            nameLabelLayout.x, nameLabelLayout.y, nameLabelLayout.width, nameLabelLayout.height,
            hwnd, (HMENU)-1, GetModuleHandle(NULL), NULL);
        
        // Create edit control for name
        CreateWindowA("EDIT", "",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            nameEditLayout.x, nameEditLayout.y, nameEditLayout.width, nameEditLayout.height,
            hwnd, reinterpret_cast<HMENU>(static_cast<UINT_PTR>(kDialogEditNameId)), GetModuleHandle(NULL), NULL);
        
        // Create label for age
        CreateWindowA("STATIC", ageLabelLayout.caption,
            WS_CHILD | WS_VISIBLE,
            ageLabelLayout.x, ageLabelLayout.y, ageLabelLayout.width, ageLabelLayout.height,
            hwnd, (HMENU)-1, GetModuleHandle(NULL), NULL);
        
        // Create edit control for age
        CreateWindowA("EDIT", "",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            ageEditLayout.x, ageEditLayout.y, ageEditLayout.width, ageEditLayout.height,
            hwnd, reinterpret_cast<HMENU>(static_cast<UINT_PTR>(kDialogEditAgeId)), GetModuleHandle(NULL), NULL);
        
        // Create OK button
        CreateWindowA("BUTTON", submitButtonLayout.caption,
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            submitButtonLayout.x, submitButtonLayout.y, submitButtonLayout.width, submitButtonLayout.height,
            hwnd, reinterpret_cast<HMENU>(static_cast<UINT_PTR>(kDialogSubmitButtonId)), GetModuleHandle(NULL), NULL);
        
        // Create Clear button
        CreateWindowA("BUTTON", clearButtonLayout.caption,
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            clearButtonLayout.x, clearButtonLayout.y, clearButtonLayout.width, clearButtonLayout.height,
            hwnd, reinterpret_cast<HMENU>(static_cast<UINT_PTR>(kDialogClearButtonId)), GetModuleHandle(NULL), NULL);
        
        // Create output static text
        CreateWindowA("STATIC", outputStaticLayout.caption,
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            outputStaticLayout.x, outputStaticLayout.y, outputStaticLayout.width, outputStaticLayout.height,
            hwnd, reinterpret_cast<HMENU>(static_cast<UINT_PTR>(kDialogOutputStaticId)), GetModuleHandle(NULL), NULL);
        
        return 0;
    }
    
    case WM_COMMAND: {
        const DialogResetPolicy resetPolicy = GetDialogResetPolicy();
        int id = LOWORD(wParam);
        int code = HIWORD(wParam);

        const DialogAction action = DetermineDialogAction(code, id);

        if (action == DialogAction::Submit) {
            ValidateAndDisplay(hwnd);
        } else if (action == DialogAction::Clear) {
            SetWindowTextA(GetDlgItem(hwnd, kDialogEditNameId), "");
            SetWindowTextA(GetDlgItem(hwnd, kDialogEditAgeId), "");
            SetStaticText(hwnd, kDialogOutputStaticId, resetPolicy.outputText);
            SetFocus(GetDlgItem(hwnd, resetPolicy.focusControlId));
        }
        return 0;
    }
    
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    
    return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

/// \brief Entry point for Windows dialog application.
/// \param hInstance Current instance handle.
/// \param nShowCmd Window display mode.
/// \return Exit code.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nShowCmd) {
    const DialogWindowLayout windowLayout = GetDialogWindowLayout();
    
    WNDCLASSA wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = windowLayout.className;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
    
    RegisterClassA(&wc);
    
    HWND hwnd = CreateWindowExA(
        0,
        windowLayout.className,
        windowLayout.title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, windowLayout.width, windowLayout.height,
        NULL,
        NULL,
        hInstance,
        NULL);
    
    if (!hwnd) {
        return 1;
    }
    
    ShowWindow(hwnd, nShowCmd);
    
    MSG msg = {};
    while (GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    
    return (int)msg.wParam;
}
