#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;
#include "LTexture.h"
#include "LTimer.h"
#include "LButton.h"

#include "Brick.h"
//Screen dimension constants
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 600;

// khoảng cách bên trái đến khung trò chơi 
const int SCREEN_LEFT=20;

// khoảng cách bên phải đến khung trò chơi
const int SCREEN_RIGHT=20;

// khoảng cách bên trên đến khung trò chơi
const int SCREEN_TOP=60;

// khoảng cách bên dưới đến khung trò chơi
const int SCREEN_BOTTOM=70;

// số viên gạch của từng level
const int TOTAL_BRICKSLV1 =49;
const int TOTAL_BRICKSLV2 = 29;
const int TOTAL_BRICKSLV3 =34;
const int TOTAL_BRICKSLV4 = 33;
const int TOTAL_BRICKSLV5 =28;


// số lượt chơi còn lại 
const int DIES=2;
int COUNT_DIES=DIES;


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

// khởi tạo music và sound
Mix_Chunk *ballcollision=NULL;
Mix_Chunk *brickcollision=NULL;
Mix_Music *music_Menu=NULL;
Mix_Music *music_Play=NULL;
Mix_Music *music_GameWin=NULL;
Mix_Music *music_GameOver=NULL;

//Globally used font
TTF_Font *gFont = NULL;
TTF_Font *gFont_HighScore = NULL;

// điểm số của trò chơi
int count_Broken_Bricks=0;

// số màu của viên gạch
const int TOTAL_COLOR_BRICK = 10;

// khai báo 2 biến để giữa vel lúc pause
int velPauseX=0;
int velPauseY=0;


// màu của quả bóng (dot)
enum color{
    red=0,
    pink=1,
    purple=2,
    blue=3,
    green=4,
    TOTAL_COLOR=5
};

// khai báo các hình chữ nhật để load các Texture khác nhau hình ảnh quả bóng
SDL_Rect gDotRect[5];

// điểm cao 
std::stringstream high_Score;

//một số màu mặc định
const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};
const SDL_Color DEFAULT_COLOR = BLACK_COLOR;

// biến để lưu trạng thái của âm thanh
bool music=true;
bool sfx=true;

int FPS=60;


//Scene textures
// khai báo các biến LTexture để load texture từ hình ảnh quả bóng (dot)
LTexture gDotTexture;

// khai báo các biến LTexture để load texture từ hình ảnh mái chèo (paddle)
LTexture gPaddleTexture;

//// khai báo các biến LTexture để load texture từ hình ảnh viên gạch (brick    )
LTexture gBricksTexture[ TOTAL_COLOR_BRICK];
//Rendered texture

// hiện thị level game
LTexture gTextTexture;

//khai báo texture điểm
LTexture gScoreTexture;

// load hình ảnh khi gameover
LTexture gGameOverTexture;

// load hình ảh khi game win 
LTexture gGameWin;

// khai báo texture điểm cao
LTexture ghigh_Score;

// load hình ảnh bg ở main_menu
LTexture gBg_Mainmenu[2];

// load hình ảnh about game
LTexture gBg_About;

//load hình ảnh khung chơi
LTexture gBgLv1;// khung chơi


//================các biến thuộc button================

LButton gButton[14];


//====================khai báo các biến sử của LButton1====================
LButton1 gButton1_Pause;
LButton1 gButton1_Back;

//====khai báo biến thuộc button này====
LButton2 gButtonsfx;
LButton2 gButtonmusic;


//====== khởi tạo class cho đối tượng mái chèo
class Paddle
{
    public:

		static const int PADDLE_WIDTH = 90;
		static const int PADDLE_HEIGHT = 20;

		static const int PADDLE_VEL = 10;

		//Initializes the variables
		Paddle();

		void handleEventPaddle( SDL_Event& e );

		void moveP();

		void renderP();

		int getPosXP();
		int getPosYP();
		int getVelXP();
		int getVelYP();
		int setPosXP(int& x);
		int setPosYP(int& y);
		SDL_Rect getColliderP();
		void freeP();
    private:
	
		int mPosXP, mPosYP;


		int mVelXP, mVelYP;
		
		
		SDL_Rect mPaddle;
};

//==== các hàm thành viên của class này ====//

int Paddle::getPosXP(){
	return mPosXP;
}
int Paddle::getPosYP(){
	return mPosYP;
}
int Paddle::getVelXP(){
	return mVelXP;
}
int Paddle::getVelYP(){
	return mVelYP;
}
int Paddle::setPosXP(int& x){
	mPosXP = x;
}
int Paddle::setPosYP(int& y){
	mPosYP = y;
}
SDL_Rect Paddle::getColliderP(){
	return mPaddle;
}
Paddle::Paddle(){
	mPosXP = (SCREEN_WIDTH)/2 - PADDLE_WIDTH/2;
	mPosYP = (SCREEN_HEIGHT-SCREEN_BOTTOM) - PADDLE_HEIGHT;
	mVelXP = 0;
	mVelYP = 0;
	mPaddle.w = PADDLE_WIDTH;
	mPaddle.h = PADDLE_HEIGHT;
}

void Paddle::handleEventPaddle( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT: mVelXP -= PADDLE_VEL; break;
            case SDLK_RIGHT: mVelXP += PADDLE_VEL; break;
			case SDLK_a: mVelXP -= PADDLE_VEL; break;
            case SDLK_d: mVelXP += PADDLE_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT: mVelXP += PADDLE_VEL; break;
            case SDLK_RIGHT: mVelXP -= PADDLE_VEL; break;
			case SDLK_a: mVelXP += PADDLE_VEL; break;
            case SDLK_d: mVelXP -= PADDLE_VEL; break;
        }
    }
}
void Paddle::moveP(){
    //Move the dot left or right
    mPosXP += mVelXP;
	mPaddle.x = mPosXP;
    //If the dot collided or went too far to the left or right
			if( ( mPosXP < SCREEN_LEFT)   )
				{
					//Move back
					mPosXP = SCREEN_LEFT;
					mPaddle.x = mPosXP;
					}
			if(( mPosXP > SCREEN_WIDTH-SCREEN_LEFT-PADDLE_WIDTH))
			{
				mPosXP = SCREEN_WIDTH-SCREEN_LEFT-PADDLE_WIDTH;
				mPaddle.x = mPosXP;
			}

}
//Starts up SDL and creates window
void Paddle::renderP(){
	//Render paddle
	gPaddleTexture.render(mPosXP, mPosYP,gRenderer);  
}
void Paddle::freeP(){
	gPaddleTexture.free();
}

Paddle paddle;

// khởi tạo cáu trúc hình tròn cho quả bóng
struct Circle
{
	int x, y;
	int r;
};

// khởi tạo class cho đối tượng quả bóng

class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 21;
		static const int DOT_HEIGHT = 21;

		//Maximum axis velocity of the dot
		static const int DOT_VEL =4;

		//Initializes the variables
		Dot();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot and checks collision
		void move( Brick brick[],int n);
        void move5( Brick brick[],int n);

		//Shows the dot on the screen
		void render(const int & color);
        void reset();
        
        void set_gDot_Texture(std::string path,const int &n);
        void ball_brick_collision(Brick brick[],int n);

        int set_mVelY(int y);
        int set_mVelX(int x);
        int getVelX();
        int getVelY();

        int getX();
        int getY();
		int setPosX(int x);
		int setPosY(int y);

        void free();
    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;
		
		//Dot's collision box
		Circle mCollider;

        void shiftColliders();// khởi tạo hình tròn cho quả bóng

        LTexture gDot[5];
};
Dot dot;

double distanceSquared( int x1, int y1, int x2, int y2 )
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}

