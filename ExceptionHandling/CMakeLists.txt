cmake_minimum_required(VERSION 3.10)

project(ExceptionHandling)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable
add_executable(exception_example src/main.cpp)

# Enable exceptions explicitly (usually on by default)
if(MSVC)
    target_compile_options(exception_example PRIVATE /EHsc /W4)
else()
    target_compile_options(exception_example PRIVATE -fexceptions -Wall -Wextra -pedantic)
endif()

# Set output directory
set_target_properties(exception_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
