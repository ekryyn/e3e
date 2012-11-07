#include "Camera.hpp"
#include <cmath>


#include <iostream>

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
}

e3e::Matrix4f e3e::Camera::lookAt(const e3e::Vector3d &position, const e3e::Vector3d &targetPoint) const
{
	e3e::Vector3d forward, up, left;
	e3e::Matrix4f mat;

	forward = targetPoint - position;

	up = e3e::Vector3d(0,0,1); // up test

	forward.normalize();
	left = forward.crossProduct(up);
	left.normalize();

	up = left.crossProduct(forward);

	mat.a1 = left.x;
	mat.a2 = left.y;
	mat.a3 = left.z;

	mat.b1 = up.x;
	mat.b2 = up.y;
	mat.b3 = up.z;

	mat.c1 = -forward.x;
	mat.c2 = -forward.y;
	mat.c3 = -forward.z;

	e3e::Matrix4f translation = e3e::Matrix4f::translation(-position.x, -position.y, -position.z);

	return mat * translation;
}


//void e3e::Camera::tick()
//{
//	KeyRegister *kr = KeyRegister::getInstance();

//	if(kr->isKeyActive(KeyRegister::SLEFT)){
//		position.x -= 0.02;
//	}
//	if(kr->isKeyActive(KeyRegister::SRIGHT)){
//		position.x += 0.02;
//	}

//	if(kr->isKeyActive(KeyRegister::FORWARD)){
//		position.z -= .2;
//	}
//	if(kr->isKeyActive(KeyRegister::BACKWARD)){
//		position.z += .2;
//	}

//	if(kr->isKeyActive(KeyRegister::JUMP)){
//		position.y += .2;
//	}
//	if(kr->isKeyActive(KeyRegister::SNEAK)){
//		position.y -= .2;
//	}
//}
