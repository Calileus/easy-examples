cmake_minimum_required(VERSION 3.14)

project(WindowsDialog)

include(CTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable with WIN32 subsystem for GUI
add_executable(dialog_example WIN32 src/main.cpp src/input_validation.cpp)

add_executable(dialog_input_validation_test src/input_validation_test.cpp src/input_validation.cpp)

# Link Windows libraries
target_link_libraries(dialog_example
    user32
    kernel32
    comdlg32)

if(BUILD_TESTING)
    add_test(NAME windows_dialog_input_validation_test
             COMMAND $<TARGET_FILE:dialog_input_validation_test>)
endif()

# Set output directory
set_target_properties(dialog_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
