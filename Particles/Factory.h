#pragma once
#include "components.h"
#include "ObjPool.h"


//templated alias/templeted typedef
//lets you create a data type set to a long thing that you don't want to type over and over again
template<typename T>
using handle = ObjectPool<T>::iterator;

struct Entity
{
	class Factory		*fact;
	handle<transform>	trans;
	handle<rigidbody>	rb;
	handle<controller>	ctrl;
	handle<sprite>		sp;
	handle<lifetime>	life;
	handle <particle>	part;

	void update(float dt)
	{

	}

	void onFree()
	{
		//if thing is valid, free it
		if (trans) trans.free();
		if (rb) rb.free();
		if (ctrl) ctrl.free();
		if (sp) sp.free();
		if (life) life.free();
		if (part) part.free();
	}
};

class Factory
{
	ObjectPool<Entity>		entities;
	ObjectPool<transform>	transforms;
	ObjectPool<rigidbody>	rigidbodies;
	ObjectPool<controller>	controllers;
	ObjectPool<sprite>		sprites;
	ObjectPool<lifetime>	lifetimes;
	ObjectPool<particle>	particles;

public:

	Factory() : entities(512), transforms(512), rigidbodies(512), controllers(512), sprites(512), lifetimes(512), particles(512) {}

	handle<Entity> destroy(handle<Entity> &ent) { ent->onFree(); return ent.free(); }

	handle<Entity> begin()	{ return entities.begin(); }
	handle<Entity> end()	{ return entities.end(); }

	handle<Entity> spawnStaticImage(unsigned id, float x, float y, float w, float h, float time = -1)
	{
		handle<Entity> out = entities.push();
		out->fact = this;

		out->trans = transforms.push();
		out->sp = sprites.push();

		out->trans->pos = vec2{ x,y };
		out->trans->scl = vec2{ w,h };
		out->sp->id = id;

		if (time > 0)
		{
			out->life = lifetimes.push();
			out->life->time = time;
		}

		return out;
	}
};



/*
Work it
Make it
Do it
Make us

Harder
Better
Faster
Stronger

More than
Hour
Our
Never

Ever
After
Work is
Over

Work it
Make it
Do it
Make us

Harder
Better
Faster
Stronger

Work it harder
Make it better
Do it faster
Makes us stronger

More than ever
Hour after
Our work is
Never over

Work it harder
Make it better
Do it faster
Makes us stronger

Work it harder
Make it better
Do it faster
Makes us stronger

Work it harder
Make it better
Do it faster
Makes us stronger

Work it harder
Make it better
Do it faster
Makes us stronger

Work it harder
Make it better
Do it faster
Makes us stronger

Work it harder
Make it better
Do it faster
Makes us stronger

Work it harder make it
Do it faster makes us
More than ever hour
Our work is

Work it harder make it
Do it faster makes us
More than ever hour
Our work is never over

Work it harder
Make it better
Do it faster
Makes us stronger

Work it harder make it
Do it faster makes us
More than ever hour
Our work is

Work it harder make it
Do it faster makes us
More than ever hour
Our work is never over

Work it harder
Make it better
Do it faster
Makes us stronger

Work it harder
Do it faster
More than ever
Our work is never over

Work it harder
Make it better
Do it faster
Makes us stronger
*/