cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(VsCodeCmakeW2src VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(vscode_cmake_w2src src/main.cpp src/helper.cpp)
