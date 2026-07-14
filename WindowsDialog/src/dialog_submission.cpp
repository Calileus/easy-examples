#include "dialog_submission.h"

#include "dialog_logic.h"
#include "input_validation.h"

DialogSubmissionResult EvaluateDialogSubmission(const std::string& name, const std::string& ageText) {
    if (!IsNameValid(name)) {
        return {DialogSubmissionStatus::MissingName, "Please enter a name."};
    }

    int age = 0;
    if (!TryParseValidatedAge(ageText, age)) {
        return {DialogSubmissionStatus::InvalidAge, "Age must be a valid number between 0 and 150."};
    }

    return {DialogSubmissionStatus::Success, BuildGreetingMessage(name, age)};
}
