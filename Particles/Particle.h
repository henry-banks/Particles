#pragma once
#include "sfwdraw.h"
#include "math.h"

using namespace sfw;

struct particle
{
	particle() : lifespan(-1), lifetime(0) {}

	unsigned sprite;
	vec2 pos, vel;
	//Start/End dimensions
	vec2 sDim, eDim;
	color sColor, eColor;

	float lifetime, lifespan;

	//laziness
	bool refresh(float dt)
	{
		lifetime += dt;

		float alpha = lifetime / lifespan;
		vec2 dim = lerp(sDim, eDim, alpha);
		color col = lerp(sColor, eColor, alpha);	//do need fix

		pos = pos + vel * dt;

		sfw::drawTexture(sprite, pos.x, pos.y, dim.x, dim.y, 0, true, 0, col.ui_color);

		//Determines if particle is still alive or not
		return alpha < 1;
	}

	bool isActive() const { return lifetime > lifespan; }
};