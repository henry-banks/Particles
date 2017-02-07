#include "sfwdraw.h"

void main()
{
	sfw::initContext();

	unsigned sprite = sfw::loadTextureMap("../res/particle_sprite.png");
	float angle = 0.f;

	while (sfw::stepContext())
	{
		sfw::drawTexture(sprite, 400, 300, 100, 100, angle, true, 0, MAGENTA);
		angle += sfw::getDeltaTime() * 10;
	}

	sfw::termContext();
}