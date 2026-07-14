#include "dialog_commands.h"

DialogAction DetermineDialogAction(int notificationCode, int controlId) {
    if (notificationCode != kDialogButtonClickedNotification) {
        return DialogAction::None;
    }

    if (controlId == kDialogSubmitButtonId) {
        return DialogAction::Submit;
    }

    if (controlId == kDialogClearButtonId) {
        return DialogAction::Clear;
    }

    return DialogAction::None;
}

DialogResetPolicy GetDialogResetPolicy() {
    DialogResetPolicy policy;
    policy.focusControlId = kDialogEditNameId;
    policy.outputText = "Results will appear here";
    return policy;
}
