cmake_minimum_required(VERSION 3.10)

project(ModernCPP_Containers)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable
add_executable(containers_example main.cpp)

# Compiler-specific options
if(MSVC)
    target_compile_options(containers_example PRIVATE /W4)
else()
    target_compile_options(containers_example PRIVATE -Wall -Wextra -pedantic)
endif()

# Set output directory
set_target_properties(containers_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
