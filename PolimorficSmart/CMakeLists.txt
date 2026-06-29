cmake_minimum_required(VERSION 3.14)
project(PolimorficSmart)

include(CTest)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Try to find GTest, but make it optional for now
find_package(GTest QUIET)

set(FINANCIAL_SHARED_SOURCES
    portfolio_market.cpp
)

# Add executable for main example
add_executable(financial_example main.cpp ${FINANCIAL_SHARED_SOURCES})

# Add simple test executable (always available)
add_executable(simple_test simple_test.cpp ${FINANCIAL_SHARED_SOURCES})

# Add threaded example executable
add_executable(threaded_example threaded_main.cpp)

# Add threaded test executable
add_executable(threaded_tests threaded_tests.cpp)

if(BUILD_TESTING)
    add_test(NAME financial_simple_test COMMAND simple_test)
    add_test(NAME financial_threaded_test COMMAND threaded_tests)
endif()

# Add test executable (only if GTest is found)
if(GTest_FOUND)
    add_executable(financial_tests test_financial_instruments.cpp ${FINANCIAL_SHARED_SOURCES})
    target_link_libraries(financial_tests GTest::gtest GTest::gtest_main)

    if(BUILD_TESTING)
        add_test(NAME financial_gtest_suite COMMAND financial_tests)
    endif()
    
    # Custom target to run tests
    add_custom_target(run_tests
        COMMAND financial_tests
        DEPENDS financial_tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running financial instruments tests"
    )
endif()

# Compiler-specific options
if(MSVC)
    target_compile_options(financial_example PRIVATE /W4)
    target_compile_options(simple_test PRIVATE /W4)
    target_compile_options(threaded_example PRIVATE /W4)
    target_compile_options(threaded_tests PRIVATE /W4)
    if(GTest_FOUND)
        target_compile_options(financial_tests PRIVATE /W4)
    endif()
else()
    target_compile_options(financial_example PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(simple_test PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(threaded_example PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(threaded_tests PRIVATE -Wall -Wextra -pedantic)
    if(GTest_FOUND)
        target_compile_options(financial_tests PRIVATE -Wall -Wextra -pedantic)
    endif()
endif()

# Set output directory
set_target_properties(financial_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

set_target_properties(simple_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

set_target_properties(threaded_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

set_target_properties(threaded_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

if(GTest_FOUND)
    set_target_properties(financial_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()

# Add include directory
target_include_directories(financial_example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(simple_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(threaded_example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(threaded_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
if(GTest_FOUND)
    target_include_directories(financial_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endif()

# Custom target to run the example
add_custom_target(run_example
    COMMAND financial_example
    DEPENDS financial_example
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running financial instruments example"
)

# Custom target to run simple tests
add_custom_target(run_simple_tests
    COMMAND simple_test
    DEPENDS simple_test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running simple financial instruments tests"
)

# Custom target to run threaded example
add_custom_target(run_threaded_example
    COMMAND threaded_example
    DEPENDS threaded_example
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running threaded financial instruments example"
)

# Custom target to run threaded tests
add_custom_target(run_threaded_tests
    COMMAND threaded_tests
    DEPENDS threaded_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running threaded financial instruments tests"
)
