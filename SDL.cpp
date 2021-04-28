
#include "SDL.h"
#include "crt.h"
#include "BG.h"
#include "Object.h"
#include "wrapped.h"

bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer)
{
	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow( "NHTM", 100, 100, 600, 605, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				success = false;
			}
			else
			{
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					success = false;
				}
				if( TTF_Init() == -1 )
				{
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					success = false;
				}
			}
		}
	}

	return success;
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void close(SDL_Window* gWindow, SDL_Renderer* gRenderer,LTexture gCrtTexture, LTexture gOJ1Texture, LTexture gBGTexture,SDL_Texture* gGO)
{
	gCrtTexture.free();
    gOJ1Texture.free();
    gBGTexture.free();

	SDL_DestroyTexture( gGO );
	gGO = NULL;

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

