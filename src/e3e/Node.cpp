#include "Node.hpp"

#include "Scene.hpp"

e3e::Node::Node() :
	entity(NULL)
{
}

e3e::Node::Node(e3e::Entity *e) :
	entity(e)
{

}

void e3e::Node::attachEntity(e3e::Entity *e)
{
	entity = e;
}

void e3e::Node::render(e3e::Scene *scene, Shader *shader)
{
	scene->matrixPush();
	scene->matrixTransform( worldTransformation );

	if( entity )
	{
		entity->render(shader);
	}

	std::vector<e3e::Node*>::iterator it;
	for(it = children.begin(); it != children.end(); it++)
	{
//		(*it)->rotateXYZ(0.015, 0, 0);
		(*it)->render(scene, shader);
	}

	scene->matrixPop();
}
