#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <SDL_mixer.h>

#include "SDL.h"
#include "crt.h"
#include "BG.h"
#include "Object.h"
#include "wrapped.h"
#include "Bullet.h"
#include "key.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont = NULL;
LTexture gTimeTextTexture;
LTexture gMangTextTexture;
SDL_Rect Play = {100,150,40,20};
SDL_Rect High1 = {80,300,100,50};
SDL_Rect Exit1 = {100,450,60,50};

SDL_Rect Exit2 = {100,510,60,50};
SDL_Rect BACK = {420,500,60,50};

SDL_Rect Yes = {100,500,40,20};
SDL_Rect High2 = {200,500,140,50};
SDL_Rect No = {400,500,40,20};

GO go;
START start;
HIGH HS;
int HighScore = 0;
int YourScore = 0;

Mix_Chunk *gMusic = NULL;
Mix_Chunk *gMedium = NULL;

bool loadMedia()
{
	bool success = true;

	gFont = TTF_OpenFont( "lazy.ttf", 30 );
	if( gFont == NULL )
	{
		success = false;
	}
	gMusic = Mix_LoadWAV( "music.wav" );
	if( gMusic == NULL )
	{
		success = false;
	}
	gMedium = Mix_LoadWAV( "medium.wav" );
	if( gMedium == NULL )
	{
		success = false;
	}
	return success;
}

