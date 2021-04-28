#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "SDL.h"
#include "wrapped.h"
#include "BG.h"
using namespace std;

BG::BG()
{
    BGPosX = 0;
    BGPosY = 0;
}

void BG::renderBG(SDL_Renderer* gRenderer)
{
    gBGTexture.render( BGPosX, BGPosY ,gRenderer);
}

bool BG::loadMediaBG(SDL_Renderer* gRenderer)
{
	if( !gBGTexture.loadFromFile( "BG1.png" ,gRenderer) ) return false;
    return true;
}

GO::GO()
{
    GOPosX = 0;
    GOPosY = 0;
}

void GO::renderGO(SDL_Renderer* gRenderer,SDL_Color &YesColor,SDL_Color &HighColor,SDL_Color &NoColor,TTF_Font *gFont)
{
    gGOTexture.render( GOPosX, GOPosY ,gRenderer);
    menuText.str( "" );
    menuText << "YES";
    if (!gYesTextTexture.loadFromRenderedText( menuText.str().c_str(), YesColor,gFont,gRenderer ))  {};
    gYesTextTexture.render( 100 , 500 ,gRenderer);
    menuText.str( "" );
    menuText << "HIGH SCORE";
    if (!gHIGHTextTexture.loadFromRenderedText( menuText.str().c_str(), HighColor,gFont,gRenderer ))  {};
    gHIGHTextTexture.render( 200 , 500 ,gRenderer);
    menuText.str( "" );
    menuText << "NO";
    if (!gNoTextTexture.loadFromRenderedText( menuText.str().c_str(), NoColor,gFont,gRenderer ))  {};
    gNoTextTexture.render( 400 , 500 ,gRenderer);
}

bool GO::loadMediaGO(SDL_Renderer* gRenderer)
{
	if( !gGOTexture.loadFromFile( "GO.png" ,gRenderer) ) return false;
    return true;
}

START::START()
{
    STARTPosX = 0;
    STARTPosY = 0;
}

void START::renderSTART(SDL_Renderer* gRenderer,SDL_Color &PlayColor,SDL_Color &HighColor,SDL_Color &ExitColor,TTF_Font *gFont)
{
    gSTARTTexture.render( STARTPosX, STARTPosY ,gRenderer);
    menuText.str( "" );
    menuText << "PLAY";
    if (!gPlayTextTexture.loadFromRenderedText( menuText.str().c_str(), PlayColor,gFont,gRenderer ))  {};
    gPlayTextTexture.render( 100 , 140 ,gRenderer);
    menuText.str( "" );
    menuText << "HIGH SCORE";
    if (!gHIGHTextTexture.loadFromRenderedText( menuText.str().c_str(), HighColor,gFont,gRenderer ))  {};
    gHIGHTextTexture.render( 60 , 310 ,gRenderer);
    menuText.str( "" );
    menuText << "EXIT";
    if (!gExitTextTexture.loadFromRenderedText( menuText.str().c_str(), ExitColor,gFont,gRenderer ))  {};
    gExitTextTexture.render( 100 , 470 ,gRenderer);
}

bool START::loadMediaSTART(SDL_Renderer* gRenderer)
{
	if( !gSTARTTexture.loadFromFile( "menu.png" ,gRenderer) ) return false;
    return true;
}

HIGH::HIGH()
{
    HIGHPosX = 0;
    HIGHPosY = 0;
}

void HIGH::renderHIGH(SDL_Renderer* gRenderer,SDL_Color &YourColor,SDL_Color &ExitColor,SDL_Color &BACKColor,TTF_Font *gFont,int &HighScore,int &YourScore)
{
    gHIGHTexture.render( HIGHPosX, HIGHPosY ,gRenderer);
    menuText.str( "" );
    menuText << "HIGH SCORE: " << HighScore;
    if (!gHIGHTextTexture.loadFromRenderedText( menuText.str().c_str(), YourColor,gFont,gRenderer ))  {};
    gHIGHTextTexture.render( 210 , 160 ,gRenderer);
    menuText.str( "" );
    menuText << "YOUR SCORE: " << YourScore;
    if (!gYourTextTexture.loadFromRenderedText( menuText.str().c_str(), YourColor,gFont,gRenderer ))  {};
    gYourTextTexture.render( 210 , 240 ,gRenderer);
    menuText.str( "" );
    menuText << "EXIT";
    if (!gExitTextTexture.loadFromRenderedText( menuText.str().c_str(), ExitColor,gFont,gRenderer ))  {};
    gExitTextTexture.render( 100 , 510 ,gRenderer);
    menuText.str( "" );
    menuText << "BACK";
    if (!gBACKTextTexture.loadFromRenderedText( menuText.str().c_str(), BACKColor,gFont,gRenderer ))  {};
    gBACKTextTexture.render( 420 , 500 ,gRenderer);
}

bool HIGH::loadMediaHIGH(SDL_Renderer* gRenderer)
{
	if( !gHIGHTexture.loadFromFile( "HighScore.png" ,gRenderer) ) return false;
    return true;
}