// hàm check va chạm giữa quả bóng và viên gạch
bool checkCollision( Circle& a, Brick& b )
{
    //Closest point on collision box
    int cX, cY;

    //Find closest x offset
    if( a.x < b.getPosXB() )
    {
        cX = b.getPosXB();
    }
    else if( a.x > b.getPosXB() + b.BRICK_WIDTH )
    {
        cX =b.getPosXB() + b.BRICK_WIDTH;
    }
    else
    {
        cX = a.x;
    }

    //Find closest y offset
    if( a.y < b.getPosYB() )
    {
        cY = b.getPosYB();
    }
    else if( a.y > b.getPosYB()+ b.BRICK_HEIGHT )
    {
        cY = b.getPosYB()+ b.BRICK_HEIGHT;
    }
    else
    {
        cY = a.y;
    }

    //If the closest point is inside the circle
    if( distanceSquared( a.x, a.y, cX, cY ) < a.r * a.r )
    {
        //This box and the circle have collided
        return true;
    }

    //If the shapes have not collided
    return false;
}
// các hàm thành viên của class này
Dot::Dot()
{
    //Initialize the offsets
    mPosX = paddle.getPosXP()+paddle.PADDLE_WIDTH/2-DOT_WIDTH/2;
    mPosY = SCREEN_HEIGHT-SCREEN_BOTTOM- DOT_HEIGHT-paddle.PADDLE_HEIGHT;// THAT ĐỔI VỊ TRÍ MỚI CỦA DOT

	//Set collision box dimension
	mCollider.r = DOT_WIDTH/2;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    //Move collider relative to the circle
    shiftColliders();
}
void Dot::shiftColliders()
{
	//Align collider to center of dot
	mCollider.x = mPosX+DOT_WIDTH/2;
	mCollider.y = mPosY+DOT_HEIGHT/2;
}

int Dot::setPosX(int x){
    mPosX = x;
}
int Dot::setPosY(int y){
    mPosY = y;
}
void Dot::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
			case SDLK_SPACE: {
                if(paddle.getPosXP()+paddle.PADDLE_WIDTH/2<SCREEN_WIDTH/2){
                    mVelX=DOT_VEL;
                    mVelY=-DOT_VEL;
                }
                else if(paddle.getPosXP()+paddle.PADDLE_WIDTH/2>=SCREEN_WIDTH/2){
                    mVelX=-DOT_VEL;
                    mVelY=-DOT_VEL;
                }
			}
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
			case SDLK_SPACE: {
				if(paddle.getPosXP()+paddle.PADDLE_WIDTH/2<SCREEN_WIDTH/2){
                    mVelX=DOT_VEL;
                    mVelY=-DOT_VEL;
                }
                else if(paddle.getPosXP()+paddle.PADDLE_WIDTH/2>=SCREEN_WIDTH/2){
                    mVelX=-DOT_VEL;
                    mVelY=-DOT_VEL;
                }
			}
        }
    }
}
void Dot::move(Brick brick[],int n ){
    // dành cho trường hợp là dot đang ở trên paddle
    if(mVelX==0&&mVelY==0){
        mPosX=paddle.getPosXP()+paddle.PADDLE_WIDTH/2-DOT_WIDTH/2;
        mPosY=SCREEN_HEIGHT-SCREEN_BOTTOM- DOT_HEIGHT-paddle.PADDLE_HEIGHT;
    }
    // tăng vận tốc x
    mPosX += mVelX;
	shiftColliders();   

    //If the dot collided or went too far to the left or right
    for(int i=0;i<n;i++){
	if(  checkCollision( mCollider, brick[i] ) )
    {
        //Move back
        mVelX*=-1;
		shiftColliders();

        // render hình ảnh quả bóng này ở chỗ khác ngoài màn hình ( không thể giải phóng vì nếu giải phóng thì LTexutre có màu giống viên gạch này cũng sẽ free())
        brick[i]=brick[i].setBrick_mPosXB(30000);
        
        if(sfx)
        {
            Mix_PlayChannel( -1, brickcollision, 0 );
        }
        count_Broken_Bricks=count_Broken_Bricks+50;
    }
    }

    // va chạm với cạnh bên trái và cạnh bên phải
    if( ( mPosX <= SCREEN_LEFT )  ) {
        mPosX = SCREEN_LEFT;
        mVelX *= -1;
        if(sfx){
        Mix_PlayChannel(-1,ballcollision,0);
        }
    }
    
    if(( mPosX + DOT_WIDTH >= (SCREEN_WIDTH-SCREEN_RIGHT) ) ) {
        mPosX = SCREEN_WIDTH-SCREEN_RIGHT-DOT_WIDTH;
        mVelX *= -1;
        if(sfx){
        Mix_PlayChannel(-1,ballcollision,0);
        }
    }


    //Move the dot up or down
    mPosY += mVelY;
	shiftColliders();

    //If the dot collided or went too far up or down
    for(int i=0;i<n;i++){
    if(  checkCollision( mCollider, brick[i] ) )
    {
        //Move back
        mVelY*=-1;
		shiftColliders();

        // render hình ảnh quả bóng này ở chỗ khác ngoài màn hình ( không thể giải phóng vì nếu giải phóng thì LTexutre có màu giống viên gạch này cũng sẽ free())
        brick[i]=brick[i].setBrick_mPosXB(30000);

        if(sfx)
        {
            Mix_PlayChannel( -1, brickcollision, 0 );
        }
        count_Broken_Bricks=count_Broken_Bricks+50;
    }
    }
    
    // va chạm với cạnh trên
    if( mPosY <= (SCREEN_TOP) ) {
        mPosY = SCREEN_TOP;
        mVelY *= -1;
        Mix_PlayChannel(-1,ballcollision,0);
    }
    // va chạm với cạnh dưới
	if(mPosY + DOT_HEIGHT >= (SCREEN_HEIGHT-SCREEN_BOTTOM) ){
        
		reset();
		SDL_Delay(50);
		COUNT_DIES--;
	}
    // va chạm với paddle
    if(mPosY+DOT_HEIGHT>=paddle.getPosYP()&&mPosX>=paddle.getPosXP()&&mPosX<=paddle.getPosXP()+paddle.PADDLE_WIDTH){
        mPosY=paddle.getPosYP()-DOT_HEIGHT;// chỗ này khá hay để tránh tình trạng lỗi chạy trên thanh paddle, chưa hiểu nguyên nhân tại sao
        mVelY*=-1;

    }
    
}
void Dot::move5(Brick brick[],int n ){
    // dành cho trường hợp là dot đang ở trên paddle
    if(mVelX==0&&mVelY==0){
        mPosX=paddle.getPosXP()+paddle.PADDLE_WIDTH/2-DOT_WIDTH/2;
        mPosY=SCREEN_HEIGHT-SCREEN_BOTTOM- DOT_HEIGHT-paddle.PADDLE_HEIGHT;
    }

    //Move the dot left or right

    //If the dot collided or went too far to the left or right

    //va chạm với viên gạch
    mPosX += mVelX;
	shiftColliders();

    //If the dot collided or went too far to the left or right
    for(int i=0;i<n;i++){
	if(  checkCollision( mCollider, brick[i] ) )
    {   
        //Move back
        if(i<21||i>26){
        mVelX*=-1;
		shiftColliders();

        brick[i]=brick[i].setBrick_mPosXB(30000);

        count_Broken_Bricks=count_Broken_Bricks+50;
        if(sfx)
        {
                Mix_PlayChannel( -1, brickcollision, 0 );
            }
        }
        else {

        mPosX-=mVelX;
        //mVelX*=-1;// có 1 bug là khi va chạm thì sẽ bị lỗi va chạm với viên gạch 26 theo hướng x nên chưa biết cách fix như nào chữa cháy bằng cách này thôi
		shiftColliders();
        if(sfx){
        Mix_PlayChannel(-1,ballcollision,0);
        }
        }  
        //delete_brick_count++;
    }
    }

    // va chạm với cạnh bên trái và cạnh bên phải
    if( ( mPosX <= SCREEN_LEFT )  ) {
        mPosX = SCREEN_LEFT;
        mVelX *= -1;
        if(sfx){
        Mix_PlayChannel(-1,ballcollision,0);
        }
    }
    if(( mPosX + DOT_WIDTH >= (SCREEN_WIDTH-SCREEN_RIGHT) ) ) {
        mPosX = SCREEN_WIDTH-SCREEN_RIGHT-DOT_WIDTH;
        mVelX *= -1;
        if(sfx){
        Mix_PlayChannel(-1,ballcollision,0);
        }
    }


    //Move the dot up or down
    mPosY += mVelY;
	shiftColliders();

    //If the dot collided or went too far up or down
    for(int i=0;i<n;i++){
    if(  checkCollision( mCollider, brick[i] ) )
    {
        //Move back

        if(i<21||i>26){
        mVelY*=-1;
		shiftColliders();
        brick[i]=brick[i].setBrick_mPosXB(30000);
        count_Broken_Bricks=count_Broken_Bricks+50;
        if(sfx)
        {
            Mix_PlayChannel( -1, brickcollision, 0 );
        }
        }
        else      {
        mPosY-=mVelY;
        mVelY*=-1;
		shiftColliders();
        if(sfx){
        Mix_PlayChannel(-1,ballcollision,0);
        }
        }   

       
    }
    }

    // va chạm với cạnh trên
    if( mPosY <= (SCREEN_TOP) ) {
        mPosY = SCREEN_TOP;
        mVelY *= -1;
        Mix_PlayChannel(-1,ballcollision,0);
    }
    // va chạm với cạnh dưới
	if(mPosY + DOT_HEIGHT >= (SCREEN_HEIGHT-SCREEN_BOTTOM) ){
        
		reset();
		SDL_Delay(50);
		COUNT_DIES--;
	}
    // va chạm với paddle
    if(mPosY+DOT_HEIGHT>=paddle.getPosYP()&&mPosX>=paddle.getPosXP()&&mPosX<=paddle.getPosXP()+paddle.PADDLE_WIDTH){
        mPosY=paddle.getPosYP()-DOT_HEIGHT;// chỗ này khá hay để tránh tình trạng lỗi chạy trên thanh paddle, chưa hiểu nguyên nhân tại sao
        mVelY*=-1;
		//Mix_PlayChannel(-1,ballcollision,0);
    }
    
}

