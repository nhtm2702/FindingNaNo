#ifndef BOSS__h
#define BOSS__h

#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <vector>

#include "SDL.h"
#include "wrapped.h"
#include "Bullet.h"

class BOSS
{
    public:
        LTexture gBOSSTexture;
        LTexture gBLBossTexture;

		BOSS();

        bool loadMediaBOSS( SDL_Renderer* gRenderer);
        bool loadMediaBossBL(SDL_Renderer* gRenderer);
        void moveBOSS( float timeStep );
		void renderBOSS(SDL_Renderer* gRenderer);
        void set_clips();
        void renderBLBoss(SDL_Renderer* gRenderer);
		float BOSSPosX, BOSSPosY;
		int count;
    private:
        SDL_Rect boss_clip[6];
        int frame = 0;
        int flag = 0;
        int Max_BOSSPosY = 300;
		int Min_BOSSPosY = 280;
};

class BulletBOSS
{
    public:
        LTexture gBLBossTexture;

		BulletBOSS();

        bool loadMediaBossBL(SDL_Renderer* gRenderer);
        void setPosition(int x, int y)
        {
            BOSSBLPosX = x;
            BOSSBLPosY = y;
        }
        void move();
        bool outside() {return BOSSBLPosX <= 0 || BOSSBLPosX > 600;}
        void renderBLBoss(SDL_Renderer* gRenderer,int x,int y,int a,int b,int &count);
        int BOSSBLPosX, BOSSBLPosY;
    private:
        int flag = 0;
};

class MINIBOSS
{
    public:
        LTexture gMINIBOSSTexture;

        static const int MINIBOSS_WIDTH = 40;
		static const int MINIBOSS_HEIGHT = 40;

		MINIBOSS();

		void setPosFirst(int x,int y)
        {
            MINIBOSSPosX = x;
            MINIBOSSPosY = y;
        }
        bool loadMediaMINIBOSS( SDL_Renderer* gRenderer);
        void moveMINIBOSS( float timeStep );
        void bulletMINIBOSS(BL* bullet);
        int renderbullet(SDL_Renderer* gRenderer,int x, int y,int &count);
		void renderMINIBOSS(SDL_Renderer* gRenderer);
		float MINIBOSSPosX, MINIBOSSPosY;
		int Max_MINIBOSSPosX ;
		int Min_MINIBOSSPosX ;
		int count = 0;
        int flag = 0;
        std::vector<BL*> BLboss;
        std::vector<BL*> get_bulletlist() {return BLboss;};
};

#endif
