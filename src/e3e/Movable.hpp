#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include "Matrix4f.hpp"

namespace e3e
{

class Movable
{
public:
	virtual void translate(float x, float y, float z);
	virtual void rotateXYZ(float x, float y, float z);

protected:
	Matrix4f worldTransformation;
};


}

#endif // MOVABLE_HPP
