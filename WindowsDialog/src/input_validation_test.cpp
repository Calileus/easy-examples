#include "input_validation.h"
#include "dialog_logic.h"
#include "dialog_commands.h"
#include "dialog_layout.h"
#include "dialog_submission.h"

#include <iostream>

namespace {

bool AssertTrue(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAIL: " << message << std::endl;
        return false;
    }
    std::cout << "PASS: " << message << std::endl;
    return true;
}

bool RunValidationTests() {
    int age = -1;

    if (!AssertTrue(TryParseValidatedAge("0", age) && age == 0, "Parses minimum age")) return false;
    if (!AssertTrue(TryParseValidatedAge("150", age) && age == 150, "Parses maximum age")) return false;
    if (!AssertTrue(TryParseValidatedAge("42", age) && age == 42, "Parses typical valid age")) return false;

    if (!AssertTrue(!TryParseValidatedAge("", age), "Rejects empty input")) return false;
    if (!AssertTrue(!TryParseValidatedAge("abc", age), "Rejects non-numeric input")) return false;
    if (!AssertTrue(!TryParseValidatedAge("10abc", age), "Rejects partial numeric input")) return false;
    if (!AssertTrue(!TryParseValidatedAge("-1", age), "Rejects negative age")) return false;
    if (!AssertTrue(!TryParseValidatedAge("151", age), "Rejects age above max")) return false;

    return true;
}

bool RunDialogLogicTests() {
    if (!AssertTrue(!IsNameValid(""), "Rejects empty name")) return false;
    if (!AssertTrue(IsNameValid("Alice"), "Accepts non-empty name")) return false;

    const std::string message = BuildGreetingMessage("Alice", 42);
    if (!AssertTrue(message == "Hello, Alice!\nYou are 42 years old.", "Builds greeting message with expected format")) return false;

    return true;
}

bool RunDialogCommandTests() {
    if (!AssertTrue(DetermineDialogAction(123, kDialogSubmitButtonId) == DialogAction::None,
                    "Ignores non-click notification codes")) return false;

    if (!AssertTrue(DetermineDialogAction(kDialogButtonClickedNotification, kDialogSubmitButtonId) == DialogAction::Submit,
                    "Maps submit button click to submit action")) return false;

    if (!AssertTrue(DetermineDialogAction(kDialogButtonClickedNotification, kDialogClearButtonId) == DialogAction::Clear,
                    "Maps clear button click to clear action")) return false;

    if (!AssertTrue(DetermineDialogAction(kDialogButtonClickedNotification, 9999) == DialogAction::None,
                    "Ignores unknown control IDs")) return false;

    const DialogResetPolicy resetPolicy = GetDialogResetPolicy();
    if (!AssertTrue(resetPolicy.focusControlId == kDialogEditNameId,
                    "Reset policy focuses name edit control")) return false;

    if (!AssertTrue(std::string(resetPolicy.outputText) == "Results will appear here",
                    "Reset policy uses expected default output text")) return false;

    return true;
}

bool RunDialogSubmissionTests() {
    const DialogSubmissionResult missingName = EvaluateDialogSubmission("", "25");
    if (!AssertTrue(missingName.status == DialogSubmissionStatus::MissingName,
                    "Submission reports missing-name status")) return false;
    if (!AssertTrue(missingName.message == "Please enter a name.",
                    "Submission reports expected missing-name message")) return false;

    const DialogSubmissionResult invalidAge = EvaluateDialogSubmission("Alice", "abc");
    if (!AssertTrue(invalidAge.status == DialogSubmissionStatus::InvalidAge,
                    "Submission reports invalid-age status")) return false;
    if (!AssertTrue(invalidAge.message == "Age must be a valid number between 0 and 150.",
                    "Submission reports expected invalid-age message")) return false;

    const DialogSubmissionResult success = EvaluateDialogSubmission("Alice", "42");
    if (!AssertTrue(success.status == DialogSubmissionStatus::Success,
                    "Submission reports success status")) return false;
    if (!AssertTrue(success.message == "Hello, Alice!\nYou are 42 years old.",
                    "Submission reports expected success message")) return false;

    return true;
}

bool RunDialogLayoutTests() {
    const DialogWindowLayout windowLayout = GetDialogWindowLayout();
    if (!AssertTrue(std::string(windowLayout.className) == "DialogExampleWindowClass",
                    "Window layout provides expected class name")) return false;
    if (!AssertTrue(std::string(windowLayout.title) == "Dialog Example - Input Validation",
                    "Window layout provides expected title")) return false;
    if (!AssertTrue(windowLayout.width == 330 && windowLayout.height == 270,
                    "Window layout provides expected dimensions")) return false;

    const DialogControlLayout submitLayout = GetDialogControlLayout(DialogControlKind::SubmitButton);
    if (!AssertTrue(std::string(submitLayout.caption) == "Submit",
                    "Submit button layout provides expected caption")) return false;

    const DialogControlLayout clearLayout = GetDialogControlLayout(DialogControlKind::ClearButton);
    if (!AssertTrue(std::string(clearLayout.caption) == "Clear",
                    "Clear button layout provides expected caption")) return false;

    const DialogControlLayout outputLayout = GetDialogControlLayout(DialogControlKind::OutputStatic);
    const DialogResetPolicy resetPolicy = GetDialogResetPolicy();
    if (!AssertTrue(std::string(outputLayout.caption) == std::string(resetPolicy.outputText),
                    "Output static layout caption matches reset policy text")) return false;

    return true;
}

} // namespace

int main() {
    if (RunValidationTests() && RunDialogLogicTests() && RunDialogCommandTests() && RunDialogSubmissionTests() && RunDialogLayoutTests()) {
        std::cout << "All dialog validation tests passed." << std::endl;
        return 0;
    }

    std::cout << "Dialog validation tests failed." << std::endl;
    return 1;
}
