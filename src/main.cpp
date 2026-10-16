#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "window.h"
#include "text.h"
#include "fuelo.h"

void start()
{
    FueloData fuelo(42.6977, 23.3219, 5);
    fuelo.Fetch();
    std::vector<GasStation> stations = fuelo.ParseStations();

    if (!SDL_Init(SDL_INIT_VIDEO)) return;
    if (!TTF_Init()) return;

    SDL_Window* window = SDL_CreateWindow("Fuelo Prices", 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    TTF_Font* font = TTF_OpenFont("./res/font.ttf", 20.0f);
    if (!font) {
        SDL_Log("Грешка при зареждане на шрифт: %s", SDL_GetError());
    }

    bool running = true;
    SDL_Event event;
    float scrollOffset = 0.0f;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) running = false;
            if (event.type == SDL_EVENT_MOUSE_WHEEL)
			{
				scrollOffset += event.wheel.y * 25.0f; 

				if (scrollOffset > 0.0f) {
					scrollOffset = 0.0f;
				}

				float totalContentHeight = stations.size() * 40.0f; 
				float maxScroll = 600.0f - totalContentHeight - 50.0f; 

				if (totalContentHeight > 600.0f) {
					if (scrollOffset < maxScroll) {
						scrollOffset = maxScroll;
					}
				} else {
					scrollOffset = 0.0f;
				}
			}
        }

        // Изчистване на фона
        SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
        SDL_RenderClear(renderer);

        float yPos = 30.0f + scrollOffset;
        SDL_Color textColor = { 255, 255, 255, 255 };

        for (size_t i = 0; i < stations.size(); ++i)
        {
            SDL_FRect cardRect = { 20.0f, yPos - 5.0f, 760.0f, 32.0f };
            SDL_SetRenderDrawColor(renderer, 35, 40, 55, 255);
            SDL_RenderFillRect(renderer, &cardRect);

            std::string line = stations[i].name + " -> " + stations[i].price;

            SDL_Surface* surface = TTF_RenderText_Blended(font, line.c_str(), 0, textColor);
            if (surface)
            {
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (texture)
                {
                    SDL_FRect dstRect = { 30.0f, yPos, (float)surface->w, (float)surface->h };
                    SDL_RenderTexture(renderer, texture, NULL, &dstRect);
                    SDL_DestroyTexture(texture);
                }
                SDL_DestroySurface(surface);
            }

            yPos += 40.0f; 
        }

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main()
{
    start();
    return 0;
}