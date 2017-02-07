#include "sfwdraw.h"
#include "math.h"
#include "Particle.h"

using namespace sfw;

void main()
{
	sfw::initContext();

	unsigned sprite = sfw::loadTextureMap("../res/radial_gradient.png");
	float angle = 0.f;

	particle part;
	part.sprite = sprite;
	part.pos = vec2{ 400,300 };
	part.vel = randDir(0,360) * lerp(20,80, rand01());
	part.sDim = randRange(vec2{ 8,8 }, vec2{ 32,32 });
	part.eDim = randRange(vec2{ 256,256 }, vec2{ 512,512 });
	part.sColor.ui_color = GREEN;
	part.eColor.ui_color = BLUE;
	part.lifespan = 6.f;
	part.lifetime = 0;

	while (sfw::stepContext())
	{
		float dt = sfw::getDeltaTime();
		if (!part.refresh(dt))
		{
			part.pos = vec2{ 400,0 };
			part.vel = vec2{ 0,20 };
			part.lifetime = 0;
		}
	}

	sfw::termContext();
}