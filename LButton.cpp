
#include"LButton.h"

//================các hàm thành viên của button================

//khai báo các hình chữ nhật để load các Texture khác nhau hình ảnh button 
SDL_Rect gSpriteClips[4];

//khai báo các hình chữ nhật để load các Texture khác nhau hình ảnh button loại 2
SDL_Rect gSpriteClips1[4];

//khai báo các hình chữ nhật để load các Texture khác nhau hình ảnh button loại 3
SDL_Rect gSpriteClips2[4];


LButtonSprite LButton::getStatus() {
	return mCurrentSprite;
}


LButton::LButton()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition( int x, int y )
{
    mPosition.x = x;
    mPosition.y = y;
}

void LButton::handleEvent( SDL_Event* e )
{
    //If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
		//Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if( x < mPosition.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > mPosition.x + BUTTON_WIDTH )
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < mPosition.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > mPosition.y + BUTTON_HEIGHT )
        {
            inside = false;
        }
		//Mouse is outside button
        if( !inside )
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch( e->type )
            {
                case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            
                case SDL_MOUSEBUTTONDOWN:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
                
                case SDL_MOUSEBUTTONUP:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                break; //thừa
            }
        }
    }
}

void LButton::render(SDL_Renderer*& gRenderer)
{
   //Show current button sprite
	switch (mCurrentSprite) {
	case BUTTON_SPRITE_MOUSE_OUT: {
		texture[0].render(mPosition.x, mPosition.y,gRenderer,&gSpriteClips[ mCurrentSprite ] );
		break;
	}
	case BUTTON_SPRITE_MOUSE_OVER_MOTION: {
		texture[1].render(mPosition.x, mPosition.y,gRenderer,&gSpriteClips[ mCurrentSprite ] );
	}
	case BUTTON_SPRITE_MOUSE_DOWN: {
		texture[2].render(mPosition.x, mPosition.y,gRenderer,&gSpriteClips[ mCurrentSprite ] );
	}
	case BUTTON_SPRITE_MOUSE_UP: {
		texture[3].render(mPosition.x, mPosition.y,gRenderer,&gSpriteClips[ mCurrentSprite ] );
	}
	}
}

void LButton::set_texture(std::string path,const int &n,SDL_Renderer*& gRenderer) {
	texture[n].loadFromFile(path,gRenderer);
			gSpriteClips[ 0 ].x = 0;
			gSpriteClips[ 0].y = 0;
			gSpriteClips[ 0 ].w = BUTTON_WIDTH;
			gSpriteClips[ 0 ].h = BUTTON_HEIGHT;
	
			gSpriteClips[ 1 ].x = 179;
			gSpriteClips[ 1 ].y = 0;
			gSpriteClips[ 1 ].w = BUTTON_WIDTH;
			gSpriteClips[ 1 ].h = BUTTON_HEIGHT;

			gSpriteClips[ 2 ].x = 358;
			gSpriteClips[ 2 ].y = 0;
			gSpriteClips[ 2 ].w = BUTTON_WIDTH;
			gSpriteClips[ 2 ].h = BUTTON_HEIGHT;
			gSpriteClips[ 3 ].x = 0;
			gSpriteClips[ 3 ].y = 0;
			gSpriteClips[ 3 ].w = BUTTON_WIDTH;
			gSpriteClips[ 3 ].h = BUTTON_HEIGHT;
}



void LButton::freeStatus() {
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}
void LButton::freeB(){
    texture[0].free();
    texture[1].free();
    texture[2].free();
    texture[3].free();
}

//=====================các hàm thành viên của LButton1=====================

LButtonSprite LButton1::getStatus() {
	return mCurrentSprite;
}


LButton1::LButton1()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton1::setPosition( int x, int y )
{
    mPosition.x = x;
    mPosition.y = y;
}

void LButton1::handleEvent( SDL_Event* e )
{
    //If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
		//Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if( x < mPosition.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > mPosition.x + BUTTON_WIDTH1 )
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < mPosition.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > mPosition.y + BUTTON_HEIGHT1 )
        {
            inside = false;
        }
		//Mouse is outside button
        if( !inside )
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch( e->type )
            {
                case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            
                case SDL_MOUSEBUTTONDOWN:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
                
                case SDL_MOUSEBUTTONUP:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                break; //thừa
            }
        }
    }
}

void LButton1::render(SDL_Renderer*& gRenderer)
{
   //Show current button sprite
	switch (mCurrentSprite) {
	case BUTTON_SPRITE_MOUSE_OUT: {
		texture[0].render(mPosition.x, mPosition.y,gRenderer,&gSpriteClips1[ mCurrentSprite ] );
		break;
	}
	case BUTTON_SPRITE_MOUSE_OVER_MOTION: {
		texture[1].render(mPosition.x, mPosition.y,gRenderer,&gSpriteClips1[ mCurrentSprite ] );
	}
	case BUTTON_SPRITE_MOUSE_DOWN: {
		texture[2].render(mPosition.x, mPosition.y,gRenderer,&gSpriteClips1[ mCurrentSprite ] );
	}
	case BUTTON_SPRITE_MOUSE_UP: {
		texture[3].render(mPosition.x, mPosition.y,gRenderer,&gSpriteClips1[ mCurrentSprite ] );
	}
	}
}

