#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "SDL.h"
#include "wrapped.h"
#include "boss.h"
#include "Bullet.h"

using namespace std;

BOSS::BOSS()
{
    BOSSPosX = 960;
    BOSSPosY = 280;
    frame = 0;
}

bool BOSS::loadMediaBOSS( SDL_Renderer* gRenderer)
{
    if( !gBOSSTexture.loadFromFile( "mons1.png",gRenderer ) ) return false;
    else set_clips();
    return true;
}

void BOSS::moveBOSS( float timeStep )
{
    if (BOSSPosY <= Min_BOSSPosY) flag = 0;
    if ( (flag == 0) )
    {
        BOSSPosY += 40 * timeStep;
    }
    if ( BOSSPosY >= Max_BOSSPosY) flag = 1;
    if ( (flag == 1) )
    {
        BOSSPosY -= 40 * timeStep;
    }
}

void BOSS::renderBOSS(SDL_Renderer* gRenderer)
{
    SDL_Rect* currentClip = &boss_clip[ frame / 6 ];
    gBOSSTexture.render( (int)BOSSPosX, (int)BOSSPosY , gRenderer, currentClip );
    frame ++;
    if( frame / 6 >= 6 )
    {
        frame = 0;
    }
}


void BOSS::set_clips()
{
        boss_clip[ 0 ].x =   0;
		boss_clip[ 0 ].y =   0;
		boss_clip[ 0 ].w =  47;
		boss_clip[ 0 ].h =  30;

		boss_clip[ 1 ].x =  51;
		boss_clip[ 1 ].y =   0;
		boss_clip[ 1 ].w =  49;
		boss_clip[ 1 ].h =  30;

		boss_clip[ 2 ].x =  99;
		boss_clip[ 2 ].y =   0;
		boss_clip[ 2 ].w =  47;
		boss_clip[ 2 ].h =  30;

		boss_clip[ 3 ].x = 147;
		boss_clip[ 3 ].y =   0;
		boss_clip[ 3 ].w =  43;
		boss_clip[ 3 ].h =  30;

		boss_clip[ 4 ].x = 189;
		boss_clip[ 4 ].y =   0;
		boss_clip[ 4 ].w =  45;
		boss_clip[ 4 ].h =  30;

		boss_clip[ 5 ].x = 235;
		boss_clip[ 5 ].y =   0;
		boss_clip[ 5 ].w =  46;
		boss_clip[ 5 ].h =  30;
}
BulletBOSS :: BulletBOSS()
{
    BOSSBLPosX = 0;
    BOSSBLPosY = 0;
}

void BulletBOSS::renderBLBoss(SDL_Renderer* gRenderer,int x,int y,int a,int b,int &count)
{
    if (flag == 0) gBLBossTexture.render( BOSSBLPosX, BOSSBLPosY , gRenderer);
    SDL_Rect cRect;
    cRect.x = x;
    cRect.y = y;
    cRect.w = 40;
    cRect.h = 40;
    SDL_Rect bRect;
    bRect.x = BOSSBLPosX;
    bRect.y = BOSSBLPosY;
    bRect.w = 9;
    bRect.h = 20;
    bool touch = checkCollision(cRect,bRect);
    if (touch)
        {
            count ++;
            setPosition(a - 20,b + 30);
        }
    SDL_Delay(5);

}

bool BulletBOSS::loadMediaBossBL(SDL_Renderer* gRenderer)
{
	if( !gBLBossTexture.loadFromFile( "mons1bullet.png",gRenderer ) ) return false;
	return true;
}

void BulletBOSS::move()
{
    BOSSBLPosX -= 5;
}

MINIBOSS::MINIBOSS()
{
    MINIBOSSPosX = 550;
    MINIBOSSPosY = 490;
}

bool MINIBOSS::loadMediaMINIBOSS( SDL_Renderer* gRenderer)
{
    if( !gMINIBOSSTexture.loadFromFile( "mons2left.png",gRenderer ) ) return false;
    return true;
}

void MINIBOSS::moveMINIBOSS( float timeStep )
{
    if (MINIBOSSPosX <= Min_MINIBOSSPosX) flag = 0;
    if ( (flag == 0) )
    {
        MINIBOSSPosX += 40 * timeStep;
    }
    if ( MINIBOSSPosX >= Max_MINIBOSSPosX) flag = 1;
    if ( (flag == 1) )
    {
        MINIBOSSPosX -= 40 * timeStep;
    }
}

void MINIBOSS::bulletMINIBOSS(BL* bullet)
{
    if (bullet != NULL)
    {
        BL* h = new BL();
        if (flag == 1)
            {
                h->setDirection = 1;
                h->setPosFirst(MINIBOSSPosX - 30, MINIBOSSPosY + 10);
            }
        else if (flag == 0)
            {
                h->setDirection = 0;
                h->setPosFirst(MINIBOSSPosX + 30, MINIBOSSPosY + 10);
            }
        BLboss.push_back(h);
    }
}

int MINIBOSS::renderbullet(SDL_Renderer* gRenderer,int x, int y,int &count)
{
    for (vector<BL*>::iterator it = BLboss.begin();it != BLboss.end(); )
    {
        BL * h = *it;
        if (h->loadMediaBossBLLeft(gRenderer) && (h->setDirection == 1))
        {
            h->move();
            h->renderBLLeft(gRenderer);
            if (h->outsideminiboss())
            {
                h->setPosFirst(MINIBOSSPosX - 30, MINIBOSSPosY + 10);
            }
            else ++it;
        }
        else if ((h->loadMediaBossBLRight(gRenderer)) && (h->setDirection == 0))
        {
            h->move();
            h->renderBLRight(gRenderer);
            if (h->outsideminiboss())
            {
                h->setPosFirst(MINIBOSSPosX - 30, MINIBOSSPosY + 10);
            }
            else ++it;
        }
        SDL_Rect cRect;
        cRect.x = x;
        cRect.y = y;
        cRect.w = 40;
        cRect.h = 40;
        SDL_Rect bRect;
        bRect.x = h->BL_PosX;
        bRect.y = h->BL_PosY;
        bRect.w = 21;
        bRect.h = 9;
        bool touch = checkCollision(cRect,bRect);
        if (touch)
        {
            count ++;
            h->setPosFirst(MINIBOSSPosX - 30, MINIBOSSPosY + 10);
        }
    }

}

void MINIBOSS::renderMINIBOSS(SDL_Renderer* gRenderer)
{
    gMINIBOSSTexture.render( (int)MINIBOSSPosX, (int)MINIBOSSPosY , gRenderer);
}

