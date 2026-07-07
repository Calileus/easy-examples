#include "input_validation.h"

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

} // namespace

int main() {
    if (RunValidationTests()) {
        std::cout << "All input validation tests passed." << std::endl;
        return 0;
    }

    std::cout << "Input validation tests failed." << std::endl;
    return 1;
}
