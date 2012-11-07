#include "Application.hpp"
#include "FPSCamera.hpp"

#include <cmath>

#include "KeyRegister.hpp"


FPSCamera::FPSCamera(double aspect, double fovy) :
	e3e::Camera(aspect, fovy),
	position(0,-4,0),
	phi(0),
	theta(0)
{
	updateVectors();
}


e3e::Matrix4f FPSCamera::lookAt(const e3e::Vector3d &, const e3e::Vector3d &) const
{
	e3e::Vector3d target = this->position + forward;
	return e3e::Camera::lookAt(this->position, target);
}

void FPSCamera::updateVectors()
{
	// on limite la plage de phi
	if (phi > 89)
		phi = 89;
	else if (phi < -89)
		phi = -89;

	// calcul du vecteur forward (basé sur phi et theta)
	double r_temp = cos(phi*M_PI/180);
	forward.y = r_temp*cos(theta*M_PI/180);
	forward.x = r_temp*sin(theta*M_PI/180);
	forward.z = sin(phi*M_PI/180);
	forward.normalize();

}

void FPSCamera::onEvent(const sf::Event &event)
{
	if( Application::getInstance()->grabbedMouse && event.Type == sf::Event::MouseMoved )
	{
		float ft = Application::getInstance()->frameTime() * 10;

		theta -= (lastMousePos.x-event.MouseMove.X)* ft;
		phi += (lastMousePos.y-event.MouseMove.Y)* ft;

		lastMousePos.x = event.MouseMove.X;
		lastMousePos.y = event.MouseMove.Y;
		updateVectors();

		// replace mouse to the center of the screen
		Application::getInstance()->resetMouse();
		lastMousePos.x = Application::getInstance()->getWidth()/2;
		lastMousePos.y = Application::getInstance()->getHeight()/2;

	}

}

void FPSCamera::move()
{
	float step = .2f;
	KeyRegister *kr = KeyRegister::getInstance();

	e3e::Vector3d up(0,0,1);
	e3e::Vector3d left = up.crossProduct(forward);

	if(kr->isKeyActive(KeyRegister::SLEFT)){
		position += left*step;
	}
	if(kr->isKeyActive(KeyRegister::SRIGHT)){
		position -= left*step;
	}

	if(kr->isKeyActive(KeyRegister::FORWARD)){
		position += forward*step;
	}
	if(kr->isKeyActive(KeyRegister::BACKWARD)){
		position -= forward*step;
	}

	if(kr->isKeyActive(KeyRegister::JUMP)){
		position	+= up*step;
	}
	if(kr->isKeyActive(KeyRegister::SNEAK)){
		position -= up*step;
	}
}
