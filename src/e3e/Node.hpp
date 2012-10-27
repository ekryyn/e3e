#ifndef NODE_HPP
#define NODE_HPP

#include "Matrix4f.hpp"
#include "Entity.hpp"

namespace e3e
{

class Scene;

class Node
{
public:
	Node(Scene *scene);
	Node(Scene *scene, Entity *e);

	void render();

	void attachEntity(Entity *e);

	void translate(float x, float y, float z);
	void rotateXYZ(float x, float y, float z);

private:
	Matrix4f worldTransformation;
	Scene *scene;
	Entity *entity;
};

}

#endif // NODE_HPP