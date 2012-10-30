#ifndef SCENE_HPP
#define SCENE_HPP

#include <GL/glew.h>
#include <vector>

#include "Camera.hpp"
#include "CameraListener.hpp"
#include "Matrix4f.hpp"
#include "Matrix4fStack.hpp"
#include "Node.hpp"
#include "Shader.hpp"

namespace e3e
{

class Scene : public CameraListener
{
public:
	Scene(int w, int h);

	void drawAxis(float scale);
	void render();

	inline void matrixPush() { sceneMatrixStack.push(); applyMatrix(); }
	inline void matrixPop() { sceneMatrixStack.pop(); applyMatrix(); }

	inline void matrixTranslate(float x, float y, float z) {
		sceneMatrixStack.translate(x,y,z); applyMatrix();
	}

	inline void matrixReplace(const Matrix4f &other){
		sceneMatrixStack.replace(other); applyMatrix();
	}

	inline void matrixTransform(const Matrix4f &t){
		sceneMatrixStack.transform(t); applyMatrix();
	}

	void applyMatrix();

	void reloadProjectionMatrix();

	void cameraUpdated();

private:

	Camera *camera;
	Shader projectionShader;

	std::vector<Node*> sceneNodes;

	int w, h;

	Matrix4fStack sceneMatrixStack;

};

}
#endif // SCENE_HPP
