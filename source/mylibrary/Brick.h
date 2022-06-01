// khởi tạo class brick để chơi tạo ra các viên gạch
class Brick{
	public:

		static const int BRICK_WIDTH = 50;
		static const int BRICK_HEIGHT = 22;

		static const int BRICK_VEL = 0;

		Brick();

		void handleEventBrick( SDL_Event& e );

		void moveB ();

		void renderB(char color);

		int getPosXB();
		int getPosYB();
		int getVelXB();
		int getVelYB();
		
		void free();

		Brick setBrick_mPosXB(int x);

		Brick setBrick(int x, int y, int velx, int vely);


	private:

		int mPosXB, mPosYB;

		int mVelXB, mVelYB;
		
		LTexture gBrick_Texture[ TOTAL_COLOR_BRICK];

};

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

void Brick::renderB(char color){
	switch (color){
		case 'r':
			gBricksTexture[RED].render(mPosXB,mPosYB);
			break;
		case 'b':
			gBricksTexture[BLUE].render(mPosXB,mPosYB);
			break;
		case 'g':
			gBricksTexture[GREEN].render(mPosXB,mPosYB);
			break;
		case 'd':
			gBricksTexture[DARK_GREEN].render(mPosXB,mPosYB);
			break;
		case 'i':
			gBricksTexture[INDIGO].render(mPosXB,mPosYB);
			break;
		case 'o':
			gBricksTexture[ORANGE].render(mPosXB,mPosYB);
			break;
		case 'p':
			gBricksTexture[PINK].render(mPosXB,mPosYB);
			break;
		case 's':
			gBricksTexture[SOLID].render(mPosXB,mPosYB);
			break;
		case 'v':
			gBricksTexture[VIOLET].render(mPosXB,mPosYB);
			break;
		case 'y' :
			gBricksTexture[YELLOW].render(mPosXB,mPosYB);
			break;
	}
}
void Brick::free(){
	gBricksTexture[BLUE].free();
	gBricksTexture[RED].free();
	gBricksTexture[GREEN].free();
	gBricksTexture[DARK_GREEN].free();
	gBricksTexture[INDIGO].free();
	gBricksTexture[ORANGE].free();
	gBricksTexture[PINK].free();
	gBricksTexture[SOLID].free();
	gBricksTexture[VIOLET].free();
	gBricksTexture[YELLOW].free();
}