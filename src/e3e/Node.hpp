#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

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

	void addChildNode(Node *c){ children.push_back(c); }

	void translate(float x, float y, float z);
	void rotateXYZ(float x, float y, float z);

private:
	Matrix4f worldTransformation;
	Scene *scene;
	Entity *entity;

	std::vector<Node*> children;
};

}

#endif // NODE_HPP
