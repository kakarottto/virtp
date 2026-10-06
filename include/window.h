#pragma once
#include<SDL3/SDL.h>
#include <functional>
//TODO: comment it
/*
<Summary> The state of the Window class</Summary>
<state name="Active"> The window is actively working </state>
<state name="Ready"> The window is initialized and ready to run </state>
<state name="Broken"> The initialization failed </state>
<state name="Empty"> Cleared or uninitialized is the object </state>
<state name="Unknown"> Unknown </state>
*/
enum class WindowState {Active, Ready, Broken, Empty, Unknown};

/*
<Summary> Window class to handle SDL Windows nicely </Summary>
<var type="SDL_Window*", "name="window"> The window handled by SDL </var>
<var type="SDL_Renderer*", name="renderer"> renderer to draw to window handled by SDL </var>
<var type="WindowState", name="state"> The state of the window </var>
<var type="bool", name="canDestroy">
Determining the destruction of the SDL objects. Useful when calling the copy constructor.
</var>

*/
class Window
{
public:
	Window();
	~Window();
	Window(SDL_Window* window, SDL_Renderer* renderer);	
	void CreateDefault(const char* title, int width, int height);
	void Copy(Window* w);
	SDL_Window* GetSDLWindow();
	SDL_Renderer* GetSDLRenderer();
	void SetSDLWindow(SDL_Window* window,bool canDestroy);
	void SetSDLRenderer(SDL_Renderer* renderer);
	SDL_WindowID GetID();
	
	WindowState GetState();
	//void SetState(WindowState state);
	bool CanDestroy();
	void print();
	
	
	
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	WindowState state = WindowState::Empty;
	bool canDestroy = true;
};
