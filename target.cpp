#include "target.h"


Target::Target(SDL_Renderer *renderer, float targetX, float targetY) {
	_renderer = renderer;
	x = targetX;
	y = targetY;
	counter = 0;
}

void Target::update(float offsetX, float offsetY) {
	SDL_SetRenderDrawColor(_renderer,0,255,0,200);	

	SDL_Rect rect;
	counter += .01;
	float rad = sin(counter)*5+15;
	rect.x = x-rad-offsetX;
	rect.y = y-rad-offsetY;
	rect.w = 2*rad;
	rect.h = 2*rad;

	SDL_RenderFillRect(_renderer, &rect);
}

bool Target::inside(float pX, float pY) {
	return (abs(x-pX)<20 && abs(y-pY)<20);
}