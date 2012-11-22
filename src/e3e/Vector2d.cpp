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


e3e::Vector2d & e3e::Vector2d::operator= (const e3e::Vector2d & v)
{
	x = v.x;
	y = v.y;
	return *this;
}

e3e::Vector2d & e3e::Vector2d::operator+= (const e3e::Vector2d & v)
{
	x += v.x;
	y += v.y;
	return *this;
}

e3e::Vector2d e3e::Vector2d::operator+ (const e3e::Vector2d & v) const
{
	Vector2d t = *this;
	t += v;
	return t;
}

e3e::Vector2d & e3e::Vector2d::operator-= (const e3e::Vector2d & v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

e3e::Vector2d e3e::Vector2d::operator- (const e3e::Vector2d & v) const
{
	Vector2d t = *this;
	t -= v;
	return t;
}

e3e::Vector2d & e3e::Vector2d::operator*= (const double a)
{
	x *= a;
	y *= a;
	return *this;
}

e3e::Vector2d e3e::Vector2d::operator* (const double a)const
{
	Vector2d t = *this;
	t *= a;
	return t;
}

e3e::Vector2d operator* (const double a, const e3e::Vector2d & v)
{
	return e3e::Vector2d(v.x*a,v.y*a);
}

e3e::Vector2d & e3e::Vector2d::operator/= (const double a)
{
	x /= a;
	y /= a;
	return *this;
}

e3e::Vector2d e3e::Vector2d::operator/ (const double a)const
{
	Vector2d t = *this;
	t /= a;
	return t;
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
