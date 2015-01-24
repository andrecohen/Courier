
#include "world.h"

World::World(SDL_Renderer *renderer) {

	_renderer = renderer;

}

void World::update(float offsetX, float offsetY) {


	for(int x=-10; x<10; x++) {
		for(int y=-10; y<10; y++) {
			SDL_SetRenderDrawColor(_renderer,255,255,255,200);	

			SDL_Rect rect;

			rect.w = 150;
			rect.h = 300;
			rect.x = x*(rect.w+200) - offsetX;
			rect.y = y*(rect.h+200) - offsetY;

			// SDL_RenderDrawRect(_renderer, &rect);
			SDL_RenderFillRect(_renderer, &rect);

		}
	}
}