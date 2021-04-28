#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "SDL.h"
#include "wrapped.h"
#include "Object.h"

OJ1::OJ1()
{
    OJ1PosX = 701;
    OJ1PosY = 310;
}

void OJ1::moveOJ1( float timeStep )
{
    if (OJ1PosY <= Min_OJ1PosY) flag = 0;
    if ( (flag == 0) )
    {
        OJ1PosY += 40 * timeStep;
    }
    if ( OJ1PosY >= Max_OJ1PosY) flag = 1;
    if ( (flag == 1) )
    {
        OJ1PosY -= 40 * timeStep;
    }
}

void OJ1::renderOJ1(SDL_Renderer* gRenderer)
{
	gOJ1Texture.render( (int)OJ1PosX, (int)OJ1PosY , gRenderer);
}

bool OJ1::loadMediaOJ1(SDL_Renderer* gRenderer)
{
	if( !gOJ1Texture.loadFromFile( "b1.png",gRenderer ) ) return false;
	return true;
}

OJ2::OJ2()
{
    OJ2PosX = 870;
    OJ2PosY = 290;
}

void OJ2::moveOJ2( float timeStep )
{
    if (OJ2PosY <= Min_OJ2PosY) flag = 0;
    if ( (flag == 0) )
    {
        OJ2PosY += 40 * timeStep;
    }
    if ( OJ2PosY >= Max_OJ2PosY) flag = 1;
    if ( (flag == 1) )
    {
        OJ2PosY -= 40 * timeStep;
    }
}

void OJ2::renderOJ2(SDL_Renderer* gRenderer)
{
	if (touch == 1) gOJ2Texture.render( (int)OJ2PosX, (int)OJ2PosY , gRenderer);
}

bool OJ2::loadMediaOJ2(SDL_Renderer* gRenderer)
{
	if( !gOJ2Texture.loadFromFile( "b2.png",gRenderer ) ) return false;
	return true;
}

KEY::KEY()
{
    KEYPosX = 370;
    KEYPosY = 360;
}

void KEY::moveKEY( float timeStep )
{
    if (KEYPosY <= Min_KEYPosY) flag = 0;
    if ( (flag == 0) )
    {
        KEYPosY += 30 * timeStep;
    }
    if ( KEYPosY >= Max_KEYPosY) flag = 1;
    if ( (flag == 1) )
    {
        KEYPosY -= 30 * timeStep;
    }
}

void KEY::renderKEY(SDL_Renderer* gRenderer)
{
	if (touch == 0) gKEYTexture.render( (int)KEYPosX, (int)KEYPosY , gRenderer);
}

bool KEY::loadMediaKEY(SDL_Renderer* gRenderer)
{
	if( !gKEYTexture.loadFromFile( "key.png",gRenderer ) ) return false;
	return true;
}

OPEN::OPEN()
{
    OPENPosX = 1030;
    OPENPosY = 305;
}

void OPEN::moveOPEN( float timeStep )
{
    if (OPENPosY <= Min_OPENPosY) flag = 0;
    if ( (flag == 0) )
    {
        OPENPosY += 20 * timeStep;
    }
    if ( OPENPosY >= Max_OPENPosY) flag = 1;
    if ( (flag == 1) )
    {
        OPENPosY -= 20 * timeStep;
    }
}

void OPEN::renderOPEN(SDL_Renderer* gRenderer)
{
	if (touch == 0) gOPENTexture.render( (int)OPENPosX, (int)OPENPosY , gRenderer);
}

bool OPEN::loadMediaOPEN(SDL_Renderer* gRenderer)
{
	if( !gOPENTexture.loadFromFile( "open.png",gRenderer ) ) return false;
	return true;
}
