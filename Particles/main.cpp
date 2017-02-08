#include "sfwdraw.h"
#include "math.h"
#include "ParticleEmitter.h"
#include <string>

using namespace sfw;

void main()
{
	sfw::initContext();

	unsigned sprite = sfw::loadTextureMap("../res/tormp.png");
	unsigned fire = loadTextureMap("../res/fire_map.png", 6, 6);
	float angle = 0.f;

	ParticleEmitter pe;

	pe.sprite = sprite;

	pe.emitRateLow = .1f;
	pe.emitRateHigh = .3f;

	pe.pos = vec2{ 400,300 };
	pe.angLow = 0;
	pe.angHigh = 360;
	pe.speedLow = 30;
	pe.speedHigh = 80;
	pe.dimLowStart = vec2{ 8,8 };
	pe.dimHighStart = vec2{ 64,64 };
	pe.dimLowEnd = vec2{ 256,256 };
	pe.dimHighEnd = vec2{ 1024,1024 };

	pe.colLowStart.ui_color = RED;
	pe.colHighStart.ui_color = YELLOW;
	pe.colLowEnd.ui_color = YELLOW;
	pe.colHighEnd.ui_color = RED;

	pe.lifespawnLow = 3.f;
	pe.lifespanHigh = 5.f;

	int fireCount = 1;

	while (sfw::stepContext())
	{
		float dt = getDeltaTime();

		//pe.update(dt);

		string s(1, fireCount);
		sfw::drawString(fire, s.c_str(), 200, 200, 60, 60, 0, '\0', YELLOW);
		
		if (fireCount >= 36)
			fireCount = 1;
		else
			fireCount++;
	}

	sfw::termContext();
}