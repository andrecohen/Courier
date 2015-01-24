#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>

class World;
class Target;


class Game {

public: 

	Game(SDL_Renderer *);


	void update();
	void updateBike();
	void drawDirection(float, float);

	void keyDown(int);
	void keyUp(int);

private:

	SDL_Renderer *_renderer;

	World *world;
	Target *currentTarget;

	float wheelAngle;
	float wheelAngleDelta;
	float heading;
	float speed;
	float acceleration;
	float length;
	float wheelRadius;
	float centerX;
	float centerY;
	float backX;
	float backY;
	float frontX;
	float frontY;

	float zoom;
};


#endif 