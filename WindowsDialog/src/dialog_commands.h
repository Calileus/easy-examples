#pragma once

#include <cstdint>

enum class DialogAction {
    None,
    Submit,
    Clear
};

struct DialogResetPolicy {
    std::uint16_t focusControlId;
    const char* outputText;
};

constexpr std::uint16_t kDialogEditNameId = 1001;
constexpr std::uint16_t kDialogEditAgeId = 1002;
constexpr std::uint16_t kDialogSubmitButtonId = 1003;
constexpr std::uint16_t kDialogClearButtonId = 1004;
constexpr std::uint16_t kDialogOutputStaticId = 1005;
constexpr int kDialogButtonClickedNotification = 0;

DialogAction DetermineDialogAction(int notificationCode, int controlId);
DialogResetPolicy GetDialogResetPolicy();
