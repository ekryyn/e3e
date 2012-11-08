#ifndef MESHMANAGER_HPP
#define MESHMANAGER_HPP

#include "Entity.hpp"
#include "Mesh.hpp"
#include "Singleton.hpp"

#include <vector>

namespace e3e
{

class MeshManager : public Singleton<MeshManager>
{
	friend class Singleton<MeshManager>;

public:

	typedef unsigned int MeshId;

	MeshManager();

	Mesh* createCube(float size);

	Mesh* createUVSphere();

	Mesh* createPlane();

private:
	std::vector<Mesh*> meshes;
};

}
#endif // MESHMANAGER_HPP
