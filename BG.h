#ifndef BG__h
#define BG__h

#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <string>
#include <sstream>

#include "SDL.h"
#include "wrapped.h"

class BG
{
    public:
        LTexture gBGTexture;

		BG();

		void renderBG(SDL_Renderer* gRenderer);
		bool loadMediaBG(SDL_Renderer* gRenderer);
		int BGPosX, BGPosY;
};

class GO
{
    public:
        LTexture gGOTexture;

		GO();

		std::stringstream menuText;
		LTexture gYesTextTexture;
        LTexture gHIGHTextTexture;
        LTexture gNoTextTexture;

		void renderGO(SDL_Renderer* gRenderer,SDL_Color &YesColor,SDL_Color &HighColor,SDL_Color &NoColor,TTF_Font *gFont);
		bool loadMediaGO(SDL_Renderer* gRenderer);
		int GOPosX, GOPosY;
};

class START
{
    public:
        LTexture gSTARTTexture;

		START();

		std::stringstream menuText;
		LTexture gPlayTextTexture;
        LTexture gHIGHTextTexture;
        LTexture gExitTextTexture;

		void renderSTART(SDL_Renderer* gRenderer,SDL_Color &PlayColor,SDL_Color &HighColor,SDL_Color &ExitColor,TTF_Font *gFont);
		bool loadMediaSTART(SDL_Renderer* gRenderer);
		int STARTPosX, STARTPosY;
};

class HIGH
{
    public:
        LTexture gHIGHTexture;

		HIGH();

		std::stringstream menuText;
		LTexture gYourTextTexture;
        LTexture gHIGHTextTexture;
        LTexture gExitTextTexture;
        LTexture gBACKTextTexture;

		void renderHIGH(SDL_Renderer* gRenderer,SDL_Color &YourColor,SDL_Color &ExitColor,SDL_Color &BACKColor,TTF_Font *gFont,int &HighScore,int &YourScore);
		bool loadMediaHIGH(SDL_Renderer* gRenderer);
		int HIGHPosX, HIGHPosY;
};

#endif

