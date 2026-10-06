#include <app.h>
App::App() : initFunction(DummyFunction), closeFunction(DummyFunction), 
runFunction(DummyFunction), haltFunction(DummyFunction), resumeFunction(DummyFunction)
{}
void App::SetInit(std::function<void()> function)
{
	initFunction = function;
}
void App::SetClose(std::function<void()> function)
{
	closeFunction = function;
}
void App::SetRun(std::function<void()> function)
{
	runFunction = function;
}
void App::SetHalt(std::function<void()> function)
{
	haltFunction = function;
}
void App::SetResume(std::function<void()> function)
{
	resumeFunction = function;
}

void App::Init()
{
	initFunction();
}
void App::Close()
{
	closeFunction();
}
void App::Run()
{
	runFunction();
}
void App::Start()
{
	Init();
	Run();
}
void App::Halt()
{
	haltFunction();
}
void App::Resume()
{
	resumeFunction();
}
