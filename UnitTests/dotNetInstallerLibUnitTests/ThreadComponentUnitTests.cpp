#include "StdAfx.h"
#include "ThreadComponentUnitTests.h"

using namespace DVLib::UnitTests;

class ThreadComponentImpl : public ThreadComponent
{
private:
    int m_exitcode;
public:
    ThreadComponentImpl(int exitcode);
    int ExecOnThread() { return m_exitcode; }
};

ThreadComponentImpl::ThreadComponentImpl(int exitcode) 
: m_exitcode(exitcode) 
{ 

}

void ThreadComponentUnitTests::testExec()
{
    ThreadComponentImpl component(0);
    component.Exec();
}

void ThreadComponentUnitTests::testExecWithError()
{
    ThreadComponentImpl component(123);
    try
    {
        component.Exec();
        throw "expected exception";
    }
    catch(std::exception&)
    {
    }
}