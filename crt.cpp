#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;
#include "SDL.h"
#include "wrapped.h"
#include "crt.h"
#include "BG.h"
#include "Object.h"
#include "Bullet.h"
#include "key.h"
#include "boss.h"

BG bg;
OJ1 oj1;
OJ2 oj2;
KEY key;
OPEN open;
BOSS boss;
BulletBOSS BLB;
MINIBOSS miniboss;
LTimer stepTimer;

Crt::Crt()
{
    CrtPosX = 0;
    CrtPosY = 0;

    bg.BGPosX = 0;
    bg.BGPosY = 0;

    oj1.OJ1PosX = 701;
    oj1.OJ1PosY = 310;

    oj2.OJ2PosX = 870;
    oj2.OJ2PosY = 290;

    key.KEYPosX = 370;
    key.KEYPosY = 360;

    open.OPENPosX = 1030;
    open.OPENPosY = 305;

    boss.BOSSPosX = 960;
    boss.BOSSPosY = 280;

    BLB.BOSSBLPosX = 0;
    BLB.BOSSBLPosY = 0;

    miniboss.MINIBOSSPosX = 550;
    miniboss.MINIBOSSPosY = 490;

    frame = 0;
    status = move_right;
    input_type.left = 0;
    input_type.right = 0;

    MINIBOSS* h = new MINIBOSS[4];
    for (int i=0;i<4;i++)
    {
        MINIBOSS* temp = (h + i);
        temp->Max_MINIBOSSPosX = oj1.OJ1PosX - 150;
        temp->Min_MINIBOSSPosX = temp->Max_MINIBOSSPosX - 190;
        if (i == 0)
        {
            temp->flag = 1;
            temp->setPosFirst(temp->Max_MINIBOSSPosX, 490);
        }
        else if (i == 1)
            {
                temp->flag = 0;
                temp->setPosFirst(temp->Min_MINIBOSSPosX, 490);
            }
        else if (i == 2)
            {
                temp->flag = 1;
                temp->setPosFirst(temp->Max_MINIBOSSPosX, 380);
            }
        else if (i == 3)
            {
                temp->flag = 0;
                temp->setPosFirst(temp->Min_MINIBOSSPosX, 380);
            }
        BL* bl = new BL();
        temp->bulletMINIBOSS(bl);
        minibosses.push_back(temp);
    }
}

bool Crt::checkoutside()
{
    if ( (input_type.left == 1) && (key.KEYPosX - CrtPosX >= 170) && (CrtPosY == 470) ) return true;
    if ( (input_type.right == 1) && (CrtPosX - key.KEYPosX >= 450) && (CrtPosY == 470) ) return true;
    return false;
}

bool Crt::chamdich()
{
    if ( (CrtPosY == 20) && (bg.BGPosX == -474)) return true;
    return false;
}
bool Crt::loadMedia( SDL_Renderer* gRenderer)
{
	if( !gRightTexture.loadFromFile( "walkright.png",gRenderer ) ) return false;
	else if( !gLeftTexture.loadFromFile( "walkleft.png",gRenderer ) ) return false;
    else set_clips();
    if ( !bg.loadMediaBG(gRenderer) ) return false;
    if ( !oj1.loadMediaOJ1(gRenderer) ) return false;
    if ( !oj2.loadMediaOJ2(gRenderer) ) return false;
    if ( !key.loadMediaKEY(gRenderer) ) return false;
    if ( !open.loadMediaOPEN(gRenderer) ) return false;
    if ( !boss.loadMediaBOSS(gRenderer) ) return false;
    if ( !BLB.loadMediaBossBL(gRenderer) ) return false;
	return true;
}

void Crt::handleEvent(SDL_Event& e)
{
	if( e.type == SDL_KEYDOWN )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT:
                {
                    status = move_left;
                    input_type.left = 1;
                    input_type.right = 0;
                    break;
                }
            case SDLK_RIGHT:
                {
                    status = move_right;
                    input_type.right = 1;
                    input_type.left = 0;
                    break;
                }
            default: break;
        }
    }
    else if( e.type == SDL_KEYUP )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT: input_type.left = 0; break;
            case SDLK_RIGHT: input_type.right = 0; break;
            default: break;
        }
    }
    if ( e.type == SDL_MOUSEBUTTONDOWN )
    {
        if ( (e.button.button == SDL_BUTTON_LEFT) )
        {
            BL* h = new BL();
            if (status == move_left)
            {
                h->setDirection = 1;
                h->setPosFirst(CrtPosX - 30, CrtPosY + 30);
            }
            else if (status == move_right)
            {
                h->setDirection = 0;
                h->setPosFirst(CrtPosX + 40, CrtPosY + 30);
            }
            BLs.push_back(h);
        }
    }
}

