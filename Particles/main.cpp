#include "sfwdraw.h"
#include "math.h"
#include "ParticleEmitter.h"
#include "ObjPool.h"
#include "Factory.h"
#include <string>

using namespace sfw;

void drawFire(const unsigned &fire, int &fireCount)
{
	string s(1, fireCount);
	sfw::drawString(fire, s.c_str(), 200, 200, 60, 60, 0, '\0', YELLOW);

	if (fireCount >= 36)
		fireCount = 1;
	else
		fireCount++;
}

void main()
{
	sfw::initContext();

	unsigned sprite = sfw::loadTextureMap("../res/tormp.png");
	unsigned fire = loadTextureMap("../res/fire_map.png", 6, 6);
	float angle = 0.f;

	Factory fact;

	int fireCount = 1;

	while (sfw::stepContext())
	{
		float dt = getDeltaTime();

		for (auto e = fact.begin(); e != fact.end();)
		{
			bool wasDestroyed = false;

			if (e->sp)
				e->sp->draw(*e->trans);

			if (e->life)
			{
				e->life->age(dt);
				if (!e->life->isAlive())
				{
					fact.destroy(e);
					continue;
				}
			}
			e++;
		}

		//drawFire(fire, fireCount);
	}

	sfw::termContext();
}