#ifndef MESHMANAGER_HPP
#define MESHMANAGER_HPP

#include "Entity.hpp"
#include "Mesh.hpp"
#include "Node.hpp"
#include "Singleton.hpp"


#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>


#include <string>
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

	Node* createNodeFromFile(const std::string &filename);

private:

	Mesh* createMeshFromAssimp(aiMesh *amesh, aiMaterial *amaterial);

	std::vector<Mesh*> meshes;
};

}
#endif // MESHMANAGER_HPP
