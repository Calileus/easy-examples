#pragma once

#include <cstdint>

enum class DialogControlKind {
    NameLabel,
    NameEdit,
    AgeLabel,
    AgeEdit,
    SubmitButton,
    ClearButton,
    OutputStatic
};

struct DialogWindowLayout {
    const char* className;
    const char* title;
    int width;
    int height;
};

struct DialogControlLayout {
    int x;
    int y;
    int width;
    int height;
    const char* caption;
};

DialogWindowLayout GetDialogWindowLayout();
DialogControlLayout GetDialogControlLayout(DialogControlKind kind);
