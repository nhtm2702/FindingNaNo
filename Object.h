#ifndef OJ__h
#define OJ__h

#include <SDL.h>
#include <string>
#include <SDL_image.h>

#include "SDL.h"
#include "wrapped.h"

class OJ1
{
    public:
        LTexture gOJ1Texture;
		static const int OJ1_WIDTH = 38;
		static const int OJ1_HEIGHT = 40;

		OJ1();

		bool loadMediaOJ1(SDL_Renderer* gRenderer);
		void moveOJ1( float timeStep );
		void renderOJ1(SDL_Renderer* gRenderer);
        float OJ1PosX, OJ1PosY;
    private:
		int flag = 0;
		int Max_OJ1PosY = 470;
		int Min_OJ1PosY = 310;
};

class OJ2
{
    public:
        LTexture gOJ2Texture;
		static const int OJ2_WIDTH = 38;
		static const int OJ2_HEIGHT = 40;

		OJ2();

		bool loadMediaOJ2(SDL_Renderer* gRenderer);
		void moveOJ2( float timeStep );
		void renderOJ2(SDL_Renderer* gRenderer);
        float OJ2PosX, OJ2PosY;
        int touch = 0;
    private:
		int flag = 0;
		int Max_OJ2PosY = 290;
		int Min_OJ2PosY = 60;
};

class KEY
{
    public:
        LTexture gKEYTexture;
		static const int KEY_WIDTH = 10;
		static const int KEY_HEIGHT = 32;

		KEY();

		bool loadMediaKEY(SDL_Renderer* gRenderer);
		void moveKEY( float timeStep );
		void renderKEY(SDL_Renderer* gRenderer);
        float KEYPosX, KEYPosY;
        int touch = 0;
    private:
        int Max_KEYPosY = 400;
        int Min_KEYPosY = 360;
		int flag = 0;
};

class OPEN
{
    public:
        LTexture gOPENTexture;
		static const int OPEN_WIDTH = 40;
		static const int OPEN_HEIGHT = 26;

		OPEN();

		bool loadMediaOPEN(SDL_Renderer* gRenderer);
		void moveOPEN( float timeStep );
		void renderOPEN(SDL_Renderer* gRenderer);
        float OPENPosX, OPENPosY;
        int touch = 0;
    private:
        int Max_OPENPosY = 305;
        int Min_OPENPosY = 290;
		int flag = 0;
};


#endif // OJ__h