void Dot::render(const int& color)
{
    switch(color){
        case red:
        gDot[0].render( mPosX, mPosY ,gRenderer,&gDotRect[0]);
        break;
        case pink:
        gDot[1].render( mPosX, mPosY ,gRenderer,&gDotRect[1]);
        break;
        case purple:
        gDot[2].render( mPosX, mPosY ,gRenderer,&gDotRect[2]);
        break;
        case blue:
        gDot[3].render( mPosX, mPosY ,gRenderer,&gDotRect[3]);
        break;
        case green:
        gDot[4].render( mPosX, mPosY ,gRenderer,&gDotRect[4]);
        break;
    }
}
void Dot::set_gDot_Texture(std::string path,const int &n) {
    gDot[n].loadFromFile(path,gRenderer);
    for(int i=0;i<5;i++){
        gDotRect[i]={i*DOT_WIDTH,0,DOT_WIDTH,DOT_HEIGHT};
    }
}
int Dot :: getX() {
    return mPosX;
}
int Dot::getY() {
    return mPosY;
}
int Dot::getVelX() {
    return mVelX;
}
int Dot::getVelY() {
    return mVelY;
}
void Dot:: reset(){
    //Initialize the offsets
    mPosX = paddle.getPosXP()+paddle.PADDLE_WIDTH/2-DOT_WIDTH/2;
    mPosY = SCREEN_HEIGHT-SCREEN_BOTTOM- DOT_HEIGHT-paddle.PADDLE_HEIGHT;// THAT ĐỔI VỊ TRÍ MỚI CỦA DOT

	//Set collision box dimension
	mCollider.r = DOT_WIDTH/2;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    shiftColliders();
}
int Dot::set_mVelX(int x) {
    mVelX = x;
}
int Dot::set_mVelY(int y) {
    mVelY = y;
}
void Dot::free(){
    gDot[0].free();
    gDot[1].free();
    gDot[2].free();
    gDot[3].free();
    gDot[4].free();
}

// các hàm chung
void init();
void loadMedia();

int loadhighScore();
void savehighScore(int& n);

void freeButton();
void freeDot();
void freePaddle();
void freeBrick();
void freeFont();
void freeMusic();
void freeSound();
void close();

void Init_Bricklv1(Brick brick[]);
void Init_Bricklv2(Brick brick[]);
void Init_Bricklv3(Brick brick[]);
void Init_Bricklv4(Brick brick[]);
void Init_Bricklv5(Brick brick[]);

void render_Brick_lv1(Brick brick[]);
void render_Brick_lv2(Brick brick[]);
void render_Brick_lv3(Brick brick[]);
void render_Brick_lv4(Brick brick[]);
void render_Brick_lv5(Brick brick[]);

// khởi tạo 1 cấu trúc toạ độ x y
struct Point{
    int x;
    int y;
    Point(){
        x=0;
        y=0;
    }
    Point(int a,int b){
        x=a;
        y=b;
    }
};

// load 1 vector từ file
vector<Point> load_Vector(std::string s){
    ifstream in(s);
    int n;
    in>>n;
    vector<Point> v;
    while(!in.eof()){
        int x,y;
        in>>x>>y;
        v.push_back(Point(x,y));
    }
    return v;
}

// load 1 vector char từ file
vector<char> load_Color(string s){
    ifstream in(s);
    int n;
    in>>n;
    vector<char> v;
    while(!in.eof()){
        char c;
        in>>c;
        v.push_back(c);
    }
    return v;
 }


// hàm khởi tạo sdl

