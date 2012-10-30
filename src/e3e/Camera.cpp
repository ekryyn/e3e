#include "Camera.hpp"
#include <cmath>

#include "KeyRegister.hpp"

#include <iostream>

e3e::Camera::Camera(double aspect, double fovy) :
	aspect(aspect),
	fovy(fovy),
	frustumScale(1.0f)
{
	far = 100;
	near = .5f;

	position.x = -6;

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
{	e3e::Matrix4f translation = e3e::Matrix4f::translation(-position.x, -position.y, -position.z);
	e3e::Matrix4f temp(projectionMatrix);
	temp *= translation;
	return temp;
}

void e3e::Camera::signalUpdate()
{
	std::vector<CameraListener*>::iterator it;
	for(it = listeners.begin(); it != listeners.end(); it++)
	{
		(*it)->cameraUpdated();
	}
}

void e3e::Camera::tick()
{
	KeyRegister *kr = KeyRegister::getInstance();

	bool happen = false;

	if(kr->isKeyActive(KeyRegister::SLEFT)){
		position.x -= .2;
		happen = true;
	}
	if(kr->isKeyActive(KeyRegister::SRIGHT)){
		position.x += .2;
		happen = true;
	}

	if(kr->isKeyActive(KeyRegister::FORWARD)){
		position.z -= .2;
		happen = true;
	}
	if(kr->isKeyActive(KeyRegister::BACKWARD)){
		position.z += .2;
		happen = true;
	}

	if(happen){
		signalUpdate();
	}
}
