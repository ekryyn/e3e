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
		scene->matrixReplace( worldTransformation );
		entity->render();
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
