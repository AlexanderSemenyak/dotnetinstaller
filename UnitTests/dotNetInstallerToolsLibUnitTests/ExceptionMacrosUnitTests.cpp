#include "StdAfx.h"
#include "ExceptionMacrosUnitTests.h"

using namespace DVLib::UnitTests;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void ExceptionMacrosUnitTests::testCHECK_WIN32_DWORD()
{
    try
    {
        CHECK_WIN32_DWORD(ERROR_NOT_FOUND, "ERROR_NOT_FOUND");
        throw "expected std::exception";
    }
    catch(std::exception& ex)
    {
        std::cout << std::endl << ex.what();
        Assert::IsTrue(0 == strcmp(ex.what(), "0x80070490 - ERROR_NOT_FOUND: Element not found."));
    }
}

void ExceptionMacrosUnitTests::testCHECK_WIN32_BOOL()
{
    try
    {
        ::SetLastError(ERROR_NOT_FOUND);
        CHECK_WIN32_BOOL(false, "ERROR_NOT_FOUND");
        throw "expected std::exception";
    }
    catch(std::exception& ex)
    {
        std::cout << std::endl << ex.what();
        Assert::IsTrue(0 == strcmp(ex.what(), "0x80070490 - ERROR_NOT_FOUND: Element not found."));
    }
}

void ExceptionMacrosUnitTests::testCHECK_BOOL()
{
    try
    {
        CHECK_BOOL(false, "ERROR_NOT_FOUND");
        throw "expected std::exception";
    }
    catch(std::exception& ex)
    {
        std::cout << std::endl << ex.what();
        Assert::IsTrue(0 == strcmp(ex.what(), "ERROR_NOT_FOUND"));
    }
}

void ExceptionMacrosUnitTests::testTHROW_EX()
{
    try
    {
        THROW_EX("expected exception: " << "test");
        throw "expected std::exception";
    }
    catch(std::exception& ex)
    {
        std::cout << std::endl << ex.what();
        Assert::IsTrue(0 == strcmp(ex.what(), "expected exception: test"));
    }
}

void ExceptionMacrosUnitTests::testCHECK_HR()
{
    try
    {
        CHECK_HR(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), L"ERROR_NOT_FOUND");
        throw "expected std::exception";
    }
    catch(std::exception& ex)
    {
        std::cout << std::endl << ex.what();
        Assert::IsTrue(0 == strcmp(ex.what(), "0x80070490 - ERROR_NOT_FOUND: Element not found."));
    }
}

void ExceptionMacrosUnitTests::testCHECK_HR_DLL()
{
    try
    {
        CHECK_HR_DLL(INET_E_SECURITY_PROBLEM, L"INET_E_SECURITY_PROBLEM", L"urlmon.dll");
        throw "expected std::exception";
    }
    catch(std::exception& ex)
    {
        std::cout << std::endl << ex.what();
        Assert::IsTrue(0 == strcmp(ex.what(), "0x800c000e - INET_E_SECURITY_PROBLEM: A security problem occurred."));
    }
}
