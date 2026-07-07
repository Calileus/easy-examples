cmake_minimum_required(VERSION 3.14)

project(ModernCPP_Containers)

include(CTest)

option(EASYEXAMPLES_STRICT_WARNINGS "Treat warnings as errors for quality gates" OFF)

if(DEFINED MODERNCPP_CONTAINERS_STRICT_WARNINGS)
    set(EASYEXAMPLES_STRICT_WARNINGS ${MODERNCPP_CONTAINERS_STRICT_WARNINGS})
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(containers_example main.cpp)

# Compiler-specific options
if(MSVC)
    set(CONTAINERS_WARNING_FLAGS /W4)
    if(EASYEXAMPLES_STRICT_WARNINGS)
        list(APPEND CONTAINERS_WARNING_FLAGS /WX)
    endif()
    target_compile_options(containers_example PRIVATE ${CONTAINERS_WARNING_FLAGS})
else()
    set(CONTAINERS_WARNING_FLAGS -Wall -Wextra -pedantic)
    if(EASYEXAMPLES_STRICT_WARNINGS)
        list(APPEND CONTAINERS_WARNING_FLAGS -Werror)
    endif()
    target_compile_options(containers_example PRIVATE ${CONTAINERS_WARNING_FLAGS})
endif()

# Set output directory
set_target_properties(containers_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

if(BUILD_TESTING)
    add_test(NAME moderncpp_containers_smoke
             COMMAND $<TARGET_FILE:containers_example>)
endif()
