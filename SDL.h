#ifndef SDL__h
#define SDL__h

#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "wrapped.h"

bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer);
void waitUntilKeyPressed();
void close(SDL_Window* gWindow, SDL_Renderer* gRenderer,LTexture gCrtTexture, LTexture gOJ1Texture, LTexture gBGTexture,SDL_Texture* gGO);

#endif