void init()
{
		gWindow = SDL_CreateWindow( "Break Brick Game	", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				IMG_Init( imgFlags );
				Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
				TTF_Init();
}

// hàm load các texture từ hình ảnh
void loadMedia()    
{
	// load các brick
	gBricksTexture[BLUE].loadFromFile("source/Data/img/bricks/blue.png",gRenderer);
	gBricksTexture[RED].loadFromFile("source/Data/img/bricks/red.png",gRenderer);
	gBricksTexture[GREEN].loadFromFile("source/Data/img/bricks/green.png",gRenderer);
	gBricksTexture[DARK_GREEN].loadFromFile("source/Data/img/bricks/darkgreen.png",gRenderer);
	gBricksTexture[INDIGO].loadFromFile("source/Data/img/bricks/indigo.png",gRenderer);
	gBricksTexture[ORANGE].loadFromFile("source/Data/img/bricks/orange.png",gRenderer);
	gBricksTexture[PINK].loadFromFile("source/Data/img/bricks/pink.png",gRenderer);
	gBricksTexture[SOLID].loadFromFile("source/Data/img/bricks/solid.png",gRenderer);
	gBricksTexture[VIOLET].loadFromFile("source/Data/img/bricks/violet.png",gRenderer);
	gBricksTexture[YELLOW].loadFromFile("source/Data/img/bricks/yellow.png",gRenderer);

	// load mái chéo paddle
	gPaddleTexture.loadFromFile("source/Data/img/paddle/paddlemedium.png",gRenderer);
	
	// load hình ảnh quả bóng

	for(int i=0;i<5;i++){
	dot.set_gDot_Texture("source/Data/img/anim/ballanim.png",i);
	}

	// load background 
	gGameOverTexture.loadFromFile("source/Data/img/bg/gameover.png",gRenderer);
	
	gGameWin.loadFromFile("source/Data/img/bg/win.png",gRenderer);
	gBg_Mainmenu[0].loadFromFile("source/Data/img/bg/bg_main_menu.jpg",gRenderer);
	gBg_Mainmenu[1].loadFromFile("source/Data/img/bg/bg_main_menu1.png",gRenderer);
	gBg_About.loadFromFile("source/Data/img/bg/gBg_About.png",gRenderer);

	gBgLv1.loadFromFile("source/Data/img/bg.png",gRenderer);

	// load music

	music_Menu=Mix_LoadMUS("source/Data/audio/music/menu_bg.ogg");
	music_Play=Mix_LoadMUS("source/Data//audio/music/play_bg.ogg");
	music_GameOver=Mix_LoadMUS("source/Data/audio/music/gameover_bg.ogg");
	music_GameWin=Mix_LoadMUS("source/Data/audio/music/gamewinning_bg.ogg");

	// load sound
    ballcollision=Mix_LoadWAV("source/Data/audio/sfx/ballcollision.wav");
    brickcollision=Mix_LoadWAV("source/Data/audio/sfx/brickcollision.wav");
	gFont= TTF_OpenFont( "source/Data/font/font_02/Roboto-Medium.ttf", 40 );
	gFont_HighScore=TTF_OpenFont("source/Data/font/font_01/DoppioOne-Regular.ttf",23);

	// load button1 
	for(int i=0;i<4;i++){
	gButton[ABOUT].set_texture("source/Data/img/buttons/aboutbutton.png",i,gRenderer);
	}
	gButton[ABOUT].setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT-70 -2*BUTTON_HEIGHT- 2*BUTTON_HEIGHT/8);

	for(int i=0;i<4;i++){
	gButton[GAME_PLAY].set_texture("source/Data/img/buttons/playbutton.png",i,gRenderer);
	}
	gButton[GAME_PLAY].setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2,SCREEN_HEIGHT-70 -3*BUTTON_HEIGHT- 3*BUTTON_HEIGHT/8);

	for(int i=0;i<4;i++){
	gButton[EXIT].set_texture("source/Data/img/buttons/exitbutton.png",i,gRenderer);
	}
	gButton[EXIT].setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT -70 );

	for(int i=0;i<4;i++){
	gButton[SOUND].set_texture("source/Data/img/buttons/soundbutton.png",i,gRenderer);
	}
	gButton[SOUND].setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT-70 -BUTTON_HEIGHT- BUTTON_HEIGHT/8);

	for(int i=0;i<4;i++){
		gButton[RESUME].set_texture("source/Data/img/buttons/resumebutton.png",i,gRenderer);
	}
	gButton[RESUME].setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT-70 -2*BUTTON_HEIGHT- 2*BUTTON_HEIGHT/8);

	for(int i=0;i<4;i++){
	gButton[RESTART].set_texture("source/Data/img/buttons/restartbutton.png",i,gRenderer);
	}
	gButton[RESTART].setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2,SCREEN_HEIGHT-70 -BUTTON_HEIGHT- BUTTON_HEIGHT/8);

	for(int i=0;i<4;i++){
	gButton[MAIN_MENU].set_texture("source/Data/img/buttons/mainmenubutton.png",i,gRenderer);
	}
	gButton[MAIN_MENU].setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT-70 -2*BUTTON_HEIGHT- 2*BUTTON_HEIGHT/8);

	// load button1
	for(int i=0;i<4;i++){
	gButton1_Pause.set_texture("source/Data/img/buttons/pausebutton.png",i,gRenderer);
	}
	gButton1_Pause.setPosition(SCREEN_WIDTH-SCREEN_RIGHT-BUTTON_WIDTH1-BUTTON_WIDTH1-2, 544);

	for(int i=0;i<4;i++){
	gButton1_Back.set_texture("source/Data/img/buttons/backbutton.png",i,gRenderer);
	}
	gButton1_Back.setPosition(8, 12);


	// load button2
	gButtonsfx.set_texture("source/Data/img/buttons/sfxoffbutton.png",0,gRenderer);
	gButtonsfx.set_texture("source/Data/img/buttons/sfxoffbutton.png",1,gRenderer);
	gButtonsfx.set_texture("source/Data/img/buttons/sfxonbutton.png",2,gRenderer);
	gButtonsfx.set_texture("source/Data/img/buttons/sfxonbutton.png",3,gRenderer);
	gButtonsfx.setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT-70 -BUTTON_HEIGHT- BUTTON_HEIGHT/8);
	gButtonmusic.set_texture("source/Data/img/buttons/musicoffbutton.png",0,gRenderer);
	gButtonmusic.set_texture("source/Data/img/buttons/musicoffbutton.png",1,gRenderer);
	gButtonmusic.set_texture("source/Data/img/buttons/musiconbutton.png",2,gRenderer);
	gButtonmusic.set_texture("source/Data/img/buttons/musiconbutton.png",3,gRenderer);
	gButtonmusic.setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT-70 -2*BUTTON_HEIGHT- 2*BUTTON_HEIGHT/8);
}

//====== hàm để ghi điểm cao vào file ======
int loadhighscore(){
    std::ifstream inFile;
    inFile.open("source/Data/data_txt/highscore.txt");
    int n;
    inFile >> n;
    return n;
}
void sethighscore(int& n){
    std::ofstream outFile;
    outFile.open("source/Data/data_txt/highscore.txt");
    outFile << n;
    outFile.close();
}

//======= các hàm giải phóng các biến của cấu trúc của game =======

void freeButton(){
	for(int i=0;i<4;i++){
		gButton[i].freeB();
	}
	//
	gButton1_Pause.freeB();
	gButton1_Back.freeB();
	//
	gButtonsfx.freeB();
	gButtonmusic.freeB();
}

void freeDot(){
	dot.free();
}

void freePaddle(){
	paddle.freeP();
}

void freeBrick(){
	for(int i=0;i<TOTAL_COLOR_BRICK;i++){
		gBricksTexture[i].free();
	}
}

void freeFont(){
	TTF_CloseFont(gFont);
	gFont = NULL;
	TTF_CloseFont(gFont_HighScore);
	gFont_HighScore = NULL;
}

void freeMusic(){
	Mix_FreeMusic(music_Menu);
	music_Menu = NULL;
	Mix_FreeMusic(music_Play);
	music_Play = NULL;
	Mix_FreeMusic(music_GameOver);
	music_GameOver = NULL;
	Mix_FreeMusic(music_GameWin);
	music_GameWin = NULL;
}

void freeSound(){
	Mix_FreeChunk(ballcollision);
	ballcollision = NULL;
	Mix_FreeChunk(brickcollision);
	brickcollision = NULL;
}


void close()
{
	// giải phóng các đối tượng
	//1 button
	freeButton();
	//2 dot
	freeDot();
	//3 paddle
	freePaddle();
	//4 brick
	freeBrick();
	// 
	freeFont();

	freeMusic();
	freeSound();
	//
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	// cần xóa giải phóng bộ nhớ sau khi chơi game	
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();

}

//== các hàm khai báo biến brick====

void Init_Bricklv1(Brick brick[]){
	vector<Point> lv1=load_Vector("source/Data/data_txt/lv1.txt");
   	for (int i = 0; i < TOTAL_BRICKSLV1; i++){
	   		brick[i].setBrick(lv1[i].x,lv1[i].y,0,0);
	      }
}
void Init_Bricklv2(Brick brick[]){
	vector<Point> lv2=load_Vector("source/Data/data_txt/lv2.txt");
   	for (int i = 0; i < TOTAL_BRICKSLV2; i++){
		brick[i].setBrick(lv2[i].x,lv2[i].y,0,0);
	}
}
void Init_Bricklv3(Brick brick[]){
	vector<Point> lv3=load_Vector("source/Data/data_txt/lv3.txt");
   	for (int i = 0; i < TOTAL_BRICKSLV3; i++){
		brick[i].setBrick(lv3[i].x,lv3[i].y,0,0);
	}
}
void Init_Bricklv4(Brick brick[]){
	vector<Point> lv4=load_Vector("source/Data/data_txt/lv4.txt");
   	for (int i = 0; i < TOTAL_BRICKSLV4; i++){
		brick[i].setBrick(lv4[i].x,lv4[i].y,0,0);
	}
}
void Init_Bricklv5(Brick brick[]){
	vector<Point> lv5=load_Vector("source/Data/data_txt/lv5.txt");
   	for (int i = 0; i < TOTAL_BRICKSLV5; i++){
		brick[i].setBrick(lv5[i].x,lv5[i].y,0,0);
	}
}

///=== render_Brick.h ===///
//==== các hàm render biến brick===========

void render_Brick_Lv1(Brick brick[]){
	vector<char> color1=load_Color("source/Data/data_txt/lev1C.txt");
	for(int i=0;i<TOTAL_BRICKSLV1;i++){
		brick[i].renderB(color1[i],gBricksTexture,gRenderer);
	}
}
void render_Brick_Lv2(Brick brick[]){
	vector<char> color2=load_Color("source/Data/data_txt/lev2C.txt");
	for(int i=0;i<TOTAL_BRICKSLV2;i++){
		brick[i].renderB(color2[i],gBricksTexture,gRenderer);
	}
}
void render_Brick_Lv3(Brick brick[]){
	vector<char> color3=load_Color("source/Data/data_txt/lev3C.txt");
	for(int i=0;i<TOTAL_BRICKSLV3;i++){
		brick[i].renderB(color3[i],gBricksTexture,gRenderer);
	}
}
void render_Brick_Lv4(Brick brick[]){
	vector<char> color4=load_Color("source/Data/data_txt/lev4C.txt");
	for(int i=0;i<TOTAL_BRICKSLV4;i++){
		brick[i].renderB(color4[i],gBricksTexture,gRenderer);
	}
}
void render_Brick_Lv5(Brick brick[]){
	vector<char> color5=load_Color("source/Data/data_txt/lev5C.txt");
	for(int i=0;i<TOTAL_BRICKSLV5;i++){
		brick[i].renderB(color5[i],gBricksTexture,gRenderer);
	}
}


