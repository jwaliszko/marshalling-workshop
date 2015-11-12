#include "CPPServer.h"
#include <iostream>
#include <process.h>
#include <windows.h>

using namespace std;

void hibernate(void *param);

CPPServer::CPPServer()
{
    _delay = 0;
    _input = nullptr;
}

void CPPServer::SetDelay(int delay)
{
    cout << "SetDelay() was called" << endl;
    cout << "The value is " << delay << endl;

    _delay = delay;
}

void CPPServer::SetInput(char* input)
{
    cout << "SetInput() was called" << endl;
    cout << "The value is " << input << endl;

    auto length = strlen(input) + 1;
    _input = new char[length];
    strcpy_s(_input, length, input);
}

void CPPServer::ReturnStringAsync(EventCallback callback)
{
    cout << "CPPServer::ReturnStringAsync() starts" << endl;

    auto arg = static_cast<Load*>(malloc(sizeof(Load)));
    arg->delay = _delay;

    auto length = strlen(_input) + 1;
    arg->input = new char[length];
    strcpy_s(arg->input, length, _input);

    arg->callback = callback;

    cout << "thread starts" << endl;
    _beginthread(hibernate, 0, static_cast<void*>(arg));
    cout << "CPPServer::ReturnStringAsync() ends" << endl;
}

void hibernate(void *param)
{    
    auto args = static_cast<Load*>(param);   

    cout << "I/O long running simulation starts" << endl;
    Sleep(args->delay);
    cout << "I/O long running simulation ends" << endl;

    auto callback = static_cast<EventCallback>(args->callback);
    callback(args->input);
        
    cout << "thread ends" << endl;
    _endthread();    
}

CPPServer::~CPPServer()
{
}