#pragma once

#include "math.h"
#include "sfwdraw.h"
#include "ObjPool.h"
//sooper simpul
//Basic component-entity system (like unity/unreal :D )

using namespace sfw;

struct transform
{
	vec2 pos, scl;
	float angle;
};

struct rigidbody
{
	vec2 velocity, acceleration;
	void integrate(transform &t, float dt)
	{
		velocity = velocity + acceleration * dt;
		t.pos = t.pos + velocity * dt;
	}
};

struct lifetime
{
	float time = 0, lifespan;

	void age(float dt) { time += dt; }
	bool isAlive() const { return time < lifespan; }
	float pctAlive() const { return time / lifespan; } //percent alive
};

struct sprite
{
	size_t id;
	color tint = { WHITE };
	
	void draw(const transform &t) { drawTexture(id, t.pos.x, t.pos.y, t.scl.x, t.scl.y, t.angle, 0, tint.ui_color); }
};

struct controller
{
	float speed;

	//anything with the controller component will follow the mouse
	void poll(transform &t, rigidbody &r)
	{
		vec2 mouse = vec2{ getMouseX(), getMouseY() };
		r.acceleration = normal(mouse - t.pos) * speed;
	}
};

//:/
struct particle
{
	vec2 sDim, eDim;
	color sColor, eColor;
	
	void update(const lifetime &l, transform &t, sprite &s)
	{
		t.scl = lerp(sDim, eDim, l.pctAlive());
		s.tint = lerp(sColor, eColor, l.pctAlive());
	}
};