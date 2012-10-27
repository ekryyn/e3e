#include "Node.hpp"

#include "Scene.hpp"

e3e::Node::Node(e3e::Scene *scene) :
	scene(scene),
	entity(NULL)
{
}

e3e::Node::Node(e3e::Scene *scene, e3e::Entity *e) :
	scene(scene),
	entity(e)
{

}

void e3e::Node::attachEntity(Entity *e)
{
	entity = e;
}

void e3e::Node::render()
{
	if( entity )
	{
		scene->matrixPush();
		scene->matrixTransform( worldTransformation );
		entity->render();

		std::vector<e3e::Node*>::iterator it;
		for(it = children.begin(); it != children.end(); it++)
		{
			(*it)->rotateXYZ(0.015, 0, 0);
			(*it)->render();
		}

		scene->matrixPop();
	}
}


void e3e::Node::translate(float x, float y, float z)
{
	e3e::Matrix4f t = e3e::Matrix4f::translation(x, y, z);
	worldTransformation *= t;
}

void e3e::Node::rotateXYZ(float x, float y, float z)
{
	e3e::Matrix4f t;
	t = e3e::Matrix4f::rotationX(x);
	worldTransformation *= t;

	t = e3e::Matrix4f::rotationY(y);
	worldTransformation *= t;

	t = e3e::Matrix4f::rotationZ(z);
	worldTransformation *= t;

}
