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
	gBricksTexture[BLUE].loadFromFile("source/Data/img/bricks/blue.png");
	gBricksTexture[RED].loadFromFile("source/Data/img/bricks/red.png");
	gBricksTexture[GREEN].loadFromFile("source/Data/img/bricks/green.png");
	gBricksTexture[DARK_GREEN].loadFromFile("source/Data/img/bricks/darkgreen.png");
	gBricksTexture[INDIGO].loadFromFile("source/Data/img/bricks/indigo.png");
	gBricksTexture[ORANGE].loadFromFile("source/Data/img/bricks/orange.png");
	gBricksTexture[PINK].loadFromFile("source/Data/img/bricks/pink.png");
	gBricksTexture[SOLID].loadFromFile("source/Data/img/bricks/solid.png");
	gBricksTexture[VIOLET].loadFromFile("source/Data/img/bricks/violet.png");
	gBricksTexture[YELLOW].loadFromFile("source/Data/img/bricks/yellow.png");

	// load mái chéo paddle
	gPaddleTexture.loadFromFile("source/Data/img/paddle/paddlemedium.png");
	
	// load hình ảnh quả bóng

	for(int i=0;i<5;i++){
	dot.set_gDot_Texture("source/Data/img/anim/ballanim.png",i);
	}

	// load background 
	gGameOverTexture.loadFromFile("source/Data/img/bg/gameover.png");
	
	gGameWin.loadFromFile("source/Data/img/bg/win.png");
	gBg_Mainmenu[0].loadFromFile("source/Data/img/bg/bg_main_menu.jpg");
	gBg_Mainmenu[1].loadFromFile("source/Data/img/bg/bg_main_menu1.png");
	gBg_About.loadFromFile("source/Data/img/bg/gBg_About.png");

	gBgLv1.loadFromFile("source/Data/img/bg.png");

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
	gButton[ABOUT].set_texture("source/Data/img/buttons/aboutbutton.png",i);
	}
	gButton[ABOUT].setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT-70 -2*BUTTON_HEIGHT- 2*BUTTON_HEIGHT/8);

	for(int i=0;i<4;i++){
	gButton[GAME_PLAY].set_texture("source/Data/img/buttons/playbutton.png",i);
	}
	gButton[GAME_PLAY].setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2,SCREEN_HEIGHT-70 -3*BUTTON_HEIGHT- 3*BUTTON_HEIGHT/8);

	for(int i=0;i<4;i++){
	gButton[EXIT].set_texture("source/Data/img/buttons/exitbutton.png",i);
	}
	gButton[EXIT].setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT -70 );

	for(int i=0;i<4;i++){
	gButton[SOUND].set_texture("source/Data/img/buttons/soundbutton.png",i);
	}
	gButton[SOUND].setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT-70 -BUTTON_HEIGHT- BUTTON_HEIGHT/8);

	for(int i=0;i<4;i++){
		gButton[RESUME].set_texture("source/Data/img/buttons/resumebutton.png",i);
	}
	gButton[RESUME].setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT-70 -2*BUTTON_HEIGHT- 2*BUTTON_HEIGHT/8);

	for(int i=0;i<4;i++){
	gButton[RESTART].set_texture("source/Data/img/buttons/restartbutton.png",i);
	}
	gButton[RESTART].setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2,SCREEN_HEIGHT-70 -BUTTON_HEIGHT- BUTTON_HEIGHT/8);

	for(int i=0;i<4;i++){
	gButton[MAIN_MENU].set_texture("source/Data/img/buttons/mainmenubutton.png",i);
	}
	gButton[MAIN_MENU].setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT-70 -2*BUTTON_HEIGHT- 2*BUTTON_HEIGHT/8);

	// load button1
	for(int i=0;i<4;i++){
	gButton1_Pause.set_texture("source/Data/img/buttons/pausebutton.png",i);
	}
	gButton1_Pause.setPosition(SCREEN_WIDTH-SCREEN_RIGHT-BUTTON_WIDTH1-BUTTON_WIDTH1-2, 544);

	for(int i=0;i<4;i++){
	gButton1_Back.set_texture("source/Data/img/buttons/backbutton.png",i);
	}
	gButton1_Back.setPosition(8, 12);


	// load button2
	gButtonsfx.set_texture("source/Data/img/buttons/sfxoffbutton.png",0);
	gButtonsfx.set_texture("source/Data/img/buttons/sfxoffbutton.png",1);
	gButtonsfx.set_texture("source/Data/img/buttons/sfxonbutton.png",2);
	gButtonsfx.set_texture("source/Data/img/buttons/sfxonbutton.png",3);
	gButtonsfx.setPosition(SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT-70 -BUTTON_HEIGHT- BUTTON_HEIGHT/8);
	gButtonmusic.set_texture("source/Data/img/buttons/musicoffbutton.png",0);
	gButtonmusic.set_texture("source/Data/img/buttons/musicoffbutton.png",1);
	gButtonmusic.set_texture("source/Data/img/buttons/musiconbutton.png",2);
	gButtonmusic.set_texture("source/Data/img/buttons/musiconbutton.png",3);
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
		brick[i].renderB(color1[i]);
	}
}
void render_Brick_Lv2(Brick brick[]){
	vector<char> color2=load_Color("source/Data/data_txt/lev2C.txt");
	for(int i=0;i<TOTAL_BRICKSLV2;i++){
		brick[i].renderB(color2[i]);
	}
}
void render_Brick_Lv3(Brick brick[]){
	vector<char> color3=load_Color("source/Data/data_txt/lev3C.txt");
	for(int i=0;i<TOTAL_BRICKSLV3;i++){
		brick[i].renderB(color3[i]);
	}
}
void render_Brick_Lv4(Brick brick[]){
	vector<char> color4=load_Color("source/Data/data_txt/lev4C.txt");
	for(int i=0;i<TOTAL_BRICKSLV4;i++){
		brick[i].renderB(color4[i]);
	}
}
void render_Brick_Lv5(Brick brick[]){
	vector<char> color5=load_Color("source/Data/data_txt/lev5C.txt");
	for(int i=0;i<TOTAL_BRICKSLV5;i++){
		brick[i].renderB(color5[i]);
	}
}