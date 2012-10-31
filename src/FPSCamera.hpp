#ifndef FPSCAMERA_HPP
#define FPSCAMERA_HPP

#include <SFML/Graphics.hpp>

#include "e3e/Camera.hpp"
#include "e3e/Vector3d.hpp"

#include "EventListener.hpp"

class FPSCamera : public e3e::Camera, public EventListener
{
public:
	FPSCamera(double aspect, double fovy);
	e3e::Matrix4f lookAt(const e3e::Vector3d &, const e3e::Vector3d &) const;

	void move();

	void onEvent(const sf::Event &event);

private:
	void updateVectors();
	e3e::Vector3d position, forward;
	float phi, theta;

	sf::Vector2f lastMousePos;

};


#endif // FPSCAMERA_HPP
