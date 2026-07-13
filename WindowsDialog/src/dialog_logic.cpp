#include "dialog_logic.h"

#include <sstream>

bool IsNameValid(const std::string& name) {
    return !name.empty();
}

std::string BuildGreetingMessage(const std::string& name, int age) {
    std::stringstream ss;
    ss << "Hello, " << name << "!\nYou are " << age << " years old.";
    return ss.str();
}
