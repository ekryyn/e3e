#include "Camera.hpp"

e3e::Camera::Camera(double aspect) :
	aspect(aspect),
	frustumScale(1.0f)
{
	far = 100;
	near = .5f;

	projectionMatrix = e3e::Matrix4f(frustumScale/aspect, 0, 0, 0,
												0, frustumScale, 0, 0,
												0, 0, (far+near)/(near-far), (2*far*near)/(near-far),
												0, 0, -1, 0);
}


e3e::Matrix4f e3e::Camera::getProjectionMatrix() const
{
	return projectionMatrix;
	e3e::Matrix4f r;
	r.a1 = .6;
	return r;
}
