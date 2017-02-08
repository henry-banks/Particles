#pragma once
#include <random>

//Random value between 0-1
inline float rand01() { return (float)rand() / RAND_MAX; }

inline float lerp(float s, float e, float t) { return s*(1-t) + e*t; }

//Multiply a degree by this to convert it to a radian
#define DEG2RAD	 0.0174533

///////////////////////////////////////////////////////////

struct vec2 { float x, y; };

inline vec2 operator+(const vec2 &a, const vec2 &b)
{ return vec2{ a.x + b.x, a.y + b.y }; }

inline vec2 operator-(const vec2 &a, const vec2 &b)
{ return vec2{ a.x - b.x, a.y - b.y }; }

inline vec2 operator*(const vec2 &a, float b)
{ return vec2{ a.x*b, a.y*b }; }
inline vec2 operator*(const vec2 &a, const vec2 &b)
{ return vec2{ a.x*b.x, a.y*b.y }; }

inline vec2 lerp(const vec2 &s, const vec2 &e, float t)
{ return s*(1 - t) + e*t; }

inline vec2 randRange(const vec2 &a, const vec2 &b)
{
	return vec2{ lerp(a.x, b.x, rand01()), lerp(a.y,b.y,rand01()) };
}

inline vec2 randDir(float min_deg, float max_deg)
{
	float deg = lerp(min_deg, max_deg, rand01());
	float rad = DEG2RAD * deg;

	return vec2{ cos(rad), sin(rad) };
}

//////////////////////////////////////////////////////////
union color
{
	unsigned ui_color;
	struct {unsigned char a, r, g, b; };
};
//Each byte corresponds to 1 hex color

inline color lerp(const color &s, const color &e, float t)
{
	color out;
	out.r = s.r*(1 - t) + e.r*t;
	out.g = s.g*(1 - t) + e.g*t;
	out.b = s.b*(1 - t) + e.b*t;
	out.a = s.a*(1 - t) + e.a*t;
	return out;
}