std::string lose();
std::string pause();
std::string main_menu();
std::string sound();
std::string about();

//==== hàm hiện thị màn hình âm thanh
std::string sound(){
	std::cout<<"sound"<<std::endl;
	bool quit = false;

	//Event handler
	SDL_Event e;
	
	//While application is running
	
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
				return "quit";
			}
			//Handle input for the dot
			dot.handleEvent(e);
			paddle.handleEventPaddle(e);
			gButton1_Back.handleEvent(&e);
			gButtonsfx.handleEvent(&e);
			gButtonmusic.handleEvent(&e);

		}
		//Clear screen
		
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xF0);
		SDL_RenderClear(gRenderer);

		if(gButtonmusic.getStatus()==BUTTON_SPRITE_MOUSE_DOWN&&gButtonmusic.get_on()) {
		music=!music;
		gButtonmusic.set_on(false);
		gButtonmusic.freeStatus();
		}
		if(gButtonmusic.getStatus()==BUTTON_SPRITE_MOUSE_DOWN&&!gButtonmusic.get_on()) {
		music=!music;
		gButtonmusic.set_on(true);
		gButtonmusic.freeStatus();
		}
		if(gButtonsfx.getStatus()==BUTTON_SPRITE_MOUSE_DOWN&&gButtonsfx.get_on()) {
		sfx=!sfx;
		gButtonsfx.set_on(false);
		gButtonsfx.freeStatus();
		}
	
		if(gButtonsfx.getStatus()==BUTTON_SPRITE_MOUSE_DOWN&&!gButtonsfx.get_on()) {
		sfx=!sfx;
		gButtonsfx.set_on(true);
		gButtonsfx.freeStatus();
		}
		if(gButton1_Back.getStatus()==BUTTON_SPRITE_MOUSE_DOWN){
			gButton1_Back.freeStatus();
			quit=true;
			return "menu";
		}
		

		//Render objects
		gButtonsfx.render(gRenderer);
		gButtonmusic.render(gRenderer);
		gButton1_Back.render(gRenderer);
		//Update screen
		SDL_RenderPresent(gRenderer);
		

	}
}

// hiện thị màn hình khi thắng

std::string win(){
    //Main loop flag
	std::cout<<"win"<<std::endl;
	bool quit = false;
	//Event handler
	SDL_Event e;

	// hiện thị điểm khi thua
    std::stringstream timeTextWin;

	// hiện thị điểm cao
	std::stringstream high_Score;

	// màu sắc của các texture load từ chữ
	SDL_Color textColor = DEFAULT_COLOR;
	

	// điều kiện để có âm thanh 
	if(music){
		Mix_PlayMusic(music_GameWin, -1);
	}
	
	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
				return "quit";
			}
			gButton[RESTART].handleEvent(&e);
			gButton[MAIN_MENU].handleEvent(&e);
			gButton[EXIT].handleEvent(&e);
			
		}

		// điểm khi ở màn hình thắng
		timeTextWin.str("");
		timeTextWin << "YOU_SCORE:: " << count_Broken_Bricks ;

		// điểm cao 

		high_Score.str("");
		high_Score << "HIGH SCORE:: " << loadhighscore();

		// load texture từ chữ
		if (!gScoreTexture.loadFromRenderedText(timeTextWin.str().c_str(), textColor,gRenderer,gFont_HighScore))
		{
			printf("Unable to render FPS texture!\n");
		}
		if (!ghigh_Score.loadFromRenderedText(high_Score.str().c_str(), textColor,gRenderer,gFont_HighScore))
		{
			printf("Unable to render FPS texture!\n");
		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0x0F, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render objects
		gButton[RESTART].render(gRenderer);
		gButton[MAIN_MENU].render(gRenderer);
		gButton[EXIT].render(gRenderer);
		gGameWin.render(10, 100,gRenderer);
		
        gScoreTexture.render(20,10,gRenderer);
		ghigh_Score.render(0, 50,gRenderer);


		if(gButton[RESTART].getStatus()==BUTTON_SPRITE_MOUSE_DOWN)
		{
			gButton[RESTART].freeStatus();
			count_Broken_Bricks=0;
			quit=true;
			return "playlv1";
			
		}
		else if(gButton[MAIN_MENU].getStatus()==BUTTON_SPRITE_MOUSE_DOWN)
		{	
			gButton[MAIN_MENU].freeStatus();
			count_Broken_Bricks=0;
			quit=true;
			return "menu";
		}
		else if(gButton[EXIT].getStatus()==BUTTON_SPRITE_MOUSE_DOWN)
		{
			gButton[EXIT].freeStatus();
			quit=true;
			return "quit";
		}
		
		//Update screen
		SDL_RenderPresent(gRenderer);
		
	}
}

