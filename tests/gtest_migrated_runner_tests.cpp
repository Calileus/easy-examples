#include <gtest/gtest.h>

#include <cstdlib>
#include <fstream>
#include <string>

namespace
{

int RunCommand(const char* executable_path)
{
    std::ifstream probe(executable_path, std::ios::binary);
    if (!probe.good())
    {
        return -999;
    }
    probe.close();
    std::string command = "\"";
    command += executable_path;
    command += "\"";
    return std::system(command.c_str());
}

} // namespace

TEST(EasyExamplesMigratedTests, VsCodeCmakeEasiestSmoke)
{
    const int rc = RunCommand(EASYEXAMPLES_VSCODE_EASIEST_TEST_PATH);
    if (rc == -999)
    {
        GTEST_SKIP() << "Executable not available: " << EASYEXAMPLES_VSCODE_EASIEST_TEST_PATH;
    }
    EXPECT_EQ(0, rc);
}

TEST(EasyExamplesMigratedTests, VsCodeCmakeW2srcSmoke)
{
    const int rc = RunCommand(EASYEXAMPLES_VSCODE_W2SRC_TEST_PATH);
    if (rc == -999)
    {
        GTEST_SKIP() << "Executable not available: " << EASYEXAMPLES_VSCODE_W2SRC_TEST_PATH;
    }
    EXPECT_EQ(0, rc);
}

TEST(EasyExamplesMigratedTests, ModernCppContainersSmoke)
{
    const int rc = RunCommand(EASYEXAMPLES_CONTAINERS_TEST_PATH);
    if (rc == -999)
    {
        GTEST_SKIP() << "Executable not available: " << EASYEXAMPLES_CONTAINERS_TEST_PATH;
    }
    EXPECT_EQ(0, rc);
}

TEST(EasyExamplesMigratedTests, ExceptionHandlingSmoke)
{
    const int rc = RunCommand(EASYEXAMPLES_EXCEPTION_TEST_PATH);
    if (rc == -999)
    {
        GTEST_SKIP() << "Executable not available: " << EASYEXAMPLES_EXCEPTION_TEST_PATH;
    }
    EXPECT_EQ(0, rc);
}

#ifdef EASYEXAMPLES_SIMPLE_TEST_PATH
TEST(EasyExamplesMigratedTests, PolimorficSimple)
{
    const int rc = RunCommand(EASYEXAMPLES_SIMPLE_TEST_PATH);
    if (rc == -999)
    {
        GTEST_SKIP() << "Executable not available: " << EASYEXAMPLES_SIMPLE_TEST_PATH;
    }
    EXPECT_EQ(0, rc);
}
#endif

#ifdef EASYEXAMPLES_THREADED_TEST_PATH
TEST(EasyExamplesMigratedTests, PolimorficThreaded)
{
    const int rc = RunCommand(EASYEXAMPLES_THREADED_TEST_PATH);
    if (rc == -999)
    {
        GTEST_SKIP() << "Executable not available: " << EASYEXAMPLES_THREADED_TEST_PATH;
    }
    EXPECT_EQ(0, rc);
}
#endif

#ifdef EASYEXAMPLES_DIALOG_INPUT_VALIDATION_TEST_PATH
TEST(EasyExamplesMigratedTests, WindowsDialogInputValidation)
{
    const int rc = RunCommand(EASYEXAMPLES_DIALOG_INPUT_VALIDATION_TEST_PATH);
    if (rc == -999)
    {
        GTEST_SKIP() << "Executable not available: " << EASYEXAMPLES_DIALOG_INPUT_VALIDATION_TEST_PATH;
    }
    EXPECT_EQ(0, rc);
}
#endif
