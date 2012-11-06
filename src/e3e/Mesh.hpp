#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>
#include <map>
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

	unsigned int nbIndices() const
	{
		return indices.size();
	}


};

class Mesh : public Entity
{
public:

	typedef enum
	{
		GEOMETRY = 0,
		FACE_NORMALS = 1,
		VERTEX_NORMAL = 2
	} VaoType;

	typedef enum
	{
		POSITION = 0,
		COLOR = 1,
		NORMAL = 2
	} DataType;

	typedef enum
	{
		CW = 0,
		CCW = 1
	} WiseType;

	Mesh();
	~Mesh();
	void initGeometry();
	void initOpenGL();
	void computeNormals(bool vertex_normals, WiseType wisetype = CW);

	virtual void render();

	std::vector<Vector3d> vertices;
	std::vector<Vector3d> vertexNormals;

	std::vector<Face> faces;
	std::vector<Vector3d> faceNormals;

	std::vector<Color> diffuses;

	Vector3d faceCenter(Face f);
	Vector3d faceNormal(const Face &f, WiseType wisetype = CW);

	bool drawFaceNormals, drawVertexNormals;

private:
	void triangulate();

	void initOpenGLGeometry();
	void initOpenGLFaceNormals();
	void initOpenGLVertexNormals();

	GLuint geometryBuffers[3];
	GLuint facenormalsBuffers[2];
	GLuint vertexnormalsBuffers[2];
	GLuint vaos[3];
	GLuint indexBuffers[2];

	bool ready;
};

}

#endif // MESH_HPP
