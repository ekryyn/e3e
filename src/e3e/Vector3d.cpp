#include "Vector3d.hpp"
#include <cmath>

e3e::Vector3d::Vector3d()
{
	x = 0;
	y = 0;
	z = 0;
}

e3e::Vector3d::Vector3d(double x,double y,double z) :
	x(x), y(y), z(z)
{
}

e3e::Vector3d::Vector3d(const e3e::Vector3d & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

e3e::Vector3d::Vector3d(const e3e::Vector3d & from,const e3e::Vector3d & to)
{
	x = to.x - from.x;
	y = to.y - from.y;
	z = to.z - from.z;
}

e3e::Vector3d & e3e::Vector3d::operator= (const e3e::Vector3d & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

e3e::Vector3d & e3e::Vector3d::operator+= (const e3e::Vector3d & v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

e3e::Vector3d e3e::Vector3d::operator+ (const e3e::Vector3d & v) const
{
	Vector3d t = *this;
	t += v;
	return t;
}

e3e::Vector3d & e3e::Vector3d::operator-= (const e3e::Vector3d & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

e3e::Vector3d e3e::Vector3d::operator- (const e3e::Vector3d & v) const
{
	Vector3d t = *this;
	t -= v;
	return t;
}

e3e::Vector3d & e3e::Vector3d::operator*= (const double a)
{
	x *= a;
	y *= a;
	z *= a;
	return *this;
}

e3e::Vector3d e3e::Vector3d::operator* (const double a)const
{
	Vector3d t = *this;
	t *= a;
	return t;
}

e3e::Vector3d operator* (const double a, const e3e::Vector3d & v)
{
	return e3e::Vector3d(v.x*a,v.y*a,v.z*a);
}

e3e::Vector3d & e3e::Vector3d::operator/= (const double a)
{
	x /= a;
	y /= a;
	z /= a;
	return *this;
}

e3e::Vector3d e3e::Vector3d::operator/ (const double a)const
{
	Vector3d t = *this;
	t /= a;
	return t;
}

e3e::Vector3d e3e::Vector3d::crossProduct(const e3e::Vector3d & v)const
{
	e3e::Vector3d t;
	t.x = y*v.z - z*v.y;
	t.y = z*v.x - x*v.z;
	t.z = x*v.y - y*v.x;
	return t;
}

double e3e::Vector3d::length()const
{
	return sqrt( x*x + y*y + z*z);
}

e3e::Vector3d & e3e::Vector3d::normalize()
{
	(*this) /= length();
	return (*this);
}


