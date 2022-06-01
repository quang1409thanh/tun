
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include "LTexture.h"

// // số màu của viên gạch
// const int TOTAL_COLOR_BRICK = 10;

// số màu của viên gạch
enum Color_Bick {
    RED=0,
    BLUE=1,
    GREEN=2,
    DARK_GREEN=3,
    INDIGO=4,
    ORANGE=5,
    PINK=6,
    SOLID=7,
    VIOLET=8,
    YELLOW=9,
    TOTAL=10
};
// khởi tạo class brick để chơi tạo ra các viên gạch
class Brick{
	public:

		static const int BRICK_WIDTH = 50;
		static const int BRICK_HEIGHT = 22;

		static const int BRICK_VEL = 0;

		Brick();

		void handleEventBrick( SDL_Event& e );

		void moveB ();

		void renderB(char color,LTexture gBricksTexture[ 10],SDL_Renderer*& gRenderer);

		int getPosXB();
		int getPosYB();
		int getVelXB();
		int getVelYB();
		
		void free(LTexture gBricksTexture[10]);

		Brick setBrick_mPosXB(int x);

		Brick setBrick(int x, int y, int velx, int vely);


	private:

		int mPosXB, mPosYB;

		int mVelXB, mVelYB;
		
		LTexture gBrick_Texture[ 10];

};
