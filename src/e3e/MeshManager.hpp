#ifndef MESHMANAGER_HPP
#define MESHMANAGER_HPP

#include "Mesh.hpp"

namespace e3e
{

class MeshManager
{
public:
	MeshManager();

	static Mesh* createCube(float size);
};

}
#endif // MESHMANAGER_HPP
