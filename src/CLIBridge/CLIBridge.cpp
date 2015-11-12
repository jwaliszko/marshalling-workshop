#include "CLIBridge.h"
#include "CPPServer.h"

using namespace System::Runtime::InteropServices;	// needed for Marshal
using namespace System::Threading::Tasks;   // needed for Task
using namespace System::Diagnostics;

CLIBridge::CLIBridge()
{
    _unmanagedServer = new CPPServer();
}

void CLIBridge::SetDelay(int delay)
{
    _unmanagedServer->SetDelay(delay);
}

void CLIBridge::SetInput(String^ input)
{
    auto ptrString = Marshal::StringToHGlobalAnsi(input);
    try
    {
        char* pchString = static_cast<char*>(ptrString.ToPointer());
        _unmanagedServer->SetInput(pchString);
    }
    finally
    {
        Marshal::FreeHGlobal(ptrString);
    }
}

Task<String^>^ CLIBridge::ReturnInputAsync()
{
    Debug::WriteLine("CLIBridge::ReturnInputAsync() starts");
    _tcs = gcnew TaskCompletionSource<String^>();  

    // create the delegate from a member function
    auto nativeCallback = gcnew EventDelegate(this, &CLIBridge::ReturnInputCallback);
    // as long as this handle is alive, the GC will not move nor collect the delegate (pointer passed to the native code will not be invalidated)
    auto delegateHandle = GCHandle::Alloc(nativeCallback);
    // get the pointer that can be passed to native code
    auto ptr = Marshal::GetFunctionPointerForDelegate(nativeCallback);
    // convert the pointer to the type required by the native code
    auto theCallback = static_cast<EventCallback>(ptr.ToPointer());

    _unmanagedServer->ReturnStringAsync(theCallback);
    auto result = _tcs->Task;

    Debug::WriteLine("CLIBridge::ReturnInputAsync() ends");

    return result;
}

void CLIBridge::ReturnInputCallback(char* output)
{
    Debug::WriteLine("CLIBridge::ReturnInputCallback() called");
    auto str = Marshal::PtrToStringAnsi(static_cast<IntPtr>(output));
    _tcs->SetResult(str);
}

CLIBridge::~CLIBridge()
{
    delete _unmanagedServer;
    _unmanagedServer = nullptr;

    //if (delegateHandle.IsAllocated)
    //    delegateHandle.Free();
}