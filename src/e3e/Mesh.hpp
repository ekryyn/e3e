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
		//	_initVao(TRIS, positions, colors, tri_indexes);
		//	e3e::Mesh::FaceType type = QUADS;
		//	unsigned int *indexes = quad_indexes;

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
	void _initVao(FaceType type,
					  float *positions,
					  size_t posSize,
					  float *colors,
					  size_t colSize,
					  unsigned int *indexes,
					  size_t indSize);
	GLuint dataBuffers[2];
	GLuint vaos[2];
	GLuint indexBuffers[2];
};

}

#endif // MESH_HPP
