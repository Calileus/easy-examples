cmake_minimum_required(VERSION 3.10)

project(ExceptionHandling)

option(EASYEXAMPLES_STRICT_WARNINGS "Treat warnings as errors for quality gates" OFF)

if(DEFINED EXCEPTION_HANDLING_STRICT_WARNINGS)
    set(EASYEXAMPLES_STRICT_WARNINGS ${EXCEPTION_HANDLING_STRICT_WARNINGS})
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable
add_executable(exception_example src/main.cpp)

# Enable exceptions explicitly (usually on by default)
if(MSVC)
    set(EXCEPTION_WARNING_FLAGS /EHsc /W4)
    if(EASYEXAMPLES_STRICT_WARNINGS)
        list(APPEND EXCEPTION_WARNING_FLAGS /WX)
    endif()
    target_compile_options(exception_example PRIVATE ${EXCEPTION_WARNING_FLAGS})
else()
    set(EXCEPTION_WARNING_FLAGS -fexceptions -Wall -Wextra -pedantic)
    if(EASYEXAMPLES_STRICT_WARNINGS)
        list(APPEND EXCEPTION_WARNING_FLAGS -Werror)
    endif()
    target_compile_options(exception_example PRIVATE ${EXCEPTION_WARNING_FLAGS})
endif()

# Set output directory
set_target_properties(exception_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
