#include "Vector2d.hpp"
#include <cmath>

e3e::Vector2d::Vector2d()
	: x(0), y(0)
{
}

e3e::Vector2d::Vector2d(double x, double y)
	: x(x), y(y)
{

}

e3e::Vector2d::Vector2d(const e3e::Vector2d &v)
	: x(v.x), y(v.y)
{

}

e3e::Vector2d operator+(const e3e::Vector2d &u, const e3e::Vector2d &v)
{
	e3e::Vector2d r(u);
	r.x += v.x;
	r.y += v.y;
	return r;
}

e3e::Vector2d operator-(const e3e::Vector2d &u, const e3e::Vector2d &v)
{
	e3e::Vector2d r(u);
	r.x -= v.x;
	r.y -= v.y;
	return r;
}

double e3e::Vector2d::length() const
{
	return sqrt( (x*x) + (y*y) );
}

void e3e::Vector2d::normalize()
{
	double n = length();
	x /= n;
	y /= n;
}
