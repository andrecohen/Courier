#include <iostream>
#include <SDL.h>

#include "game.h"

int main(int argc, char **argv) {

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("Courier", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if(window == NULL)
		return 0;
	
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
	if(renderer == NULL)
		return 0;

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	SDL_RenderClear(renderer);

	Game *game = new Game(renderer);

	int lastTime = SDL_GetTicks();
	int frames = 0;
	while(true) {
		

		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_KEYDOWN) {
				int key = event.key.keysym.scancode;
				
				if(key == SDL_SCANCODE_ESCAPE){
					return 0;
				}

				game->keyDown(key);
			}else if(event.type == SDL_KEYUP) {
				game->keyUp(event.key.keysym.scancode);
			}
		}

		game->update();

		SDL_RenderPresent(renderer);

		frames++;
		if(SDL_GetTicks()-lastTime>1000) {
			std::cout<<frames<<", "<<(frames*1.0/(SDL_GetTicks()-lastTime)*1000)<<" fps\n";
			lastTime = SDL_GetTicks();
			frames = 0;
		}

		SDL_Delay(10);
	}


	SDL_Quit();

	return 0;
}