int main( int argc, char* args[] )
{
	if( (init(gWindow, gRenderer)) && (loadMedia()) && (go.loadMediaGO(gRenderer)) && (start.loadMediaSTART(gRenderer)))
	{
        SDL_Event e;
        SDL_Event e_menu;
        SDL_Color textColor = { 200, 95, 0, 0 };
        SDL_Color PlayColor = { 200, 95, 0, 0 };
        SDL_Color HighColor = { 200, 95, 0, 0 };
        SDL_Color ExitColor = { 200, 95, 0, 0 };
        SDL_Color YesColor =  { 200, 95, 0, 0 };
        SDL_Color NoColor =   { 200, 95, 0, 0 };
        SDL_Color YourColor =  { 200, 95, 0, 0 };
        SDL_Color BACKColor = { 200, 95, 0, 0 };
        int flag = 0;
        bool success = true;
        int x_menu,y_menu;
        std::stringstream timeText;
        std::stringstream mangText;
        Uint32 startTime = 0;
        start.renderSTART(gRenderer,PlayColor,HighColor,ExitColor,gFont);
        SDL_RenderPresent( gRenderer );
        while (flag < 4)
        {
            Mix_PlayChannel( -1, gMusic, 0 );
            while (flag == 0)
            {
                while (SDL_PollEvent( &e_menu ))
                {
                    switch (e_menu.type)
                    {
                    case SDL_MOUSEMOTION:
                        {
                            x_menu = e_menu.motion.x;
                            y_menu = e_menu.motion.y;
                            if (check(x_menu,y_menu,Play) == true) PlayColor = { 0, 0, 0, 0 };
                            else PlayColor = { 200, 95, 0, 0 };
                            if (check(x_menu,y_menu,High1) == true) HighColor = { 0, 0, 0, 0 };
                            else HighColor = { 200, 95, 0, 0 };
                            if (check(x_menu,y_menu,Exit1) == true) ExitColor = { 0, 0, 0, 0 };
                            else ExitColor = { 200, 95, 0, 0 };
                            start.renderSTART(gRenderer,PlayColor,HighColor,ExitColor,gFont);
                            SDL_RenderPresent( gRenderer );
                        }
                    case SDL_MOUSEBUTTONDOWN:
                        {
                            if (e_menu.button.button == SDL_BUTTON_LEFT)
                            {
                                x_menu = e_menu.button.x;
                                y_menu = e_menu.button.y;
                                if (check(x_menu,y_menu,Play) == true) {flag = 1;break;}
                                if  (check(x_menu,y_menu,High1) == true) {flag = 3;break;}
                                if (check(x_menu,y_menu,Exit1) == true) {flag = 4;break;}
                            }
                        }
                    }
                }
            }
            if (flag == 1)
            {
                Crt crt;
                int Score = 0;
                if ( (crt.loadMedia(gRenderer)) )
                {
                    while( flag == 1 )
                    {
                        crt.Drop(gRenderer,gTimeTextTexture,gMangTextTexture);
                        while ( SDL_PollEvent( &e ) != 0 )
                        {
                        crt.handleEvent(  e );
                        if (e.type == SDL_KEYDOWN)
                        {
                            switch( e.key.keysym.sym )
                            case SDLK_SPACE: crt.Jump(gRenderer, e,gTimeTextTexture,gMangTextTexture);Mix_PlayChannel( -1, gMedium, 0 );break;
                        }
                        }
                        timeText.str( "" );
                        timeText << "Time " << (SDL_GetTicks() - startTime)/60000 << ":" << (SDL_GetTicks() - startTime)/1000;
                        if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor,gFont,gRenderer ) ) {};
                        mangText.str( "" );
                        mangText << "Mang: " << 15 - crt.count;
                        if( !gMangTextTexture.loadFromRenderedText( mangText.str().c_str(), textColor,gFont,gRenderer ) ) {};
                        crt.moveCrt();
                        crt.Render(gRenderer,gTimeTextTexture,gMangTextTexture);
                        SDL_Delay(10);
                        if ( (crt.count == 15) || (crt.checkoutside()) )
                        {
                            flag = 2;
                            break;
                        }
                        if ( crt.chamdich() )
                        {
                            Score = (SDL_GetTicks() - startTime)/10000;
                            if (Score > HighScore) HighScore = Score;
                            flag = 3;
                            YourScore = Score;
                            break;
                        }
                    }
                }
            }
            if (flag == 2)
                {
                    go.renderGO(gRenderer,YesColor,HighColor,NoColor,gFont);
                    SDL_RenderPresent( gRenderer );
                }
            while (flag == 2)
            {
                while (SDL_PollEvent( &e_menu ))
                {
                    switch (e_menu.type)
                    {
                        case SDL_MOUSEMOTION:
                            {
                                x_menu = e_menu.motion.x;
                                y_menu = e_menu.motion.y;
                                if (check(x_menu,y_menu,Yes) == true) YesColor = { 0, 0, 0, 0 };
                                else YesColor = { 200, 95, 0, 0 };
                                if (check(x_menu,y_menu,High2) == true) HighColor = { 0, 0, 0, 0 };
                                else HighColor = { 200, 95, 0, 0 };
                                if (check(x_menu,y_menu,No) == true) NoColor = { 0, 0, 0, 0 };
                                else NoColor = { 200, 95, 0, 0 };
                                go.renderGO(gRenderer,YesColor,HighColor,NoColor,gFont);
                                SDL_RenderPresent( gRenderer );
                            }
                        case SDL_MOUSEBUTTONDOWN:
                            {
                                if (e_menu.button.button == SDL_BUTTON_LEFT)
                                {
                                    x_menu = e_menu.button.x;
                                    y_menu = e_menu.button.y;
                                    if (check(x_menu,y_menu,Yes) == true) {flag = 1;break;}
                                    if (check(x_menu,y_menu,High2) == true) {flag = 3; break;}
                                    if (check(x_menu,y_menu,No) == true) {flag = 4;break;}
                                }
                            }
                        }
                    }
                }

            SDL_RenderPresent( gRenderer );
            if ((flag == 3) && HS.loadMediaHIGH(gRenderer) ) { HS.renderHIGH(gRenderer,YourColor,ExitColor,BACKColor,gFont,HighScore,YourScore);SDL_RenderPresent( gRenderer );}
            while (flag == 3)
            {
                while (SDL_PollEvent( &e_menu ))
                {
                    switch (e_menu.type)
                    {
                    case SDL_MOUSEMOTION:
                        {
                            x_menu = e_menu.motion.x;
                            y_menu = e_menu.motion.y;
                            if (check(x_menu,y_menu,Exit2) == true) ExitColor = { 0, 0, 0, 0 };
                            else ExitColor = { 200, 95, 0, 0 };
                            if (check(x_menu,y_menu,BACK) == true) BACKColor = { 0, 0, 0, 0 };
                            else BACKColor = { 200, 95, 0, 0 };
                            HS.renderHIGH(gRenderer,YourColor,ExitColor,BACKColor,gFont,HighScore,YourScore);
                            SDL_RenderPresent( gRenderer );
                        }
                    case SDL_MOUSEBUTTONDOWN:
                        {
                            if (e_menu.button.button == SDL_BUTTON_LEFT)
                            {
                                x_menu = e_menu.button.x;
                                y_menu = e_menu.button.y;
                                if (check(x_menu,y_menu,BACK) == true) {flag = 0;break;}
                                if (check(x_menu,y_menu,Exit2) == true) {flag = 4;break;}
                            }
                        }
                    }
                }
            }
            SDL_RenderPresent( gRenderer );
        }
	}


	//close(gWindow, gRenderer, gCrtTexture, gOJ1Texture, gBGTexture, gGO);
	return 0;
}

