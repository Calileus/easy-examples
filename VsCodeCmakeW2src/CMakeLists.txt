cmake_minimum_required(VERSION 3.14)

# Set the project name and version
project(VsCodeCmakeW2src VERSION 1.0)

include(CTest)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(vscode_cmake_w2src src/main.cpp src/helper.cpp)

if(BUILD_TESTING)
	add_test(NAME vscode_cmake_w2src_smoke
			 COMMAND $<TARGET_FILE:vscode_cmake_w2src>)
endif()
