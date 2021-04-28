#ifndef BL__H_
#define BL__H_

#include <SDL.h>
#include <SDL_image.h>

class BL
{
public:
    LTexture gBLTexture;
    LTexture gBLLeftTexture;
    LTexture gBLRightTexture;
    int BL_PosX, BL_PosY;
    BL();

    bool loadMediaCrtBL(SDL_Renderer* gRenderer);
    bool loadMediaBossBLLeft(SDL_Renderer* gRenderer);
    bool loadMediaBossBLRight(SDL_Renderer* gRenderer);
    void handleEvent(SDL_Event& e);
    void setPosFirst(int x,int y)
    {
        BL_PosX = x;
        BL_PosY = y;
    }
    void move()
    {
        if (setDirection == 0) BL_PosX += 5;
        else if (setDirection == 1) BL_PosX -= 5;
    }
    bool outsideCrt() {return BL_PosX < 0 || BL_PosX > 600;}
    bool outsideminiboss() {return BL_PosX < 0 || BL_PosX > 900;}
    void renderBL(SDL_Renderer* gRenderer);
    void renderBLLeft(SDL_Renderer* gRenderer);
    void renderBLRight(SDL_Renderer* gRenderer);
    int setDirection;
    int flag = 0;
};
#endif
