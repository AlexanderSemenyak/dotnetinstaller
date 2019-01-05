#include "StdAfx.h"
#include "DirectoryUtilUnitTests.h"

using namespace DVLib::UnitTests;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void DirectoryUtilUnitTests::testDirectoryExists()
{
    std::string path = DVLib::GetTemporaryFileNameA();
    std::cout << std::endl << "Temporary filename: " << path;

    std::string directory = DVLib::GetFileDirectoryA(path);
    std::cout << std::endl << "Directory: " << directory;

    Assert::IsTrue(DVLib::DirectoryExists(directory));
    Assert::IsTrue(! DVLib::DirectoryExists(path));		
    DVLib::FileDelete(path);

    Assert::IsTrue(DVLib::DirectoryExists("C:\\"));
    Assert::IsTrue(! DVLib::DirectoryExists(""));

    std::string filename = DVLib::GenerateGUIDStringA();
    std::string guidpath = "C:\\" + filename;
    std::cout << std::endl << "Guid path: " << guidpath;
    Assert::IsTrue(! DVLib::DirectoryExists(guidpath));
}

void DirectoryUtilUnitTests::testDirectoryCreate()
{
    std::wstring root = DVLib::GetTemporaryDirectoryW();
    // check that we can create one level
    std::wstring guid = DVLib::GenerateGUIDStringW();
    std::wstring path1 = root + guid;
    std::wcout << std::endl << L"Creating: " << path1;
    Assert::IsTrue(! DVLib::DirectoryExists(path1));
    std::wstring path1_created = DVLib::DirectoryCreate(path1);
    Assert::IsTrue(DVLib::DirectoryExists(path1));
    Assert::IsTrue(path1 == path1_created);
    // check that we can create two more levels
    std::wstring path2 = path1 + L"\\" + guid;
    std::wstring path3 = path2 + L"\\" + guid;
    std::wcout << std::endl << L"Creating: " << path3;
    Assert::IsTrue(! DVLib::DirectoryExists(path3));
    std::wstring path3_created = DVLib::DirectoryCreate(path3);
    Assert::IsTrue(DVLib::DirectoryExists(path2));
    // the first created directory is path2
    Assert::IsTrue(path2 == path3_created);
    // delete the final result
    DVLib::DirectoryDelete(path1);
}

void DirectoryUtilUnitTests::testDirectoryDelete()
{
    std::wstring root = DVLib::GetTemporaryDirectoryW();
    std::wstring guid = DVLib::GenerateGUIDStringW();
    std::wstring deeppath = root + guid + L"\\" + guid + L"\\" + guid;
    std::wstring newpath = DVLib::DirectoryCreate(deeppath);
    std::wcout << std::endl << "Path: " << newpath;
    // delete files in a directory that doesn't have any files or subdirectories
    DVLib::DirectoryDelete(deeppath, DVLib::DELETE_DIRECTORY_FILES);
    // delete files in a directory that doesn't have any files, but has subdirectories
    DVLib::DirectoryDelete(newpath, DVLib::DELETE_DIRECTORY_FILES);
    Assert::IsTrue(DVLib::DirectoryExists(newpath));
    // create two files
    std::wstring filename1 = newpath + L"\\" + guid + L"-1.tmp";
    std::wstring filename2 = newpath + L"\\" + guid + L"-2.tmp";
    DVLib::FileCreate(filename1);
    DVLib::FileCreate(filename2);
    Assert::IsTrue(DVLib::FileExists(filename1));
    Assert::IsTrue(DVLib::FileExists(filename2));
    // two directories + two files
    std::list<std::wstring> files = DVLib::GetFiles(newpath, L"*.*", DVLib::GET_FILES_ALL);
    Assert::IsTrue(4 == files.size());
    // try to delete effectively nothing, this will fail
    try
    {
        DVLib::DirectoryDelete(newpath, 0);
        throw "DeleteDirectory was expected to throw std::exception";
    }
    catch(std::exception& ex)
    {
        // expected exception, this directory can't be deleted since it has files in it
        std::cout << std::endl << "Expected exception: " << ex.what();
        Assert::IsTrue(DVLib::FileExists(filename1));
        Assert::IsTrue(DVLib::FileExists(filename2));
    }
    // make sure nothing was deleted
    Assert::IsTrue(4 == DVLib::GetFiles(newpath, L"*.*", DVLib::GET_FILES_ALL).size());
    // delete without deleting files, the empty subdirectories will be deleted, leaving us with 2 files
    DVLib::DirectoryDelete(newpath, DVLib::DELETE_DIRECTORY_EMPTY);
    Assert::IsTrue(2 == DVLib::GetFiles(newpath, L"*.*", DVLib::GET_FILES_ALL).size());
    // delete with file and non-empty subdirectories
    DVLib::DirectoryDelete(newpath);
    Assert::IsTrue(! DVLib::FileExists(filename1));
    Assert::IsTrue(! DVLib::FileExists(filename2));
    Assert::IsTrue(! DVLib::DirectoryExists(newpath));
}

