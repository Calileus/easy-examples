cmake_minimum_required(VERSION 3.14)

project(WindowsDrawing)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable with WIN32 subsystem
add_executable(drawing_example WIN32 src/main.cpp)

# Link Windows and GDI+ libraries
target_link_libraries(drawing_example
    user32
    gdi32
    gdiplus)

# Set output directory
set_target_properties(drawing_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
