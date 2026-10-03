#include <cstdio>
#include <cstdlib>

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

static const char *MY_COOL_MP3 =
    "./res/Rainbow - I Surrender (Remastered) (SHM-CD).mp3";

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    if ((Mix_Init(MIX_INIT_MP3) & MIX_INIT_MP3) != MIX_INIT_MP3) {
        printf("Mix_Init failed: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }

    if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640) < 0) {
        printf("Mix_OpenAudio failed: %s\n", Mix_GetError());
        Mix_Quit();
        SDL_Quit();
        return 1;
    }

    Mix_Music *music = Mix_LoadMUS(MY_COOL_MP3);

    if (!music) {
        printf("Mix_LoadMUS failed: %s\n", Mix_GetError());
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
        return 1;
    }

    if (Mix_PlayMusic(music, 1) < 0) {
        printf("Mix_PlayMusic failed: %s\n", Mix_GetError());
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
        return 1;
    }

    printf("Playing: %s\n", MY_COOL_MP3);

    while (!SDL_QuitRequested() && Mix_PlayingMusic()) {
        SDL_Delay(250);
    }

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();

    return 0;
}

