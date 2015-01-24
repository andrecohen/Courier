#ifndef _WORLD_H_
#define _WORLD_H_

#include <SDL.h>

class World {

public: 

	World(SDL_Renderer *);

	void update(float, float);

private:

	SDL_Renderer *_renderer;

};


#endif