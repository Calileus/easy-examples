cmake_minimum_required(VERSION 3.14)
project(EasyExamples VERSION 0.0.0)

include(CTest)
include(FetchContent)

if(BUILD_TESTING)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(googletest)
endif()

option(BUILD_WINDOWS_EXAMPLES "Build Win32 GUI examples" ON)
option(BUILD_CONSOLE_EXAMPLES "Build console examples" ON)
option(EASYEXAMPLES_STRICT_WARNINGS "Enable strict warnings mode for selected modules" OFF)
option(EASYEXAMPLES_ENABLE_COVERAGE "Enable code coverage instrumentation (GNU/Clang only)" OFF)
option(EASYEXAMPLES_STRICT_WARNINGS_POLIMORFICSMART "Apply strict warnings mode to PolimorficSmart" ON)
option(EASYEXAMPLES_STRICT_WARNINGS_MODERNCPP_CONTAINERS "Apply strict warnings mode to ModernCPP_Containers" ON)
option(EASYEXAMPLES_STRICT_WARNINGS_EXCEPTION_HANDLING "Apply strict warnings mode to ExceptionHandling" ON)

if(EASYEXAMPLES_ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(STATUS "Enabling coverage instrumentation for compiler: ${CMAKE_CXX_COMPILER_ID}")
        add_compile_options(--coverage -O0 -g)
        add_link_options(--coverage)
    else()
        message(WARNING "EASYEXAMPLES_ENABLE_COVERAGE is ON, but compiler '${CMAKE_CXX_COMPILER_ID}' is not supported for coverage flags")
    endif()
endif()

if(EASYEXAMPLES_STRICT_WARNINGS AND EASYEXAMPLES_STRICT_WARNINGS_POLIMORFICSMART)
    set(POLIMORFICSMART_STRICT_WARNINGS ON)
else()
    set(POLIMORFICSMART_STRICT_WARNINGS OFF)
endif()

if(EASYEXAMPLES_STRICT_WARNINGS AND EASYEXAMPLES_STRICT_WARNINGS_MODERNCPP_CONTAINERS)
    set(MODERNCPP_CONTAINERS_STRICT_WARNINGS ON)
else()
    set(MODERNCPP_CONTAINERS_STRICT_WARNINGS OFF)
endif()

if(EASYEXAMPLES_STRICT_WARNINGS AND EASYEXAMPLES_STRICT_WARNINGS_EXCEPTION_HANDLING)
    set(EXCEPTION_HANDLING_STRICT_WARNINGS ON)
else()
    set(EXCEPTION_HANDLING_STRICT_WARNINGS OFF)
endif()

if(EASYEXAMPLES_STRICT_WARNINGS)
    message(STATUS "Strict warnings diagnostics:")
    message(STATUS "  EASYEXAMPLES_STRICT_WARNINGS=${EASYEXAMPLES_STRICT_WARNINGS}")
    message(STATUS "  POLIMORFICSMART_STRICT_WARNINGS=${POLIMORFICSMART_STRICT_WARNINGS}")
    message(STATUS "  MODERNCPP_CONTAINERS_STRICT_WARNINGS=${MODERNCPP_CONTAINERS_STRICT_WARNINGS}")
    message(STATUS "  EXCEPTION_HANDLING_STRICT_WARNINGS=${EXCEPTION_HANDLING_STRICT_WARNINGS}")
endif()

if(BUILD_CONSOLE_EXAMPLES)
    add_subdirectory(VsCodeCmakeEasiest)
    add_subdirectory(VsCodeCmakeW2src)
    add_subdirectory(ModernCPP_Containers)
    add_subdirectory(ExceptionHandling)
    add_subdirectory(PolimorficSmart)
endif()

if(BUILD_WINDOWS_EXAMPLES)
    if(WIN32)
        add_subdirectory(WindowsHEasiest)
        add_subdirectory(WindowsAndCommctrlH)
        add_subdirectory(WindowsDialog)
        add_subdirectory(Gdiplus_H)
        add_subdirectory(ResourcesAndGdiplus_H)
        add_subdirectory(ResourcesProgressBar)
        add_subdirectory(WindowsDrawing)
    else()
        message(STATUS "Skipping Win32 examples because host platform is not Windows")
    endif()
endif()

if(BUILD_TESTING)
    add_executable(easyexamples_gtest_migrated_runner
        tests/gtest_migrated_runner_tests.cpp
    )

    target_compile_features(easyexamples_gtest_migrated_runner PRIVATE cxx_std_17)

    target_link_libraries(easyexamples_gtest_migrated_runner PRIVATE GTest::gtest_main)

    target_compile_definitions(easyexamples_gtest_migrated_runner PRIVATE
        EASYEXAMPLES_VSCODE_EASIEST_TEST_PATH="$<TARGET_FILE:vscode_cmake_easiest>"
        EASYEXAMPLES_VSCODE_W2SRC_TEST_PATH="$<TARGET_FILE:vscode_cmake_w2src>"
        EASYEXAMPLES_CONTAINERS_TEST_PATH="$<TARGET_FILE:containers_example>"
        EASYEXAMPLES_EXCEPTION_TEST_PATH="$<TARGET_FILE:exception_example>"
    )

    if(TARGET simple_test)
        target_compile_definitions(easyexamples_gtest_migrated_runner PRIVATE
            EASYEXAMPLES_SIMPLE_TEST_PATH="$<TARGET_FILE:simple_test>"
        )
    endif()

    if(TARGET threaded_tests)
        target_compile_definitions(easyexamples_gtest_migrated_runner PRIVATE
            EASYEXAMPLES_THREADED_TEST_PATH="$<TARGET_FILE:threaded_tests>"
        )
    endif()

    if(TARGET dialog_input_validation_test)
        target_compile_definitions(easyexamples_gtest_migrated_runner PRIVATE
            EASYEXAMPLES_DIALOG_INPUT_VALIDATION_TEST_PATH="$<TARGET_FILE:dialog_input_validation_test>"
        )
    endif()

    include(GoogleTest)
    gtest_discover_tests(easyexamples_gtest_migrated_runner)
endif()
