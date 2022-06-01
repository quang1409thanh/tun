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

// số màu của viên gạch
const int TOTAL_COLOR_BRICK = 10;

// khai báo 2 biến để giữa vel lúc pause
int velPauseX=0;
int velPauseY=0;

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

// trạng thái của chuột
enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

// trạng thái của game
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

// màu của quả bóng (dot)
enum color{
    red=0,
    pink=1,
    purple=2,
    blue=3,
    green=4,
    TOTAL_COLOR=5
};
//khai báo các hình chữ nhật để load các Texture khác nhau hình ảnh button 
SDL_Rect gSpriteClips[4];

//khai báo các hình chữ nhật để load các Texture khác nhau hình ảnh button loại 2
SDL_Rect gSpriteClips1[4];

//khai báo các hình chữ nhật để load các Texture khác nhau hình ảnh button loại 3
SDL_Rect gSpriteClips2[4];

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