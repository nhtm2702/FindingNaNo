#ifndef WR__h
#define WR__h

#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "SDL.h"

class LTexture
{
	public:
		LTexture();
		~LTexture();

		bool loadFromFile( std::string path, SDL_Renderer* gRenderer );
		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor,TTF_Font *gFont, SDL_Renderer* gRenderer );
		#endif
		void free();
		void render( int x, int y,SDL_Renderer* gRenderer, SDL_Rect* clip = NULL );

	private:
        SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
};

class LTimer
{
    public:
		LTimer();
		void start();
		void stop();
		void pause();
		void unpause();
		Uint32 getTicks();
		bool isStarted();
		bool isPaused();

    private:
		Uint32 mStartTicks;
		Uint32 mPausedTicks;
		bool mPaused;
		bool mStarted;
};

struct Input
{
    int left;
    int right;
};

bool checkCollision( SDL_Rect a, SDL_Rect b );
bool check(int x,int y, SDL_Rect rect);

#endif // WR__h
