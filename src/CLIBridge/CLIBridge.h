#pragma once

using namespace System;
using namespace System::Threading::Tasks;

// Forward declariation
class CPPServer;
public delegate void EventDelegate(char*);

public ref class CLIBridge
{
public:
    CLIBridge();
    virtual ~CLIBridge();

    void SetDelay(int delay);
    void SetInput(String^ input);
    Task<String^>^ ReturnInputAsync();
private:
    CPPServer* _unmanagedServer; 
    TaskCompletionSource<String^>^ _tcs;

    void ReturnInputCallback(char* output);
};

