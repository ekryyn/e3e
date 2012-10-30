#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>

#include "Matrix4f.hpp"
#include "Vector3d.hpp"

#include "CameraListener.hpp"

namespace e3e
{
class Scene;

class Camera
{
public:
	Camera(double aspect, double fovy);

	Matrix4f getProjectionMatrix() const;

	void zoomIn();

	void tick();

	void addListener(CameraListener *l){ listeners.push_back(l); }

private:
	void computeProjection();
	void signalUpdate();

	double near;
	double far;
	double aspect;
	double fovy;
	double frustumScale;

	Vector3d position;
	Vector3d forward, up;

	Matrix4f projectionMatrix;

	std::vector<CameraListener*> listeners;
};

}

#endif // CAMERA_HPP
