#pragma once

#include <string>

enum class DialogSubmissionStatus {
    Success,
    MissingName,
    InvalidAge
};

struct DialogSubmissionResult {
    DialogSubmissionStatus status;
    std::string message;
};

DialogSubmissionResult EvaluateDialogSubmission(const std::string& name, const std::string& ageText);
