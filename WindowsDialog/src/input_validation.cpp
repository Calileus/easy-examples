#include "input_validation.h"

#include <cerrno>
#include <cstdlib>

bool TryParseValidatedAge(const std::string& input, int& age) {
    if (input.empty()) {
        return false;
    }

    char* parseEnd = nullptr;
    errno = 0;
    long parsedAge = std::strtol(input.c_str(), &parseEnd, 10);
    if (errno != 0 || parseEnd == input.c_str() || (parseEnd != nullptr && *parseEnd != '\0')) {
        return false;
    }

    if (parsedAge < 0 || parsedAge > 150) {
        return false;
    }

    age = static_cast<int>(parsedAge);
    return true;
}