std::string playlv5() {
	//Main loop flag
	std::cout<<"playlv5"<<std::endl;
	bool quit = false;
	//Event handler
	SDL_Event e;

	// khởi tạo brick
	Brick brick5[TOTAL_BRICKSLV5];
	Init_Bricklv5(brick5);
	
	//Angle of rotation
	double degrees = 0;

	if(music){
		Mix_PlayMusic(music_Play, -1);
	}

	//Flip type
	SDL_RendererFlip flipType = SDL_FLIP_NONE;

	SDL_Color textColor = WHITE_COLOR;


	//In memory text stream
	std::stringstream timeText;
	

	//While application is running
	
	while (!quit)
	{   
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
				return "quit";
			}
			//Handle input for the dot
			if(dot.getVelX()==0&&dot.getVelY()==0){
				dot.handleEvent(e);
			}
			paddle.handleEventPaddle(e);
			gButton1_Pause.handleEvent(&e);

		}	
		//Move the dot and check collision
		dot.move5(brick5,TOTAL_BRICKSLV5); 
		paddle.moveP();

		if(count_Broken_Bricks>loadhighscore()){
			sethighscore(count_Broken_Bricks);
		}
		high_Score.str("");
		high_Score << "HIGH_SCORE:: " << loadhighscore();
		gTextTexture.loadFromRenderedText( "Level 5 ", textColor ,gRenderer,gFont);
		// //Set text to be rendered
		timeText.str("");
		timeText << "SCORE:: " << count_Broken_Bricks ;
        timeText << " Live:: " << COUNT_DIES;
		//Render text
		if (!gScoreTexture.loadFromRenderedText1(timeText.str().c_str(), textColor,gRenderer,gFont_HighScore))
		{
			printf("Unable to render FPS texture!\n");
		}
		if (!ghigh_Score.loadFromRenderedText1(high_Score.str().c_str(), textColor,gRenderer,gFont_HighScore))
		{
			printf("er!\n");
		}
		
		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0x0F, 0xFF, 0xFF, 0x00);
		SDL_RenderClear(gRenderer);

		// Render objects
		dot.render(1);
		paddle.renderP();
		
		render_Brick_Lv5(brick5);
		
		gButton1_Pause.render(gRenderer);
		gBgLv1.render(0, 0,gRenderer);// hiện thị khung để chơi 
		//Render current frame
		gTextTexture.render(0, 10,gRenderer);// LV
		gScoreTexture.render(23, 551,gRenderer);// ĐIỂM
		ghigh_Score.render(150,28,gRenderer);// ĐIỂM CAO

		//Update screen
		SDL_RenderPresent(gRenderer);
		
		
		if (COUNT_DIES < 0) {
			Mix_HaltMusic();
			return "lose";
		}
		if(count_Broken_Bricks==(TOTAL_BRICKSLV1+TOTAL_BRICKSLV2+TOTAL_BRICKSLV3+TOTAL_BRICKSLV4+TOTAL_BRICKSLV5-6)*50){// chú ý sửa chỗ này 
			quit = true;
			//return "quit";
			SDL_Delay(100);
			dot.reset();
			return "win";
		}
		if(gButton1_Pause.getStatus()==BUTTON_SPRITE_MOUSE_DOWN)
		{	
			velPauseX=dot.getVelX();
			velPauseY=dot.getVelY();
			dot.set_mVelX(0);
			dot.set_mVelY(0);
			Mix_HaltMusic();
			gButton1_Pause.freeStatus();
			pause();
		}
		
}
}
std::string playlv4() {
	//Main loop flag
	std::cout<<"playlv4"<<std::endl;
	bool quit = false;

	//Event handler
	SDL_Event e;

	// khởi tạo brick 
	Brick brick4[TOTAL_BRICKSLV4];
	Init_Bricklv4(brick4);

	//Angle of rotation
	double degrees = 0;
	if(music){
		Mix_PlayMusic(music_Play, -1);
	}

	//Flip type
	SDL_RendererFlip flipType = SDL_FLIP_NONE;

	// màu của font chữ 
	SDL_Color textColor = WHITE_COLOR;

	//The frames per second timer
	LTimer fpsTimer;

	//In memory text stream
	std::stringstream timeText;
	
	fpsTimer.start();

   	int i=0;
	//While application is running
	while (!quit)
	{   
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
				return "quit";
			}
			//Handle input for the dot
			if(dot.getVelX()==0&&dot.getVelY()==0){
				dot.handleEvent(e);
			}
			paddle.handleEventPaddle(e);
			gButton1_Pause.handleEvent(&e);

		}	
		//Move the dot and check collision
		dot.move(brick4,TOTAL_BRICKSLV4); 
		paddle.moveP();


		if(count_Broken_Bricks>loadhighscore()){
			sethighscore(count_Broken_Bricks);
		}
		high_Score.str("");
		high_Score << "HIGH_SCORE:: " << loadhighscore();
		gTextTexture.loadFromRenderedText( "Level 4 ", textColor,gRenderer,gFont );
		// //Set text to be rendered
		timeText.str("");
		timeText << "SCORE:: " << count_Broken_Bricks ;
        timeText << " Live:: " << COUNT_DIES;
		//Render text
		if (!gScoreTexture.loadFromRenderedText1(timeText.str().c_str(), textColor,gRenderer,gFont_HighScore))
		{
			printf("Unable to render FPS texture!\n");
		}
		if (!ghigh_Score.loadFromRenderedText1(high_Score.str().c_str(), textColor,gRenderer,gFont_HighScore))
		{
			printf("er!\n");
		}
		
		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

		// render object
		//Render dot
        if(fpsTimer.getTicks()%1000==0){
            i++;
            while(i>4) i-=4;

        }
		dot.render(i);
		paddle.renderP();
		render_Brick_Lv4(brick4);
		gButton1_Pause.render(gRenderer);
		gBgLv1.render(0, 0,gRenderer);// hiện thị khung để chơi 
		gTextTexture.render(0, 10,gRenderer);// LV
		gScoreTexture.render(23, 551,gRenderer);// ĐIỂM
		ghigh_Score.render(150,28,gRenderer);// điểm cao 

		//Update screen
		SDL_RenderPresent(gRenderer);
		
		
		if (COUNT_DIES < 0) {
			Mix_HaltMusic();
			return "lose";
		}
		if(count_Broken_Bricks==(TOTAL_BRICKSLV1+TOTAL_BRICKSLV2+TOTAL_BRICKSLV3+TOTAL_BRICKSLV4)*50){// chú ý sửa chỗ này 
			quit = true;
			//return "quit";
			SDL_Delay(100);
			dot.reset();
			return "playlv5";
		}
		if(gButton1_Pause.getStatus()==BUTTON_SPRITE_MOUSE_DOWN)
		{	
			velPauseX=dot.getVelX();
			velPauseY=dot.getVelY();
			dot.set_mVelX(0);
			dot.set_mVelY(0);
			Mix_HaltMusic();
			gButton1_Pause.freeStatus();
			pause();
		}
		
}
}
std::string playlv3() {
	//Main loop flag
	std::cout<<"playlv3"<<std::endl;
	bool quit = false;

	//Event handler
	SDL_Event e;

	//khởi tạo brick
	Brick brick3[TOTAL_BRICKSLV3];
	Init_Bricklv3(brick3);

	//Angle of rotation
	double degrees = 0;
	if(music){
		Mix_PlayMusic(music_Play, -1);
	}

	//Flip type
	SDL_RendererFlip flipType = SDL_FLIP_NONE;


	SDL_Color textColor = WHITE_COLOR;

	//The frames per second timer
	LTimer fpsTimer;

	//In memory text stream
	std::stringstream timeText;
	


   	int i=0;
	//While application is running
	while (!quit)
	{   
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
				return "quit";
			}
			//Handle input for the dot
			if(dot.getVelX()==0&&dot.getVelY()==0){
				dot.handleEvent(e);
			}
			paddle.handleEventPaddle(e);
			gButton1_Pause.handleEvent(&e);

		}	
		//Move the dot and check collision
		dot.move(brick3,TOTAL_BRICKSLV3);
		
		paddle.moveP();

		if(count_Broken_Bricks>loadhighscore()){
			sethighscore(count_Broken_Bricks);
		}

		// điểm cao 
		high_Score.str("");
		high_Score << "HIGH_SCORE:: " << loadhighscore();
		gTextTexture.loadFromRenderedText( "Level 3 ", textColor ,gRenderer,gFont);
		
		// điểm và lượt chơi còn lại 
		timeText.str("");
		timeText << "SCORE:: " << count_Broken_Bricks ;
        timeText << " Live:: " << COUNT_DIES;

		//Render text
		if (!gScoreTexture.loadFromRenderedText1(timeText.str().c_str(), textColor,gRenderer,gFont_HighScore))
		{
			printf("Unable to render FPS texture!\n");
		}
		if (!ghigh_Score.loadFromRenderedText1(high_Score.str().c_str(), textColor,gRenderer,gFont_HighScore))
		{
			printf("er!\n");
		}
		
		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render objects
		// thay đổi màu quả bóng được
        if(fpsTimer.getTicks()%1000==0){
            i++;
            while(i>4) i-=4;

        }
		dot.render(i);
		paddle.renderP();
		render_Brick_Lv3(brick3);
		gButton1_Pause.render(gRenderer);
		gBgLv1.render(0, 0,gRenderer);// hiện thị khung để chơi 

		gTextTexture.render(0, 10,gRenderer);// LV
		gScoreTexture.render(23, 551,gRenderer);// ĐIỂM
		ghigh_Score.render(150,28,gRenderer);// điểm cao 
		
		//Update screen
		SDL_RenderPresent(gRenderer);
		

		if (COUNT_DIES < 0) {
			Mix_HaltMusic();
			return "lose";
		}
		if(count_Broken_Bricks==(TOTAL_BRICKSLV1+TOTAL_BRICKSLV2+TOTAL_BRICKSLV3)*50){// chú ý sửa chỗ này 
			quit = true;
			//return "quit";
			SDL_Delay(100);
			dot.reset();
			return "playlv4";
		}
		if(gButton1_Pause.getStatus()==BUTTON_SPRITE_MOUSE_DOWN)
		{	
			velPauseX=dot.getVelX();
			velPauseY=dot.getVelY();
			dot.set_mVelX(0);
			dot.set_mVelY(0);
			Mix_HaltMusic();
			gButton1_Pause.freeStatus();
			pause();
		}
		
}
}

