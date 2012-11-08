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

void e3e::Node::render(Shader *shader)
{
	if( entity )
	{
		scene->matrixPush();
		scene->matrixTransform( worldTransformation );

		entity->render(shader);

		std::vector<e3e::Node*>::iterator it;
		for(it = children.begin(); it != children.end(); it++)
		{
			(*it)->rotateXYZ(0.015, 0, 0);
			(*it)->render(shader);
		}

		scene->matrixPop();
	}
}
