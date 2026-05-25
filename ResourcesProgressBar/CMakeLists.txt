cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MyWindowsProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable, specifying the source file
add_executable(MyWindowsProject src/main.cpp resource.rc)

# Link against Windows libraries
target_link_libraries(MyWindowsProject 
    user32 
    comctl32 
    gdi32 
    gdiplus)

# Add resource file compilation
set_source_files_properties(resource.rc PROPERTIES LANGUAGE RC)
