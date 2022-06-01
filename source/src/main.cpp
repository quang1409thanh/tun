#include"source/mylibrary/TheGame.h"
int main(int argc, char* args[])
{
	init();
	loadMedia();
 	//game.render_Game();
	while(game.get_Char()!=EXIT){
		game.update_Status_Game();
		game.render_Game();
	}
	close();
	return 0;
}
