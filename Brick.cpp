#include "Brick.h"

///== các hàm thành viên thuộc class này
Brick::Brick(){
	mPosXB=-100;
	mPosYB=-100;
	mVelXB=-100;
	mVelYB=-100;
}

int Brick::getPosXB(){
	return mPosXB;
}
int Brick::getPosYB(){
	return mPosYB;
}
int Brick::getVelXB(){
	return mVelXB;
}
int Brick::getVelYB(){
	return mVelYB;
}

Brick Brick::setBrick(int x, int y, int velx, int vely){
	mPosXB=x;
	mPosYB=y;
	mVelXB=velx;
	mVelYB=vely;
    return *this;
}
Brick Brick::setBrick_mPosXB(int x){
    mPosXB=x;
    return *this;
}

void Brick::renderB(char color,LTexture gBricksTexture[10],SDL_Renderer*& gRenderer){
	switch (color){
		case 'r':
			gBricksTexture[RED].render(mPosXB,mPosYB,gRenderer);
			break;
		case 'b':
			gBricksTexture[BLUE].render(mPosXB,mPosYB,gRenderer);
			break;
		case 'g':
			gBricksTexture[GREEN].render(mPosXB,mPosYB,gRenderer);
			break;
		case 'd':
			gBricksTexture[DARK_GREEN].render(mPosXB,mPosYB,gRenderer);
			break;
		case 'i':
			gBricksTexture[INDIGO].render(mPosXB,mPosYB,gRenderer);
			break;
		case 'o':
			gBricksTexture[ORANGE].render(mPosXB,mPosYB,gRenderer);
			break;
		case 'p':
			gBricksTexture[PINK].render(mPosXB,mPosYB,gRenderer);
			break;
		case 's':
			gBricksTexture[SOLID].render(mPosXB,mPosYB,gRenderer);
			break;
		case 'v':
			gBricksTexture[VIOLET].render(mPosXB,mPosYB,gRenderer);
			break;
		case 'y' :
			gBricksTexture[YELLOW].render(mPosXB,mPosYB,gRenderer);
			break;
	}
}
