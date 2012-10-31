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
	unsigned int nbIndices;
	unsigned int *indices;

	Face()
	{
		nbIndices = 0;
		indices = NULL;
	}

	~Face()
	{
		delete [] indices;
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

	unsigned int nbVertices;
	Vector3d *vertices;
	Color *diffuses;

	unsigned int nbQuads;
	Face *quads;

	unsigned int nbTris;
	Face *tris;

private:
	GLuint dataBuffers[2];
	GLuint vaos[2];
	GLuint indexBuffers[2];
};

}

#endif // MESH_HPP
