#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include<string>
#include <window.h>
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>

void start()
{

	if(!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		return;
	}
		if(!TTF_Init())
	{
		SDL_Log("TTF_Init failed: %s", SDL_GetError());
	}
	std::string title="example title";
	unsigned int width=800, height = 600;
	//https://wiki.libsdl.org/SDL3/SDL_CreateWindow
	SDL_Window* window=SDL_CreateWindow(title.c_str(),width,height,SDL_WINDOW_BORDERLESS|SDL_WINDOW_MOUSE_FOCUS|SDL_WINDOW_INPUT_FOCUS);
	if(window==nullptr)
	{
		SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
		SDL_Quit();
		return;
	}
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	if(renderer==nullptr)
	{
		SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
	}
	
	SDL_Texture* texture = IMG_LoadTexture(renderer,"./res/example.png");
	if(texture == nullptr)
	{
		SDL_Log("IMG_LoadTexture failed: %s", SDL_GetError());
	}
	
	bool running = true;
	//text logic
	TTF_TextEngine *engine = TTF_CreateRendererTextEngine(renderer);
	if(engine == nullptr)
	{
		SDL_Log("TTF_CreateRendererTextEngine failed: %s", SDL_GetError());
	}
	TTF_Font *font = TTF_OpenFont("./res/test.ttf", 44.0f);
		if(font == nullptr)
	{
		SDL_Log("TTF_OpenFont failed: %s", SDL_GetError());
	}

	TTF_Text *text = TTF_CreateText(engine, font, "FUZ", 0);	SDL_Event event;
		if(text == nullptr)
	{
		SDL_Log("IMG_CreateText failed: %s", SDL_GetError());
	}
	while(running)
	{
		//upadte
		while(SDL_PollEvent(&event))
		{
			if(event.type==SDL_EVENT_QUIT) running = false;
			if(event.type == SDL_EVENT_KEY_DOWN)
			{
				if(event.key.key == SDLK_ESCAPE) running = false;
			}
		}
		
		//draw
		SDL_SetRenderDrawColor(renderer,0,10,0,24);
		SDL_RenderClear(renderer);
		//https://wiki.libsdl.org/SDL3/SDL_RenderTexture
		SDL_FRect dest = {200.0f,100.0f,400.0f,400.0f};
		SDL_FRect src = {100,100,100,100};
		SDL_RenderTexture(renderer,texture,&src,&dest);
		
		SDL_FRect sq = {300.0f,200.0f,200.0f,200.0f};
		SDL_SetRenderDrawColor(renderer,100,0,140,24);
		SDL_RenderFillRect(renderer,&sq);
		TTF_DrawRendererText(text, 350, 250);
		SDL_RenderPresent(renderer);
		
		
	}
	TTF_DestroyText(text);
    TTF_CloseFont(font);
    TTF_DestroyRendererTextEngine(engine);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



void start2()
{
	Window wi;
	wi.CreateDefault("",600,600);
	
	if(!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
	}
	
	bool running = true;
	SDL_Event event;
	SDL_Texture* texture = IMG_LoadTexture(wi.GetSDLRenderer(),"./res/example.png");
	SDL_SetRenderDrawColor(wi.GetSDLRenderer(),0,10,0,255);
	SDL_RenderClear(wi.GetSDLRenderer());
	SDL_FRect dest = {200.0f,100.0f,400.0f,400.0f};
	SDL_FRect src = {100,100,100,100};
	SDL_RenderTexture(wi.GetSDLRenderer(),texture,&src,&dest);
	
	SDL_FRect sq = {300.0f,200.0f,200.0f,200.0f};
	SDL_SetRenderDrawColor(wi.GetSDLRenderer(),100,0,140,255);
	
	SDL_RenderFillRect(wi.GetSDLRenderer(),&sq);
	
	SDL_RenderPresent(wi.GetSDLRenderer());
	Window wi2;
	wi2.Copy(&wi);
	wi2.print();
	int count;
	SDL_Window** windows = SDL_GetWindows(&count);
	std::cout<<count<<"\n";
	SDL_free(windows);
	
	while(running)
	{
		//upadte
		while(SDL_PollEvent(&event))
		{
			if(event.type==SDL_EVENT_QUIT) running = false;
			if(event.type == SDL_EVENT_KEY_DOWN)
			{
				if(event.key.key == SDLK_ESCAPE) running = false;
			}
		}
		
		//draw
		
		SDL_RenderPresent(wi.GetSDLRenderer());
		SDL_RenderPresent(wi2.GetSDLRenderer());
	}
	
	SDL_Quit();
}

int main()
{
		
	start();
	return 0;
}
