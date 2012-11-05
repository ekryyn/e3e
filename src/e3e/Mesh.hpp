#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>
#include <vector>

#include "Entity.hpp"
#include "Vector3d.hpp"
#include "Color.hpp"

namespace e3e
{

struct Face
{
	std::vector<unsigned int> indices;

	Face()
	{
	}

	~Face()
	{
	}

	unsigned int nbIndices()
	{
		return indices.size();
	}


};

class Mesh : public Entity
{
	typedef enum
	{
		QUADS = 0,
		TRIS = 1
	} FaceType;

	typedef enum
	{
		POSITION = 0,
		COLOR = 1
	} DataType;

public:
	Mesh();
	~Mesh();

	void init();
	virtual void render();

	std::vector<Vector3d> vertices;
	std::vector<Color> diffuses;
	std::vector<Face> faces;

private:
	void transformsQuadsToTris();
	GLuint dataBuffers[2];
	GLuint vaos[2];
	GLuint indexBuffers[2];
};

}

#endif // MESH_HPP
