#include "Movable.hpp"

void e3e::Movable::translate(float x, float y, float z)
{
	e3e::Matrix4f t = e3e::Matrix4f::translation(x, y, z);
	worldTransformation *= t;
}

void e3e::Movable::rotateXYZ(float x, float y, float z)
{
	e3e::Matrix4f t;
	t = e3e::Matrix4f::rotationX(x);
	worldTransformation *= t;

	t = e3e::Matrix4f::rotationY(y);
	worldTransformation *= t;

	t = e3e::Matrix4f::rotationZ(z);
	worldTransformation *= t;

}
