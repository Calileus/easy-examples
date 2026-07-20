#include "dialog_layout.h"

DialogWindowLayout GetDialogWindowLayout() {
    DialogWindowLayout layout;
    layout.className = "DialogExampleWindowClass";
    layout.title = "Dialog Example - Input Validation";
    layout.width = 330;
    layout.height = 270;
    return layout;
}

DialogControlLayout GetDialogControlLayout(DialogControlKind kind) {
    switch (kind) {
    case DialogControlKind::NameLabel:
        return {20, 20, 50, 25, "Name:"};
    case DialogControlKind::NameEdit:
        return {80, 20, 200, 25, ""};
    case DialogControlKind::AgeLabel:
        return {20, 60, 50, 25, "Age:"};
    case DialogControlKind::AgeEdit:
        return {80, 60, 200, 25, ""};
    case DialogControlKind::SubmitButton:
        return {80, 100, 90, 30, "Submit"};
    case DialogControlKind::ClearButton:
        return {190, 100, 90, 30, "Clear"};
    case DialogControlKind::OutputStatic:
        return {20, 150, 260, 60, "Results will appear here"};
    default:
        return {0, 0, 0, 0, ""};
    }
}
