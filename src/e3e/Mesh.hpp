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
public:

	typedef enum
	{
		NORMALS = 0,
		GEOMETRY = 1
	} FaceType;

	typedef enum
	{
		POSITION = 0,
		COLOR = 1
	} DataType;

	typedef enum
	{
		CW = 0,
		CCW = 1
	} WiseType;

	Mesh();
	~Mesh();

	void initGeometry();
	void initNormals(WiseType wisetype);
	virtual void render();

	std::vector<Vector3d> vertices;
	std::vector<Color> diffuses;
	std::vector<Face> faces;

	Vector3d faceCenter(Face f);
	Vector3d faceNormal(Face f, WiseType wisetype = CW);
private:
	void transformsQuadsToTris();
	GLuint geometryBuffers[2];
	GLuint facenormalsBuffers[2];
	GLuint vaos[2];
	GLuint indexBuffers[2];
};

}

#endif // MESH_HPP
