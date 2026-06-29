cmake_minimum_required(VERSION 3.10)

project(WindowsDialog)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable with WIN32 subsystem for GUI
add_executable(dialog_example WIN32 src/main.cpp)

# Link Windows libraries
target_link_libraries(dialog_example
    user32
    kernel32
    comdlg32)

# Set output directory
set_target_properties(dialog_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
