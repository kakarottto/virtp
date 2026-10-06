#include <window.h>
#include <iostream>
Window::Window() : window(nullptr), renderer(nullptr) {}
Window::~Window()
{
	if(canDestroy)
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
}
Window::Window(SDL_Window* window, SDL_Renderer* renderer) : window(window), renderer(renderer)
{
	state = (window==nullptr || renderer==nullptr) ? WindowState::Empty : WindowState::Ready; 
}

void Window::CreateDefault(const char* title, int width, int height)
{
	window = SDL_CreateWindow(title,width,height,0);
	renderer = SDL_CreateRenderer(window,NULL);
	state = WindowState::Ready;
}

void Window::Copy(Window* w)
{
	SDL_WindowFlags flags = SDL_GetWindowFlags(w->window);
	int width, height;
	SDL_GetWindowSize(w->window,&width,&height);
	char* title = (char*)SDL_GetWindowTitle(w->window);
	window = SDL_CreateWindow(title,width,height,flags);
	//create SDL_Renderer
	renderer = SDL_CreateRenderer(window,SDL_GetRendererName(w->renderer));
	SDL_GetRenderOutputSize(w->renderer,&width,&height);
	SDL_Surface* surface = SDL_RenderReadPixels(w->renderer,NULL);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FRect dest = {0,0,(float)width,(float)height};
	SDL_RenderTexture(renderer,texture,NULL,&dest);
	state = w->state;
	canDestroy = w->canDestroy;
}
	
SDL_Window* Window::GetSDLWindow(){ return window; }
SDL_Renderer* Window::GetSDLRenderer(){ return renderer; }
void Window::SetSDLWindow(SDL_Window* window, bool canDestroy=false){
	this->window = window;
	this->canDestroy = canDestroy; 
}
void Window::SetSDLRenderer(SDL_Renderer* renderer){ this->renderer = renderer; }

SDL_WindowID Window::GetID()
{
	return SDL_GetWindowID(window);
}

WindowState Window::GetState()
{
	return state;
}

/*void Window::SetState(WindowState state)
{
this->state = state;
}*/

bool Window::CanDestroy()
{
	return canDestroy;
}
void Window::print()
{
	std::cout<< "window: "<<((window==nullptr) ? "nullptr" : "evaluated") << "\n"
	<< "reunderer: "<< (( renderer==nullptr) ? "nullptr" : "evaluated") << "\n"
	<< "state: ";

	switch(state)
	{
	case WindowState::Active:
	case WindowState::Ready:
		std::cout<<"ok\n";
		break;
	default:
		std::cout<<"issue\n";
	}
	std::cout<<"canDestroy: "<< ((canDestroy) ? "yes" : "no") << "\n";
}
