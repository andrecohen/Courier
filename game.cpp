#include <iostream>
#include <math.h>

#include "game.h"
#include "world.h"
#include "target.h"


Game::Game(SDL_Renderer *renderer) {

	_renderer = renderer;
	world = new World(renderer);
	currentTarget = new Target(renderer, rand()%1000, rand()%1000);

	wheelAngle = 0;
	wheelAngleDelta = 0;
	speed = 1;
	acceleration = 0;
	length = 50;
	wheelRadius = 13.5;

	heading = 0;
	centerX = 250;
	centerY = 250;
	frontX = -1;
	frontY = -1;


	zoom = 1;
}

void Game::update() {
	

	SDL_Rect screen;
	SDL_RenderGetViewport(_renderer, &screen);
	
	zoom = zoom * .98 + fmax((3-speed)/2.0, .6)*.02;
	SDL_RenderSetScale(_renderer, zoom, zoom);

	float offsetX = centerX - screen.w/2.0;
	float offsetY = centerY - screen.h/2.0;
	
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

	SDL_SetRenderDrawColor(_renderer,0,0,0,255);
	SDL_RenderClear(_renderer);

	updateBike();
	world->update(offsetX, offsetY);
	currentTarget->update(offsetX, offsetY);

	if(currentTarget->inside(centerX, centerY)) {
		delete currentTarget;
		currentTarget = new Target(_renderer, rand()%1000, rand()%1000);
	}

	SDL_SetRenderDrawColor(_renderer,255,255,255,200);	
	SDL_RenderDrawLine(_renderer, backX-offsetX, backY-offsetY, frontX-offsetX, frontY-offsetY);
	SDL_SetRenderDrawColor(_renderer,255,255,255,255);
	SDL_RenderDrawLine(_renderer, frontX-offsetX, frontY-offsetY, frontX + cos((heading+wheelAngle)*M_PI/180.0)*wheelRadius-offsetX, frontY + sin((heading+wheelAngle)*M_PI/180.0)*wheelRadius-offsetY);
	SDL_RenderDrawLine(_renderer, frontX-offsetX, frontY-offsetY, frontX + cos((heading+wheelAngle)*M_PI/180.0+M_PI)*wheelRadius-offsetX, frontY + sin((heading+wheelAngle)*M_PI/180.0+M_PI)*wheelRadius-offsetY);

	drawDirection(offsetX, offsetY);
	
}

void Game::updateBike() {
	if(wheelAngleDelta != 0) {
		wheelAngle += wheelAngleDelta;
		if(wheelAngle>90) wheelAngle = 90;
		if(wheelAngle<-90) wheelAngle = -90;
	}else{
		if(floor(wheelAngle)>0) wheelAngle -= .5;
		if(floor(wheelAngle)<0) wheelAngle += .5;
	}

	if(acceleration != 0) {
		speed += acceleration;
		if(speed>5) speed = 3;
		if(speed<0) speed = 0;
	}else{
		if(speed>1) speed -= .05;
		if(speed<1) speed += .05;
	}

	frontX = centerX + length/2.0 * cos(heading*M_PI/180.0);
	frontY = centerY + length/2.0 * sin(heading*M_PI/180.0);
	backX = centerX - length/2.0 * cos(heading*M_PI/180.0);
	backY = centerY - length/2.0 * sin(heading*M_PI/180.0);


	backX += speed * cos(heading*M_PI/180.0);
	backY += speed * sin(heading*M_PI/180.0);
	frontX += speed * cos((heading+wheelAngle)*M_PI/180.0);
	frontY += speed * sin((heading+wheelAngle)*M_PI/180.0);

	centerX = (frontX+backX)/2.0;
	centerY = (frontY+backY)/2.0;

	heading = atan2(frontY-backY, frontX-backX)*180.0/M_PI;
	

}

//SDL_SCANCODE_LEFT
void Game::keyDown(int key) {
	
	switch(key) {
		case SDL_SCANCODE_LEFT:		wheelAngleDelta = -1; break;
		case SDL_SCANCODE_RIGHT:	wheelAngleDelta = 1; break;
		case SDL_SCANCODE_UP:		acceleration = .05; break;
		case SDL_SCANCODE_DOWN:		acceleration = -.05; break;
	}

}

void Game::keyUp(int key) {
	
	switch(key) {
		case SDL_SCANCODE_LEFT:		wheelAngleDelta = 0; break;
		case SDL_SCANCODE_RIGHT:	wheelAngleDelta = 0; break;
		case SDL_SCANCODE_UP:		acceleration = 0; break;
		case SDL_SCANCODE_DOWN:		acceleration = 0; break;
	
	}

}

void Game::drawDirection(float offsetX, float offsetY) {

	SDL_SetRenderDrawColor(_renderer, 228, 199, 68, 255);
	SDL_Rect rect;

	float angle = atan((currentTarget->y-centerY)/(currentTarget->x-centerX));

	rect.x = centerX + cos(angle)*60 - offsetX;
	rect.y = centerY + sin(angle)*60 - offsetY;

	rect.w = 10;
	rect.h = 10;

	SDL_RenderDrawRect(_renderer, &rect);

}