#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

#include "Matrix4f.hpp"
#include "Movable.hpp"
#include "Entity.hpp"

namespace e3e
{

class Scene;

class Node : public Movable
{
public:
	Node(Scene *scene);
	Node(Scene *scene, Entity *e);

	void render();

	void attachEntity(Entity *e);

	void addChildNode(Node *c){ children.push_back(c); }



private:
	Scene *scene;
	Entity *entity;

	std::vector<Node*> children;
};

}

#endif // NODE_HPP
