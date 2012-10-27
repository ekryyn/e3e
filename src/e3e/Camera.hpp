#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Matrix4f.hpp"

namespace e3e
{

class Camera
{
public:
	Camera(double aspect, double fovy);

	Matrix4f getProjectionMatrix() const;

	void zoomIn();

private:
	void computeProjection();

	double near;
	double far;
	double aspect;
	double fovy;
	double frustumScale;

	Matrix4f projectionMatrix;
};

}

#endif // CAMERA_HPP