void LButton1::set_texture(std::string path,const int &n,SDL_Renderer*& gRenderer) {
	texture[n].loadFromFile(path,gRenderer);
			gSpriteClips1[ 0 ].x = 0;
			gSpriteClips1[ 0].y = 0;
			gSpriteClips1[ 0 ].w = BUTTON_WIDTH1;
			gSpriteClips1[ 0 ].h = BUTTON_HEIGHT1;
	
			gSpriteClips1[ 1 ].x = 40;
			gSpriteClips1[ 1 ].y = 0;
			gSpriteClips1[ 1 ].w = BUTTON_WIDTH1;
			gSpriteClips1[ 1 ].h = BUTTON_HEIGHT1;

			gSpriteClips1[ 2 ].x = 80;
			gSpriteClips1[ 2 ].y = 0;
			gSpriteClips1[ 2 ].w = BUTTON_WIDTH1;
			gSpriteClips1[ 2 ].h = BUTTON_HEIGHT1;
			gSpriteClips1[ 3 ].x = 0;
			gSpriteClips1[ 3 ].y = 0;
			gSpriteClips1[ 3 ].w = BUTTON_WIDTH1;
			gSpriteClips1[ 3 ].h = BUTTON_HEIGHT1;
}



void LButton1::freeStatus() {
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
}
void LButton1::freeB() {
    texture[0].free();
    texture[1].free();
    texture[2].free();
    texture[3].free();
}

bool LButton2::get_on() {
	return on;
}
LButtonSprite LButton2::getStatus() {
	return mCurrentSprite;
}

void LButton2::set_on(bool b) {
	on = b;
}
LButton2::LButton2()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    on=true;
}

void LButton2::setPosition( int x, int y )
{
    mPosition.x = x;
    mPosition.y = y;
}

void LButton2::handleEvent( SDL_Event* e )
{
    //If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
		//Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if( x < mPosition.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > mPosition.x + BUTTON_WIDTH2 )
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < mPosition.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > mPosition.y + BUTTON_HEIGHT2 )
        {
            inside = false;
        }
		//Mouse is outside button
        if( !inside )
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch( e->type )
            {
                case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            
                case SDL_MOUSEBUTTONDOWN:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
            }
        }
    }
}

void LButton2::render(SDL_Renderer*& gRenderer)
{
   //Show current button sprite
    
	if(mCurrentSprite == BUTTON_SPRITE_MOUSE_OUT && on){
        texture[0].render(mPosition.x, mPosition.y,gRenderer,&gSpriteClips2[0]);
    }
    else if(mCurrentSprite == BUTTON_SPRITE_MOUSE_OVER_MOTION && on)
        {
            texture[1].render(mPosition.x, mPosition.y,gRenderer,&gSpriteClips2[1]);
            //setup_Sound_Off(music,sfx);
        }
    else if(mCurrentSprite == BUTTON_SPRITE_MOUSE_OUT && !on)

        texture[2].render(mPosition.x, mPosition.y,gRenderer,&gSpriteClips2[2]);

    else if(mCurrentSprite == BUTTON_SPRITE_MOUSE_OVER_MOTION  && !on)
        {
            texture[3].render(mPosition.x, mPosition.y,gRenderer,&gSpriteClips2[3]);
            //setup_Sound_On(music,sfx);
        }
}

void LButton2::set_texture(std::string path,const int &n,SDL_Renderer*& gRenderer) {
	texture[n].loadFromFile(path,gRenderer);
			gSpriteClips2[ 0 ].x = 0;
			gSpriteClips2[ 0].y = 0;
			gSpriteClips2[ 0 ].w = BUTTON_WIDTH2;
			gSpriteClips2[ 0 ].h = BUTTON_HEIGHT2;
            gSpriteClips2[ 1 ].x = 179;
			gSpriteClips2[ 1 ].y = 0;
			gSpriteClips2[ 1 ].w = BUTTON_WIDTH2;
			gSpriteClips2[ 1 ].h = BUTTON_HEIGHT2;
            gSpriteClips2[ 2 ].x = 0;
			gSpriteClips2[ 2 ].y = 0;
			gSpriteClips2[ 2 ].w = BUTTON_WIDTH2;
			gSpriteClips2[ 2 ].h = BUTTON_HEIGHT2;
            gSpriteClips2[ 3 ].x = 179;
			gSpriteClips2[ 3 ].y = 0;
			gSpriteClips2[ 3 ].w = BUTTON_WIDTH2;
			gSpriteClips2[ 3 ].h = BUTTON_HEIGHT2;
}



void LButton2::freeStatus() {
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton2::freeB() {
    texture[0].free();
    texture[1].free();
    texture[2].free();
    texture[3].free();
}
