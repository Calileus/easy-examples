cmake_minimum_required(VERSION 3.14)

# Set the project name
project(Gdiplus_H)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable, specifying the source file
add_executable(gdiplus_example WIN32 src/main.cpp)

# Link against Windows libraries
target_link_libraries(
    gdiplus_example 
    user32 
    comctl32 
    gdi32 
    gdiplus)