void DirectoryUtilUnitTests::testGetFilesRecursive()
{
    std::list<std::wstring> files = DVLib::GetFiles(
        DVLib::GetModuleDirectoryW(), L"*.exe", DVLib::GET_FILES_ALL);

    bool found = false;
    for each (const std::wstring& file in files)
        found |= (file == DVLib::GetModuleFileNameW());

    Assert::IsTrue(found);
}

void DirectoryUtilUnitTests::testGetFilesWithWildcard()
{
    std::list<std::wstring> files = DVLib::GetFiles(
        DVLib::GetModuleDirectoryW() + L"\\*.exe", DVLib::GET_FILES_ALL);

    bool found = false;
    for each (const std::wstring& file in files)
        found |= (file == DVLib::GetModuleFileNameW());

    Assert::IsTrue(found);
}

void DirectoryUtilUnitTests::testGetFilesWithNoWildcard()
{
    std::list<std::wstring> files = DVLib::GetFiles(
        DVLib::GetModuleFileNameW(), DVLib::GET_FILES_FILES);

    Assert::IsTrue(files.size() == 1);
    Assert::IsTrue(* files.begin() == DVLib::GetModuleFileNameW());
}

void DirectoryUtilUnitTests::testGetFilesWithInvalidWildcard()
{
    LPCWSTR file_wildcards[] = 
    {
        { L"x:\\temp\\*\\*.txt" },
        { L"x:\\temp\\?\\*.txt" },
        { L"x:\\temp\\?*\\*.txt" },
        { L"x:\\temp\\*?\\*.txt" },
        { L"?*\\no wildcard here" },
    };

    for (int i = 0; i < ARRAYSIZE(file_wildcards); i++)
    {
        try 
        { 
            DVLib::GetFiles(L"x:\\temp\\*\\*.txt", DVLib::GET_FILES_FILES); 
            throw "expected std::exception";
        } 
        catch(std::exception&) 
        { 
            // expected
        }
    }
}

void DirectoryUtilUnitTests::testDirectoryCreateMultipleSlashes()
{
    std::wstring root = DVLib::GetTemporaryDirectoryW();
    // check that we can create one level
    std::wstring guid = DVLib::GenerateGUIDStringW();
    // append various numbers of backslashes
    std::wstring path_0 = root + guid;
    std::wstring path_1 = root + L"\\" + guid;
    std::wstring path_2 = root + L"\\\\" + guid;
    std::wcout << std::endl << L"Creating: " << path_0;
    Assert::IsTrue(! DVLib::DirectoryExists(path_0));
    Assert::IsTrue(! DVLib::DirectoryExists(path_1));
    Assert::IsTrue(! DVLib::DirectoryExists(path_2));
    Assert::IsTrue(path_0 == DVLib::DirectoryCreate(path_0));
    Assert::IsTrue(DVLib::DirectoryDelete(path_0));
    Assert::IsTrue(path_0 == DVLib::DirectoryCreate(path_1));
    Assert::IsTrue(DVLib::DirectoryDelete(path_1));
    Assert::IsTrue(path_0 == DVLib::DirectoryCreate(path_2));
    Assert::IsTrue(DVLib::DirectoryDelete(path_2));
}

void DirectoryUtilUnitTests::testDirectoryNormalize()
{
    struct TestData
    {
        LPCWSTR path;
        LPCWSTR expected;
    };

    TestData testdata[] = 
    {
        { L"", L"" },
        { L"C:", L"C:" },
        { L"C:\\", L"C:\\" },
        { L"C:\\\\", L"C:\\" },
        { L"C:\\path", L"C:\\path" },
        { L"D:\\\\path", L"D:\\path" },
        { L"E:\\path\\", L"E:\\path\\" },
        { L"C:\\\\path\\\\", L"C:\\path\\" },
        // { L"C:\\\\\\path\\\\", L"C:\\path\\" },
    };

    for (int i = 0; i < ARRAYSIZE(testdata); i++)
    {
        std::wstring normalized_path = DVLib::DirectoryNormalize(testdata[i].path);
        std::wcout << std::endl << L" " << i << L": " << normalized_path;
        Assert::IsTrue(normalized_path == testdata[i].expected);
    }
}
