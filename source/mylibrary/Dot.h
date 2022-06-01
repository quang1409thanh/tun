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
        gDot[0].render( mPosX, mPosY ,&gDotRect[0]);
        break;
        case pink:
        gDot[1].render( mPosX, mPosY ,&gDotRect[1]);
        break;
        case purple:
        gDot[2].render( mPosX, mPosY ,&gDotRect[2]);
        break;
        case blue:
        gDot[3].render( mPosX, mPosY ,&gDotRect[3]);
        break;
        case green:
        gDot[4].render( mPosX, mPosY ,&gDotRect[4]);
        break;
    }
}
void Dot::set_gDot_Texture(std::string path,const int &n) {
    gDot[n].loadFromFile(path);
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