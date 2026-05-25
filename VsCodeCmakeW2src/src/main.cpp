/// \file main.cpp
/// \brief Entry point for multi-file CMake project example.
///
/// Demonstrates organizing code across multiple source files and linking
/// them together using CMake.

#include <iostream>
#include "helper.h"

/// \brief Entry point: calls helper function from separate module.
/// \return Exit code (0 on success).
int main() {
    std::cout << "Hello, World!" << std::endl;
    helperFunction();
    return 0;
}