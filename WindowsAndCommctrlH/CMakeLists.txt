cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MyWindowsProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable, specifying the source file with the correct path
add_executable(MyWindowsProject WIN32 src/main.cpp)

# Link against Windows libraries
target_link_libraries(MyWindowsProject user32 comctl32)