/* Stephen's Tutorials (https://stephenmeier.net/)
gcc main.c -o game.exe -I./include -L./lib -lSDL2main -lSDL2
running on gcc 4.8.1, SDL 2.0.1
*/
 
//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
 
//----------------------------------------------------------------------
#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
 
//----------------------------------------------------------------------
void game_init(void);
void game_quit(void);
 
static struct {
	// define "attributes"
	SDL_bool running;
 
	// define "methods"
	void (*init)(void);
	void (*quit)(void);
} Game = {
	SDL_FALSE,
	game_init,
	game_quit
};
 
//----------------------------------------------------------------------
void game_init(void) {
	printf("game_init()n");
 
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0) {
		printf("SDL error -> %sn", SDL_GetError());
		exit(1);
	}
 
	Game.running = SDL_TRUE;
}
 
//----------------------------------------------------------------------
void game_quit(void) {
	printf("game_quit()n");
	SDL_Quit();
	Game.running = SDL_FALSE;
}
 
//----------------------------------------------------------------------
int main(int argc, char* argv[]) {
 
	Game.init();

	printf("running = %dn", Game.running);
 
	while(Game.running) {
		Game.quit();
	}
 
	printf("running = %dn", Game.running);
 
	return 0;
}