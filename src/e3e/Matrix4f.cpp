#include "Matrix4f.hpp"

#include <cmath>

e3e::Matrix4f::Matrix4f() :
	a1(1), a2(0), a3(0), a4(0),
	b1(0), b2(1), b3(0), b4(0),
	c1(0), c2(0), c3(1), c4(0),
	d1(0), d2(0), d3(0), d4(1)
{
}

e3e::Matrix4f::Matrix4f(float a1, float a2, float a3, float a4,
								float b1, float b2, float b3, float b4,
								float c1, float c2, float c3, float c4,
								float d1, float d2, float d3, float d4) :
	a1(a1), a2(a2), a3(a3), a4(a4),
	b1(b1), b2(b2), b3(b3), b4(b4),
	c1(c1), c2(c2), c3(c3), c4(c4),
	d1(d1), d2(d2), d3(d3), d4(d4)
{

}

e3e::Matrix4f& e3e::Matrix4f::operator *= (const e3e::Matrix4f& m)
{
	*this = e3e::Matrix4f(
				m.a1 * a1 + m.b1 * a2 + m.c1 * a3 + m.d1 * a4,
				m.a2 * a1 + m.b2 * a2 + m.c2 * a3 + m.d2 * a4,
				m.a3 * a1 + m.b3 * a2 + m.c3 * a3 + m.d3 * a4,
				m.a4 * a1 + m.b4 * a2 + m.c4 * a3 + m.d4 * a4,
				m.a1 * b1 + m.b1 * b2 + m.c1 * b3 + m.d1 * b4,
				m.a2 * b1 + m.b2 * b2 + m.c2 * b3 + m.d2 * b4,
				m.a3 * b1 + m.b3 * b2 + m.c3 * b3 + m.d3 * b4,
				m.a4 * b1 + m.b4 * b2 + m.c4 * b3 + m.d4 * b4,
				m.a1 * c1 + m.b1 * c2 + m.c1 * c3 + m.d1 * c4,
				m.a2 * c1 + m.b2 * c2 + m.c2 * c3 + m.d2 * c4,
				m.a3 * c1 + m.b3 * c2 + m.c3 * c3 + m.d3 * c4,
				m.a4 * c1 + m.b4 * c2 + m.c4 * c3 + m.d4 * c4,
				m.a1 * d1 + m.b1 * d2 + m.c1 * d3 + m.d1 * d4,
				m.a2 * d1 + m.b2 * d2 + m.c2 * d3 + m.d2 * d4,
				m.a3 * d1 + m.b3 * d2 + m.c3 * d3 + m.d3 * d4,
				m.a4 * d1 + m.b4 * d2 + m.c4 * d3 + m.d4 * d4);
	return *this;
}

e3e::Matrix4f e3e::Matrix4f::operator* (const e3e::Matrix4f& m) const
{
	e3e::Matrix4f temp( *this );
	temp *= m;
	return temp;
}

e3e::Matrix4f e3e::Matrix4f::translation(float x, float y, float z)
{
	e3e::Matrix4f result;
	result.a4 = x;
	result.b4 = y;
	result.c4 = z;
	return result;
}

e3e::Matrix4f e3e::Matrix4f::rotationX(float r)
{
	e3e::Matrix4f result;
	result.b2 = cos(r);
	result.b3 = -sin(r);
	result.c2 = sin(r);
	result.c3 = cos(r);
	return result;
}

e3e::Matrix4f e3e::Matrix4f::rotationY(float r)
{
	e3e::Matrix4f result;
	result.a1 = cos(r);
	result.c1 = -sin(r);
	result.a3 = sin(r);
	result.c3 = cos(r);
	return result;
}

e3e::Matrix4f e3e::Matrix4f::rotationZ(float r)
{
	e3e::Matrix4f result;
	result.a1 = cos(r);
	result.a2 = -sin(r);
	result.b1 = sin(r);
	result.b2 = cos(r);
	return result;
}

/*
ROW-MAJOR indexes

0  1  2  3
4  5  6  7
8  9  10 11
12 13 14 15

COLUMN-MAJOR indexes

0  4  8  12
1  5  9  13
2  6  10 14
3  7  11	15

*/

float* e3e::Matrix4f::createColumnMajorArray() const
{
	float *result = new float[16];
	result[0] = a1;
	result[1] = b1;
	result[2] = c1;
	result[3] = d1;
	result[4] = a2;
	result[5] = b2;
	result[6] = c2;
	result[7] = d2;
	result[8] = a3;
	result[9] = b3;
	result[10] = c3;
	result[11] = d3;
	result[12] = a4;
	result[13] = b4;
	result[14] = c4;
	result[15] = d4;
	return result;
}