std::string playlv2() {
	//Main loop flag
	std::cout<<"playlv2"<<std::endl;
	// 
	bool quit = false;
	//Event handler
	SDL_Event e;

	// khởi tạo brick
	Brick brick2[TOTAL_BRICKSLV2];
	Init_Bricklv2(brick2);

	//Angle of rotation
	double degrees = 0;

	if(music){
		Mix_PlayMusic(music_Play, -1);
	}

	//Flip type
	SDL_RendererFlip flipType = SDL_FLIP_NONE;


	SDL_Color textColor = WHITE_COLOR;


	//In memory text stream
	std::stringstream timeText;
	

   	int i=0;
	//While application is running
	while (!quit)
	{   
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
				return "quit";
			}
			//Handle input for the dot
			if(dot.getVelX()==0&&dot.getVelY()==0){
				dot.handleEvent(e);
			}
			paddle.handleEventPaddle(e);
			gButton1_Pause.handleEvent(&e);

		}	
		//Move the dot and check collision
		dot.move(brick2,TOTAL_BRICKSLV2);
		paddle.moveP();
		
		if(count_Broken_Bricks>loadhighscore()){
			sethighscore(count_Broken_Bricks);
		}
		high_Score.str("");
		high_Score << "HIGH_SCORE:: " << loadhighscore();
		gTextTexture.loadFromRenderedText( "Level 2 ", textColor ,gRenderer,gFont);
		// //Set text to be rendered
		timeText.str("");
		timeText << "SCORE:: " << count_Broken_Bricks ;
        timeText << " Live:: " << COUNT_DIES;
		//Render text
		if (!gScoreTexture.loadFromRenderedText1(timeText.str().c_str(), textColor,gRenderer,gFont_HighScore))
		{
			printf("Unable to render FPS texture!\n");
		}
		if (!ghigh_Score.loadFromRenderedText1(high_Score.str().c_str(), textColor,gRenderer,gFont_HighScore))
		{
			printf("er!\n");
		}
		
		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render objects
		dot.render(i);
		paddle.renderP();
		render_Brick_Lv2(brick2);
		gButton1_Pause.render(gRenderer);
		gBgLv1.render(0, 0,gRenderer);// hiện thị khung để chơi 

		gTextTexture.render(0, 10,gRenderer);// LV
		gScoreTexture.render(23, 551,gRenderer);// ĐIỂM
		ghigh_Score.render(150,28,gRenderer);// điểm cao

		//Update screen
		SDL_RenderPresent(gRenderer);
		

		if (COUNT_DIES < 0) {
			Mix_HaltMusic();
			return "lose";
		}
		if(count_Broken_Bricks==(TOTAL_BRICKSLV1+TOTAL_BRICKSLV2)*50){// chú ý sửa chỗ này 
			quit = true;
			//return "quit";
			SDL_Delay(100);
			dot.reset();
			return "playlv3";
		}
		if(gButton1_Pause.getStatus()==BUTTON_SPRITE_MOUSE_DOWN)
		{	
			velPauseX=dot.getVelX();
			velPauseY=dot.getVelY();
			dot.set_mVelX(0);
			dot.set_mVelY(0);
			Mix_HaltMusic();
			gButton1_Pause.freeStatus();
			pause();
		}
		
}
}

std::string playlv1() {
	//Main loop flag
	std::cout<<"playlv1"<<std::endl;
	bool quit = false;

	// số lượt chơi còn lại
	COUNT_DIES=DIES;
	//Event handler
	SDL_Event e;

	// khởi tạo các viên gạch 
	Brick brick1[TOTAL_BRICKSLV1];
	Init_Bricklv1(brick1);

	//Angle of rotation
	double degrees = 0;

	// điều kiện để có âm thanh khi chơi

	if(music){
		Mix_PlayMusic(music_Play, -1);
	}

	//Flip type
	SDL_RendererFlip flipType = SDL_FLIP_NONE;

	SDL_Color textColor = WHITE_COLOR;

	//The frames per second timer
	LTimer fpsTimer;

	//In memory text stream
	std::stringstream timeText;
	
	fpsTimer.start();

   	int i=0;
	//While application is running
	while (!quit)
	{   
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
				return "quit";
			}
			//Handle input for the dot
			if(dot.getVelX()==0&&dot.getVelY()==0){
			dot.handleEvent(e);
			}
			paddle.handleEventPaddle(e);
			gButton1_Pause.handleEvent(&e);
			
		}	
		//Move the dot and check collision
		dot.move(brick1,TOTAL_BRICKSLV1); 
		paddle.moveP();

		if(count_Broken_Bricks>loadhighscore()){
			sethighscore(count_Broken_Bricks);
		}

		// điểm cao 
		high_Score.str("");
		high_Score << "HIGH_SCORE:: " << loadhighscore();
		gTextTexture.loadFromRenderedText( "Level 1 ", textColor, gRenderer,gFont);
		
		// điểm
		timeText.str("");
		timeText << "SCORE:: " << count_Broken_Bricks ;

		// số lượt chơi còn lại 
        timeText << " Live:: " << COUNT_DIES;

		//Render text
		if (!gScoreTexture.loadFromRenderedText1(timeText.str().c_str(), textColor,gRenderer,gFont_HighScore))
		{
			printf("Unable to render FPS texture!\n");
		}
		if (!ghigh_Score.loadFromRenderedText1(high_Score.str().c_str(), textColor,gRenderer,gFont_HighScore))
		{
			printf("er!\n");
		}
		
		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

        if(fpsTimer.getTicks()%1000==0){
            i++;
            while(i>4) i-=4;
        }
	
		// render object
		// thay đổi màu của quả bóng theo thời gian 
		dot.render(i);
		paddle.renderP();
		render_Brick_Lv1(brick1);
		gButton1_Pause.render(gRenderer);
		gBgLv1.render(0, 0,gRenderer);// hiện thị khung để chơi 

		gTextTexture.render(0, 10,gRenderer);// LV
		gScoreTexture.render(23, 551,gRenderer);// ĐIỂM
		ghigh_Score.render(150,28,gRenderer);// điểm cao 

		//update screen
		SDL_RenderPresent(gRenderer);
		

		if (COUNT_DIES < 0) {
			Mix_HaltMusic();
			return "lose";
		}
		if(count_Broken_Bricks==TOTAL_BRICKSLV1*50){
			
			quit = true;
			SDL_Delay(100);
			dot.reset();
			return "playlv2";
		}
		if(gButton1_Pause.getStatus()==BUTTON_SPRITE_MOUSE_DOWN)
		{	
			velPauseX=dot.getVelX();
			velPauseY=dot.getVelY();
			dot.set_mVelX(0);
			dot.set_mVelY(0);
			Mix_HaltMusic();
			gButton1_Pause.freeStatus();
			pause();
		}
		
}
}

std::string lose() {
	std::cout<<"lose"<<std::endl;
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;

	// hiện thị điểm thua
    std::stringstream timeTextLose;

	// hiện thị điểm cao 
	std::stringstream high_Score;

	// màu phông chữ 
	SDL_Color textColor = GREEN_COLOR;

	// điểu kiện để bật âm thanh game thua
	if(music){
	Mix_PlayMusic(music_GameOver, -1 );
	}
	
	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				return "quit";
				quit = true;
				
			}
			gButton[RESTART].handleEvent(&e);
			gButton[MAIN_MENU].handleEvent(&e);
			gButton[EXIT].handleEvent(&e);
		}

		// điểm khi thua 
        timeTextLose.str("");
		timeTextLose << "YOU_SCORE:: " << count_Broken_Bricks ;

		// điểm cao 
		high_Score.str("");
		high_Score << "HIGH SCORE:: " << loadhighscore();

		// load texture từ chữ
		if (!gScoreTexture.loadFromRenderedText(timeTextLose.str().c_str(), textColor,gRenderer,gFont_HighScore))
        {
            printf("Unable to render FPS texture!\n");
        }
		{
			printf("Unable to render FPS texture!\n");
		}
		if (!ghigh_Score.loadFromRenderedText(high_Score.str().c_str(), textColor,gRenderer,gFont_HighScore))
		{
			printf("Unable to render FPS texture!\n");
		}
		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0x0F, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		
		//render objects
		gButton[RESTART].render(gRenderer);
		gButton[MAIN_MENU].render(gRenderer);
		gButton[EXIT].render(gRenderer);
        gScoreTexture.render(0,50,gRenderer);
		ghigh_Score.render(0, 90,gRenderer);
		gGameOverTexture.render(00, 150,gRenderer);


		if(gButton[RESTART].getStatus()==BUTTON_SPRITE_MOUSE_DOWN)
		{
			gButton[RESTART].freeStatus();
			count_Broken_Bricks=0;
			quit=true;
			return "playlv1";
			
		}
		else if(gButton[MAIN_MENU].getStatus()==BUTTON_SPRITE_MOUSE_DOWN)
		{	
			gButton[MAIN_MENU].freeStatus();
			count_Broken_Bricks=0;
			quit=true;
			return "menu";
		}
		else if(gButton[EXIT].getStatus()==BUTTON_SPRITE_MOUSE_DOWN)
		{
			gButton[EXIT].freeStatus();
			quit=true;
			return "quit";
		}


		//Update screen
		SDL_RenderPresent(gRenderer);
		
}
}

