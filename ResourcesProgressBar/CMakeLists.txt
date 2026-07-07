cmake_minimum_required(VERSION 3.14)

# Set the project name
project(ResourcesProgressBar)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable, specifying the source file
add_executable(resources_progress_bar WIN32 src/main.cpp resource.rc)

# Link against Windows libraries
target_link_libraries(resources_progress_bar 
    user32 
    comctl32)

# Add resource file compilation
set_source_files_properties(resource.rc PROPERTIES LANGUAGE RC)
