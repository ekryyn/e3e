#include "Camera.hpp"
#include <cmath>


e3e::Camera::Camera(double aspect, double fovy) :
	aspect(aspect),
	fovy(fovy),
	frustumScale(1.0f)
{
	far = 100;
	near = .5f;

	computeProjection();
}

void e3e::Camera::computeProjection()
{
	double fovy_rad = fovy * M_PI / 180;
	double t = tan( fovy_rad/2.f );
	double r = t * aspect;
	projectionMatrix = e3e::Matrix4f(near/r, 0, 0, 0,
												0, near/t, 0, 0,
												0, 0, (far+near)/(near-far), (2*far*near)/(near-far),
												0, 0, -1, 0);
}

void e3e::Camera::zoomIn()
{
	fovy -= 5;
	computeProjection();
}

e3e::Matrix4f e3e::Camera::getProjectionMatrix() const
{
	return projectionMatrix;
	e3e::Matrix4f r;
	r.a1 = .6;
	return r;
}