std::string main_menu(){
	std::cout<<"main_menu"<<std::endl;
    //Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;


	if(music){

	Mix_PlayMusic(music_Menu, -1 );
	}
	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
				return "quit";
			}
			gButton[ABOUT].handleEvent(&e);
			gButton[GAME_PLAY].handleEvent(&e);
			gButton[EXIT].handleEvent(&e);
			gButton[SOUND].handleEvent(&e);
		}
		
		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);
		
		//render objects
		gBg_Mainmenu[0].render(0, 0,gRenderer);
		gBg_Mainmenu[1].render(0, 0,gRenderer);
		gButton[ABOUT].render(gRenderer);
		gButton[GAME_PLAY].render(gRenderer);
		gButton[EXIT].render(gRenderer);
		gButton[SOUND].render(gRenderer);
		

		if(gButton[GAME_PLAY].getStatus()==BUTTON_SPRITE_MOUSE_DOWN){
        	
			gButton[GAME_PLAY].freeStatus();
			quit=true;

			return "playlv1";
           
    	}
		else if(gButton[ABOUT].getStatus()==BUTTON_SPRITE_MOUSE_DOWN){
			quit=true;
			gButton[ABOUT].freeStatus();
			Mix_HaltMusic();
			return "about";
		}
		else if(gButton[SOUND].getStatus()==BUTTON_SPRITE_MOUSE_DOWN){
			quit=true;
			gButton[SOUND].freeStatus();

			Mix_HaltMusic();
			return "sound";
		}
		else if(gButton[EXIT].getStatus()==BUTTON_SPRITE_MOUSE_DOWN){
			std::cout<<"Exit"<<std::endl;
			gButton[EXIT].freeStatus();
			quit=true;
			return "quit";
		}

		//Update screen
		SDL_RenderPresent(gRenderer);
		
	}
}
std::string about(){
	std::cout<<"about"<<std::endl;
    //Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
	//std::stringstream timeText_About;
	SDL_Color textColor = BLACK_COLOR;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
				return "quit";
			}
			 gButton1_Back.handleEvent(&e);

		}
		// //Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0x0F, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//render objects
		gBg_Mainmenu[1].render(0, 0,gRenderer);
		gBg_About.render(0, 300,gRenderer);
		gButton1_Back.render(gRenderer);

		if(gButton1_Back.getStatus()==BUTTON_SPRITE_MOUSE_DOWN){
			gButton1_Back.freeStatus();
			quit=true;
			return "menu";
		}
		//Update screen
		SDL_RenderPresent(gRenderer);
		
	}
}

std::string pause(){
	std::cout<<"pause"<<std::endl;
	bool quit = false;

	//Event handler
	SDL_Event e;
	
	//While application is running
	
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
				return "quit";
			}
			//Handle input for the dot
			dot.handleEvent(e);
			paddle.handleEventPaddle(e);
			gButton[RESUME].handleEvent(&e);
			gButton[SOUND].handleEvent(&e);

		}

		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
		//SDL_RenderClear(gRenderer);

		//render objects
		gButton[RESUME].render(gRenderer);
		gButton[SOUND].render(gRenderer);


		if(gButton[RESUME].getStatus()==BUTTON_SPRITE_MOUSE_DOWN){
			gButton[RESUME].freeStatus();
			quit=true;
			dot.set_mVelX(velPauseX);
			dot.set_mVelY(velPauseY);
			if(music){
				Mix_PlayMusic(music_Play, -1);
			}
			
			return "playlv1";
		}
		if(gButton[SOUND].getStatus()==BUTTON_SPRITE_MOUSE_DOWN){
			gButton[SOUND].freeStatus();
			// quit=true;
			// return "sound";
			sound();
		}

		//Update screen
		SDL_RenderPresent(gRenderer);
		
		
	}

}


class TheGame{

    int status;
    std::string status_next;
    public:
    TheGame(){
    // Initialize the game
    this->status=MAIN_MENU;
    this->status_next="menu";
    }
    int get_Char(){
        return this->status;
    }
    
    void update_Status_Game(){
        if(this->status_next=="playlv1"){
            if(this->status==MAIN_MENU){
                this->status=GAME_PLAY;
            }
            if(this->status==LOSE){
                this->status=GAME_PLAY;
            }
            if(this->status==GAME_PLAY){
                this->status=GAME_PLAY;
                // trường hợp đặc biệt reset lại game cần để ý chỗ này
            }
            if(this->status==WIN){
                this->status=GAME_PLAY;
            }
            if(this->status==PAUSE){
                this->status=GAME_PLAY;
            }
            return;
        }
        if(this->status_next=="playlv2"){
            if(this->status==GAME_PLAY){
                this->status=GAME_PLAY2;
            }
            return;
        }
        if(this->status_next=="playlv3"){
            if(this->status==GAME_PLAY2){
                this->status=GAME_PLAY3;
            }
            return;
        }
        if(this->status_next=="playlv4"){
            if(this->status==GAME_PLAY3){
                this->status=GAME_PLAY4;
            }
            return;
        }   
        if(this->status_next=="playlv5"){
            if(this->status==GAME_PLAY4){
                this->status=GAME_PLAY5;
            }
            return;
        }
        if(this->status_next=="about"){
            if(this->status==MAIN_MENU){
                this->status=ABOUT;
            }
            return;
        }
        if(this->status_next=="sound"){
            if(this->status==MAIN_MENU){
                this->status=SOUND;
            }
            return;
        }
        if(this->status_next=="quit"){
            if(this->status==MAIN_MENU||this->status==GAME_PLAY2||this->status==GAME_PLAY||this->status==GAME_PLAY3||this->status==GAME_PLAY4||this->status==GAME_PLAY5||this->status==ABOUT||this->status==SOUND||this->status==WIN||this->status==LOSE||this->status==PAUSE){
                this->status=EXIT;
            }
        }
        if(this->status_next=="menu"){
            if(this->status==ABOUT){
                this->status=MAIN_MENU;
            }
            if(this->status==SOUND){
                this->status=MAIN_MENU;
            }
            if(this->status==LOSE){
                this->status=MAIN_MENU;
            }
            if(this->status==WIN){
                this->status=MAIN_MENU;
            }
            return;
        }
        if(this->status_next=="lose"){
            if(this->status==GAME_PLAY){
                this->status=LOSE;
            }
            if(this->status==GAME_PLAY2){
                this->status=LOSE;
            }
            if(this->status==GAME_PLAY3){
                this->status=LOSE;
            }
            if(this->status==GAME_PLAY4){
                this->status=LOSE;
            }
            if(this->status==GAME_PLAY5){
                this->status=LOSE;
            }
            return;
        }
        if(this->status_next=="win"){
            if(this->status==GAME_PLAY5){
                this->status=WIN;
            }
            return;
        }
    }
    void render_Game(){
        switch(this->status){
            case MAIN_MENU:
            {
                this->status_next=main_menu();
                break;
            }
            // chỗ này để chạy level thôi :v
            case GAME_PLAY:
            {
                this->status_next=playlv1();
                break;
            }
            case ABOUT:
            {
                this->status_next=about();
                break;
            }
            case SOUND:
            {
                this->status_next=sound();
                break;
            }
            case LOSE :
            {
                this->status_next=lose();
                break;
            }
            case GAME_PLAY2 :
            {
                this->status_next=playlv2();
                break;
            }
            case GAME_PLAY3 :
            {
                this->status_next=playlv3();
                break;
            }
            case GAME_PLAY4 :
            {
                this->status_next=playlv4();
                break;
            }
            case GAME_PLAY5 :
            {
                this->status_next=playlv5();
                break;
            }

            case WIN :
            {
                this->status_next=win();
                break;
            }
        }
    }
};

int main(int argc, char* args[])
{
	init();
	loadMedia();
	
	TheGame* game= new TheGame;
 	game->render_Game();
	while(game->get_Char()!=EXIT){
		game->update_Status_Game();
		game->render_Game();
	}
	close();
	return 0;
}

