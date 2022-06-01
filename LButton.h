#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include "LTexture.h"
// trạng thái của game
// trạng thái của chuột
enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

enum Status {
	MAIN_MENU = 0,
	GAME_PLAY = 1,
    GAME_PLAY2 = 2,
    GAME_PLAY3=3,
    GAME_PLAY4=4,
    GAME_PLAY5=5,
    ABOUT=6,
    SOUND=7,
	WIN = 8,
	LOSE = 9,
	RESUME = 10,
    PAUSE =11,
    RESTART = 12,
	EXIT = 13,
    TOTAL_STATUS = 14
};


//Button constants- các kích thước của button và tất cả trạng thái của button đó
const int BUTTON_WIDTH = 179;
const int BUTTON_HEIGHT = 71;
const int TOTAL_BUTTONS = 4;

//Button constants- các kích thước của button loại 2 ( bé hơn) và tất cả trạng thái của button đó
const int BUTTON_WIDTH1 = 40;
const int BUTTON_HEIGHT1 = 40;
const int TOTAL_BUTTONS1 = 4;

// kích thước của loại button loại 3 có thể thay đổi trạng thái on(off)- như button bật tắt âm thanh
const int BUTTON_WIDTH2 = 179;
const int BUTTON_HEIGHT2 = 71;
const int TOTAL_BUTTONS2 = 4;
 
// dành cho  các button lớn và chỉ có 1 chức năng ấn vào và 4 trạng thái ( không thay đổi nôi dung khi click vào)
class LButton
{
    public:
        //Initializes internal variables
        LButton();

        //Sets top left position
        void setPosition( int x, int y );

        //Handles mouse event
        void handleEvent( SDL_Event* e );
    
        //Shows button sprite
        void render(SDL_Renderer*& gRenderer);

		void set_texture(std::string s,const int &n,SDL_Renderer*& gRenderer);

		void freeB();

		LButtonSprite getStatus();

		void freeStatus();

    private:
        //Top left position
        SDL_Point mPosition;

        //Currently used global sprite
        LButtonSprite mCurrentSprite;
		// 2 trang thái của Button	
		LTexture texture[4];
};


///============================xây dựng lớp Button 2 dành cho các nút bé hơn như back và pause 

// build class button1==========================================================
class LButton1
{
    public:
        //Initializes internal variables
        LButton1();

        //Sets top left position
        void setPosition( int x, int y );

        //Handles mouse event
        void handleEvent( SDL_Event* e );
    
        //Shows button sprite
        void render(SDL_Renderer*& gRenderer);

		void set_texture(std::string s,const int &n,SDL_Renderer*& gRenderer);

		void freeB();

		LButtonSprite getStatus();

		void freeStatus();


    private:
        //Top left position
        SDL_Point mPosition;

        //Currently used global sprite
        LButtonSprite mCurrentSprite;
		// 2 trang thái của Button	
		LTexture texture[4];
};



 


//=========================xây dựng lớp Button2 giúp dành cho các nút lớn và có thể thay đổi nội dung khi click vào ( giống như bật tắt công tắc)====

class LButton2
{
    private:
        //Top left position
        SDL_Point mPosition;

        //Currently used global sprite
        LButtonSprite mCurrentSprite;
		// 2 trang thái của Button	
		LTexture texture[4];

        bool on;
    public:
        //Initializes internal variables
        LButton2();

        //Sets top left position
        void setPosition( int x, int y );

        //Handles mouse event
        void handleEvent( SDL_Event* e );
        void update_Status();

        //Shows button sprite
        void render(SDL_Renderer*& gRenderer);

		void set_texture(std::string s,const int &n,SDL_Renderer*& gRenderer);

		void freeB();

		LButtonSprite getStatus();

		void freeStatus();

		bool get_on();

		void set_on(bool b);

};