void Crt::Drop(SDL_Renderer* gRenderer,LTexture &gTimeTextTexture,LTexture &gMangTextTexture)
{
    while ( ((CrtPosX == 0) && (CrtPosY <= 185))
            || ( (abs(oj1.OJ1PosX - CrtPosX) >= 20) && (abs(oj1.OJ1PosX - CrtPosX) <= 30) && (CrtPosY >= 290) && (CrtPosY <= 465) && (input_type.left == 1))
            || ( (abs(oj1.OJ1PosX - CrtPosX) >= 20) && (abs(oj1.OJ1PosX - CrtPosX) <= 30) && (CrtPosY >= 360) && (CrtPosY <= 465))
            || ( (abs(oj1.OJ1PosX - CrtPosX) >= 370) && (abs(oj1.OJ1PosX - CrtPosX) <= 400) && (CrtPosY >= 360) && (CrtPosY <= 465) && (input_type.left == 1))
            || ( (abs(oj2.OJ2PosX - CrtPosX) >= 20) && (abs(oj2.OJ2PosX - CrtPosX) <= 50) && (CrtPosY <= 285) && (input_type.left == 1))
            || ( (abs(oj2.OJ2PosX - CrtPosX) >= 20) && (abs(oj2.OJ2PosX - CrtPosX) <= 50) && (CrtPosY > 20) && (CrtPosY <= 285) && (input_type.right == 1))
            || ( (CrtPosX == 260) && (CrtPosY >= 185) && (CrtPosY <= 465) && (oj1.OJ1PosX == 701)) )
    {
        CrtPosY += 5;
        Render(gRenderer,gTimeTextTexture,gMangTextTexture);
        SDL_Delay(5);
    }
}

void Crt::moveCrt()
{
    if (input_type.left == 1)
    {
        CrtPosX -= 2.5;
        if ((CrtPosX < 300) && (bg.BGPosX < 0 ) )
        {
            bg.BGPosX += 6;
            oj1.OJ1PosX +=6;
            oj2.OJ2PosX +=6;
            key.KEYPosX +=6;
            open.OPENPosX += 6;
            boss.BOSSPosX += 6;
            BLB.BOSSBLPosX += 6;
            for (vector<MINIBOSS*>::iterator it = minibosses.begin();it != minibosses.end(); )
            {
                MINIBOSS * h = *it;
                h->MINIBOSSPosX +=6;
                h->Min_MINIBOSSPosX += 6;
                h->Max_MINIBOSSPosX +=6;
                ++it;
            }
        }
        }
    if (input_type.right == 1)
    {
        CrtPosX += 2.5;
        if ((CrtPosX > 300) && (bg.BGPosX > (-1076 + 602)) )
        {
            bg.BGPosX -= 6;
            oj1.OJ1PosX -=6;
            oj2.OJ2PosX -=6;
            key.KEYPosX -=6;
            open.OPENPosX -= 6;
            boss.BOSSPosX -= 6;
            BLB.BOSSBLPosX -= 6;
            for (vector<MINIBOSS*>::iterator it = minibosses.begin();it != minibosses.end(); )
            {
                MINIBOSS * h = *it;
                h->MINIBOSSPosX -=6;
                h->Min_MINIBOSSPosX -= 6;
                h->Max_MINIBOSSPosX -=6;
                ++it;
            }
        }
    }
    //cout << CrtPosX << " " << CrtPosY << " " << bg.BGPosX << " " << oj1.OJ1PosX << endl;
    if ( ( CrtPosX < 0 ) ) CrtPosX += 2.5;
    if ( ( CrtPosX > 560 ) ) CrtPosX -= 2.5;
}

