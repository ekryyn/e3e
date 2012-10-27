#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Matrix4f.hpp"

namespace e3e
{

class Camera
{
public:
	Camera(double aspect);

	Matrix4f getProjectionMatrix() const;

private:
	double near;
	double far;
	double aspect;
	double frustumScale;

	Matrix4f projectionMatrix;
};

}

#endif // CAMERA_HPP
