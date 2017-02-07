#include "sfwdraw.h"
#include "math.h"

using namespace sfw;

void main()
{
	sfw::initContext();

	unsigned sprite = sfw::loadTextureMap("../res/particle_sprite.png");
	float angle = 0.f;

	color startCol, endCol;

	startCol.ui_color = MAGENTA;
	endCol.ui_color = CYAN;
	float timer = 0;

	while (sfw::stepContext())
	{
		timer += sfw::getDeltaTime();

		color curCol = lerp(startCol, endCol, timer / 10.f);

		sfw::drawTexture(sprite, 400, 300, 100, 100, angle, true, 0, curCol.ui_color);
		angle += sfw::getDeltaTime() * 10;
	}

	sfw::termContext();
}