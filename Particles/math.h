#pragma once

struct vec2 { float x, y; };

inline vec2 operator+(const vec2 &a, const vec2 &b)
{ return vec2{ a.x + b.x, a.y + b.y }; }

inline vec2 operator*(const vec2 &a, float b)
{ return vec2{ a.x*b, a.y*b }; }
inline vec2 operator*(const vec2 &a, const vec2 &b)
{ return vec2{ a.x*b.x, a.y*b.y }; }

inline vec2 lerp(const vec2 &s, const vec2 &e, float t)
{ return s*(t - 1) + e*t; }

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
	out.r = s.r*(t - 1) + e.r*t;
	out.g = s.g*(t - 1) + e.g*t;
	out.b = s.b*(t - 1) + e.b*t;
	out.a = s.a*(t - 1) + e.a*t;
	return out;
}