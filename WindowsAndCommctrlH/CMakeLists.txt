cmake_minimum_required(VERSION 3.14)

# Set the project name
project(WindowsAndCommctrlH)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable, specifying the source file with the correct path
add_executable(windows_and_commctrl WIN32 src/main.cpp)

# Link against Windows libraries
target_link_libraries(windows_and_commctrl user32 comctl32)