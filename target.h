#ifndef _TARGET_H_
#define _TARGET_H_


#include <SDL.h>

class Target {

public:
	Target(SDL_Renderer *, float, float);


	void update(float, float);

	bool inside(float, float);

	float x, y;

private:

	SDL_Renderer *_renderer;
	float counter;

};

#endif