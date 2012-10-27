#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>
#include <vector>

#include "Entity.hpp"
#include "Vector3d.hpp"

namespace e3e
{

class Mesh : public Entity
{
public:
	Mesh();

	virtual void render();

private:
	std::vector<Vector3d> vertex;
};

}

#endif // MESH_HPP
