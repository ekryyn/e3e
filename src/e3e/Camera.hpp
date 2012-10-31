#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>

#include "CameraListener.hpp"
#include "Matrix4f.hpp"
#include "Vector3d.hpp"

namespace e3e
{

class Camera
{
public:
	Camera(double aspect, double fovy);

	Matrix4f getProjectionMatrix() const;

	void zoomIn();

	virtual Matrix4f lookAt(const Vector3d &position, const Vector3d &targetPoint) const;

private:
	void computeProjection();
	void signalUpdate();

	double near;
	double far;
	double aspect;
	double fovy;
	double frustumScale;


	Matrix4f projectionMatrix;
};

}

#endif // CAMERA_HPP
