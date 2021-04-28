#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "SDL.h"
#include "wrapped.h"
#include "Bullet.h"

BL::BL()
{
    BL_PosX = 0;
    BL_PosY = 0;
}

void BL::renderBL(SDL_Renderer* gRenderer)
{
	gBLTexture.render( BL_PosX, BL_PosY , gRenderer);
}

void BL::renderBLLeft(SDL_Renderer* gRenderer)
{
    gBLLeftTexture.render( BL_PosX, BL_PosY , gRenderer);
}

void BL::renderBLRight(SDL_Renderer* gRenderer)
{
    gBLRightTexture.render( BL_PosX, BL_PosY , gRenderer);
}


bool BL::loadMediaCrtBL(SDL_Renderer* gRenderer)
{
	if( !gBLTexture.loadFromFile( "dan.png",gRenderer ) ) return false;
	return true;
}

bool BL::loadMediaBossBLLeft(SDL_Renderer* gRenderer)
{
	if( !gBLLeftTexture.loadFromFile( "mons2bulletleft.png",gRenderer ) ) return false;
	return true;
}

bool BL::loadMediaBossBLRight(SDL_Renderer* gRenderer)
{
	if( !gBLRightTexture.loadFromFile( "mons2bulletright.png",gRenderer ) ) return false;
	return true;
}
