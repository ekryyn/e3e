#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>
#include <vector>

#include "Entity.hpp"
#include "Vector3d.hpp"

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

public:
	Mesh();
	~Mesh();

	void init();
	virtual void render();

	unsigned int nbVertices;
	Vector3d *vertices;

	unsigned int nbQuads;
	Face *quads;

	unsigned int nbTris;
	Face *tris;

private:
	GLuint bufferData;
	GLuint vaos[2];
	GLuint buffers[2];
};

}

#endif // MESH_HPP
