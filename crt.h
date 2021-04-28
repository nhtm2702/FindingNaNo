#ifndef character__h
#define character__h

#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <vector>

#include "SDL.h"
#include "wrapped.h"
#include "Bullet.h"
#include "boss.h"

class Crt
{
    public:
        LTexture gLeftTexture;
        LTexture gRightTexture;

		static const int CRT_JUMP_VEL = 5;

		Crt();
        enum move_type
        {
            move_right = 0,
            move_left = 1,
        };

        bool loadMedia( SDL_Renderer* gRenderer);
        void handleEvent(SDL_Event& e );
        void Drop(SDL_Renderer* gRenderer,LTexture &gTimeTextTexture,LTexture &gMangTextTexture);
        void moveCrt();
        void Jump(SDL_Renderer* gRenderer,SDL_Event& e,LTexture &gTimeTextTexture,LTexture &gMangTextTexture);
		void renderCrt(SDL_Renderer* gRenderer);
        void set_clips();
        void Render(SDL_Renderer* gRenderer,LTexture &gTimeTextTexture,LTexture &gMangTextTexture);
		float CrtPosX, CrtPosY;
		int count = 0;
		bool checkoutside();
		bool chamdich();
    private:
        std::vector<BL*> BLs;
        std::vector<MINIBOSS*> minibosses;
        std::vector<BOSS*> bosses;
        SDL_Rect frame_clip[7];
        Input input_type;
        int frame;
        int status;
};



#endif // character__h

