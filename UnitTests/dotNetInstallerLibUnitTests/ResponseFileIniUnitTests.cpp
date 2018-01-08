#include "StdAfx.h"
#include "ResponseFileIniUnitTests.h"
#include "ResponseFileUnitTests.cpp"

using namespace DVLib::UnitTests;

void ResponseFileIniUnitTests::testExec()
{
    ResponseFileUnitTestsTestData testdata[] = 
    {
        { "", "" },
        { "text", "text" },
        { "#GUID", "#GUID" },
        { "[section]\r\nGUID=#GUID", "[section]\r\nGUID=" + DVLib::wstring2string(
        InstallerSession::Instance->ExpandVariables(L"#GUID")) },
    };

    ResponseFileUnitTests::testExec(testdata, ARRAYSIZE(testdata));
}