void Crt::Jump(SDL_Renderer* gRenderer,SDL_Event& e,LTexture &gTimeTextTexture,LTexture &gMangTextTexture)
{
    if ( (CrtPosY == 190) || (CrtPosY == 470) || (CrtPosY == 360) || (CrtPosY == 290))
    {
        for (int i=0;i<12;i++)
        {
            CrtPosY -= CRT_JUMP_VEL;
            handleEvent(  e );
            Render(gRenderer,gTimeTextTexture,gMangTextTexture);
            SDL_Delay(5);
        }
    }
    if ( (CrtPosY == 410) && (CrtPosY <= oj1.OJ1PosY) && (abs(oj1.OJ1PosX - CrtPosX) <= 20) ) Render(gRenderer,gTimeTextTexture,gMangTextTexture);
    else if ( (CrtPosY == 230) && (CrtPosY <= oj2.OJ2PosY) && (abs(oj2.OJ2PosX - CrtPosX) <= 20)) Render(gRenderer,gTimeTextTexture,gMangTextTexture);
    else
    {
        for (int i=0;i<12;i++)
        {
            CrtPosY += CRT_JUMP_VEL;
            handleEvent( e );
            Render(gRenderer,gTimeTextTexture,gMangTextTexture);
            SDL_Delay(10);
        }
    }
    while  ( ((CrtPosY <= 410) && (abs(oj1.OJ1PosX - CrtPosX) <= 30))
            || ((CrtPosY <= 230) && (abs(oj2.OJ2PosX - CrtPosX) <= 30)) )
    {
        Render(gRenderer,gTimeTextTexture,gMangTextTexture);
        SDL_Delay(5);
        if ( (CrtPosY <= 410) && ( CrtPosY > 230) ) CrtPosY = oj1.OJ1PosY - 60;
        if ( (CrtPosY <= 230) ) CrtPosY = oj2.OJ2PosY - 60;
        if ( SDL_PollEvent(&e) != 0 &&  ( (e.type == SDL_KEYDOWN ) || (e.type == SDL_KEYUP ) ) )
        {
            handleEvent(  e );
            moveCrt();
        }
    }
    if ( ((abs(oj1.OJ1PosX - CrtPosX) > 20) && (abs(oj1.OJ1PosX - CrtPosX) < 50)) )
    {
        Drop(gRenderer,gTimeTextTexture,gMangTextTexture);
        if ( (CrtPosY < 360) && (input_type.left == 1) ) CrtPosY = 360;
        if ( (CrtPosY > 360) && (CrtPosY < 470)&& (input_type.left == 1)) CrtPosY = 470;
        if ( (CrtPosY < 290) && (input_type.right == 1) ) CrtPosY = 290;
        if ( (CrtPosY < 290) && (input_type.right == 1) ) CrtPosY = 290;
        if ( (CrtPosY > 290) && (input_type.right == 1) ) CrtPosY = 470;
        Render(gRenderer,gTimeTextTexture,gMangTextTexture);
    }
    if ( (abs(oj2.OJ2PosX - CrtPosX) > 20) && (abs(oj2.OJ2PosX - CrtPosX) < 50) )
        {
            Drop(gRenderer,gTimeTextTexture,gMangTextTexture);
            if ( (CrtPosY <= 20) && (input_type.right == 1) ) CrtPosY = 20;
            if ( (CrtPosY > 280) && (CrtPosY < 290) ) CrtPosY = 290;
            Render(gRenderer,gTimeTextTexture,gMangTextTexture);
        }
}

void Crt::renderCrt( SDL_Renderer* gRenderer)
{
    SDL_Rect* currentClip = &frame_clip[ frame / 7 ];
    if (status == move_left) gLeftTexture.render( CrtPosX, CrtPosY,gRenderer, currentClip );
    else gRightTexture.render( CrtPosX, CrtPosY,gRenderer, currentClip );
    if ( (input_type.left == 1) || (input_type.right == 1) )
    {
        frame ++;
    }
    else frame = 0;
    if( frame / 6 >= 6 )
    {
        frame = 0;
    }

}

