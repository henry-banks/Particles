#pragma once
#include "Particle.h"
#include <vector>

using namespace std;
#define PART_SIZE 24

class ParticleEmitter
{
	particle particles[PART_SIZE];
	float emissionTimer;

	/////////////////////////////////////////////////////////
	void emit()
	{
		for (int i = 0; i < PART_SIZE; i++)
		{
			if (!particles[i].isActive())
			{
				particles[i] = _generate();
				return;
			}
		}
	}

	particle _generate()
	{
		particle part;
		part.pos = pos;
		part.sprite = sprite;

		part.vel = randDir(angLow, angHigh) * lerp(speedLow, speedHigh, rand01());

		part.lifespan = lerp(lifespawnLow, lifespanHigh, rand01());

		part.sColor = lerp(colLowStart, colHighStart, rand01());
		part.eColor = lerp(colLowEnd, colHighEnd, rand01());

		part.sDim = lerp(dimLowStart, dimHighStart, rand01());
		part.eDim = lerp(dimLowEnd, dimHighEnd, rand01());

		part.lifetime = 0;
		return part;
	}

	/////////////////////////////////////////////////////////

public:

	ParticleEmitter() : emissionTimer(0) {}

	//Emissions
	float emitRateLow, emitRateHigh;

	//Defaults
	vec2 pos;							//THE POSITION
	unsigned sprite;					//THE SPRITE
	float angLow, angHigh;				//direction
	float speedLow, speedHigh;			//speed = velocity
	vec2 dimLowStart, dimHighStart;		//range of starting dimensions
	vec2 dimLowEnd, dimHighEnd;			//range of ending dimensions
	color colLowStart, colHighStart;	//start color range
	color colLowEnd, colHighEnd;		//end color range
	float lifespawnLow, lifespanHigh;	//lifespan range

	//////////////////////////////////////

	void update(float dt)
	{
		for (int i = 0; i < PART_SIZE; ++i)
		{
			if (particles[i].isActive())
				particles[i].refresh(dt);
		}

		emissionTimer -= dt;
		while (emissionTimer < 0)
		{
			emit();
			emissionTimer += lerp(emitRateLow, emitRateHigh, rand01());
		}
	}
};