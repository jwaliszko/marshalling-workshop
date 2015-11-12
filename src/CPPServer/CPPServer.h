#pragma once

#ifdef CPPSERVER_EXPORTS
    #define CPPSERVER_API __declspec(dllexport)
#else
    #define CPPSERVER_API __declspec(dllimport)
#endif

typedef void(__stdcall* EventCallback)(char*);
typedef struct {
    int delay;
    char* input;
    EventCallback callback;
}Load;

class CPPSERVER_API CPPServer
{
public:
    CPPServer();
    ~CPPServer();

    void SetDelay(int delay);
    void SetInput(char* input);
    void ReturnStringAsync(EventCallback callback);
private:
    int _delay;
    char* _input;
};
