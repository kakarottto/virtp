#pragma once
#include <functional>
#include <vector>
#include <window.h>
#include <memory>
//TODO: comment it

enum class AppState {Running, Halted, Closed, Broken, Unknown};
static void DummyFunction(){}
class App
{
public:
	App();
	~App();
	
	void SetInit(std::function<void()> function);
	void SetClose(std::function<void()> function);
	void SetRun(std::function<void()> function);
	//Init+Run
	void SetHalt(std::function<void()> function);
	void SetResume(std::function<void()> function);
	
	void Init();
	void Close();
	void Run();
	void Start();
	void Halt();
	void Resume();
private:
	bool running = false;
	std::vector<std::unique_ptr<Window>> windows;
	AppState state;
	std::function<void()> initFunction;
	std::function<void()> closeFunction;
	std::function<void()> runFunction;
	std::function<void()> haltFunction;
	std::function<void()> resumeFunction;
};