void Crt::Render(SDL_Renderer* gRenderer,LTexture &gTimeTextTexture,LTexture &gMangTextTexture)
{
    float timeStep = stepTimer.getTicks() / 1000.f;
    oj1.moveOJ1( timeStep );
    oj2.moveOJ2( timeStep );
    key.moveKEY( timeStep );
    open.moveOPEN( timeStep );
    boss.moveBOSS( timeStep );
    stepTimer.start();


    if ( (abs(key.KEYPosX - CrtPosX) <= 5) && (CrtPosY == 360) ) key.touch = 1;
    if ( (abs(open.OPENPosX - CrtPosX) <= 10) && (CrtPosY == 290) && (key.touch == 1)) open.touch = 1;
    if ( (open.touch == 1) ) oj2.touch = 1;
    SDL_RenderClear( gRenderer );

    bg.renderBG( gRenderer);
    oj1.renderOJ1(gRenderer);
    oj2.renderOJ2(gRenderer);
    key.renderKEY(gRenderer);
    open.renderOPEN(gRenderer);
    gTimeTextTexture.render( 0 , 0 ,gRenderer);
    gMangTextTexture.render( 480 , 0 ,gRenderer);
    if (boss.count < 10)
    {
        boss.renderBOSS(gRenderer);
        if (BLB.outside()) BLB.setPosition(boss.BOSSPosX - 10, boss.BOSSPosY + 30);
        BLB.move();
        BLB.renderBLBoss(gRenderer,CrtPosX,CrtPosY,boss.BOSSPosX,boss.BOSSPosY,count);
    }

    for (vector<BL*>::iterator itBL = BLs.begin();itBL != BLs.end(); )
    {
            BL * b = *itBL;
            SDL_Rect mRect;
            mRect.x = boss.BOSSPosX;
            mRect.y = boss.BOSSPosY;
            mRect.w = 47;
            mRect.h = 30;
            SDL_Rect bRect;
            bRect.x = b->BL_PosX;
            bRect.y = b->BL_PosY;
            bRect.w = 16;
            bRect.h = 16;
            bool touch = checkCollision(mRect,bRect);
            if ( (touch) && (boss.count < 10) )
            {
                boss.count ++;
                itBL = BLs.erase(itBL);
                delete b;
            }
           else ++ itBL;
    }
    renderCrt( gRenderer);

    for (vector<BL*>::iterator it = BLs.begin();it != BLs.end(); )
    {
        BL * h = *it;
        if (h != NULL)
        {
        if (h->loadMediaCrtBL(gRenderer))
        {
            h->move();
            h->renderBL(gRenderer);
            if (h->outsideCrt())
            {
                it = BLs.erase(it);
                delete h;
            }
            else ++it;
        }
        }
    }

    for (vector<MINIBOSS*>::iterator it = minibosses.begin();it != minibosses.end(); )
    {
        MINIBOSS * h = *it;
        if (h->loadMediaMINIBOSS(gRenderer))
         {
            h->moveMINIBOSS(timeStep);
            h->renderbullet(gRenderer,CrtPosX,CrtPosY,count);
            h->renderMINIBOSS(gRenderer);
            ++it;
         }
    }
    for (vector<BL*>::iterator itBL = BLs.begin();itBL != BLs.end(); )
    {
            MINIBOSS * h = * minibosses.begin();
            BL * b = *itBL;
            SDL_Rect mRect;
            mRect.x = h->MINIBOSSPosX;
            mRect.y = h->MINIBOSSPosY;
            mRect.w = h->MINIBOSS_WIDTH;
            mRect.h = h->MINIBOSS_HEIGHT;
            SDL_Rect bRect;
            bRect.x = b->BL_PosX;
            bRect.y = b->BL_PosY;
            bRect.w = 16;
            bRect.h = 16;
            bool touch = checkCollision(mRect,bRect);
            if (touch)
            {
                h->count ++;
                itBL = BLs.erase(itBL);
                delete b;
                if (h->count == 3) minibosses.erase(minibosses.begin());
            }
           else ++ itBL;
    }

    SDL_RenderPresent( gRenderer );

}

void Crt::set_clips()
{
        frame_clip[ 0 ].x =   0;
		frame_clip[ 0 ].y =   0;
		frame_clip[ 0 ].w =  43;
		frame_clip[ 0 ].h =  60;

		frame_clip[ 1 ].x =  46;
		frame_clip[ 1 ].y =   0;
		frame_clip[ 1 ].w =  47;
		frame_clip[ 1 ].h =  60;

		frame_clip[ 2 ].x =  93;
		frame_clip[ 2 ].y =   0;
		frame_clip[ 2 ].w =  47;
		frame_clip[ 2 ].h =  60;

		frame_clip[ 3 ].x =  139;
		frame_clip[ 3 ].y =   0;
		frame_clip[ 3 ].w =  47;
		frame_clip[ 3 ].h =  60;

		frame_clip[ 4 ].x = 185;
		frame_clip[ 4 ].y =   0;
		frame_clip[ 4 ].w =  47;
		frame_clip[ 4 ].h =  60;

		frame_clip[ 5 ].x = 233;
		frame_clip[ 5 ].y =   0;
		frame_clip[ 5 ].w =  47;
		frame_clip[ 5 ].h =  60;
}
