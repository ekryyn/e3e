#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>
#include <map>
#include <vector>

#include "Color.hpp"
#include "Entity.hpp"
#include "Material.hpp"
#include "Shader.hpp"
#include "Vector3d.hpp"
#include "Vector2d.hpp"

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
//		COLOR = 1,
		NORMAL = 1,
		UV = 2
	} DataType;

	typedef enum
	{
		CW = 0,
		CCW = 1
	} WiseType;

	typedef struct
	{
		bool face_normals_ok;
		bool vertex_normals_ok;
		bool draw_face_normals;
		bool draw_vertex_normals;
	} NormalState;

	Mesh();
	~Mesh();
	void initGeometry(bool interpolate_vertex_normals = true);
	void initOpenGL();

	void subdivideQuads();

	void addTexture();

	void computeFaceNormals(WiseType wisetype = CW);
	void computeVertexNormals();

	virtual void render(Shader *shader);

	std::vector<Vector3d> vertices;
	std::vector<Vector3d> vertexNormals;

	std::vector<Face> faces;
	std::vector<Vector3d> faceNormals;

	std::vector<Vector2d> uvCoords;

	std::vector<Color> diffuses;

	Material material;

	Vector3d faceCenter(Face f);
	Vector3d faceNormal(const Face &f, WiseType wisetype = CW);

	NormalState normal_state;


private:
	void triangulate();

	void initOpenGLGeometry();
	void initOpenGLFaceNormals();
	void initOpenGLVertexNormals();

	void applyMaterial(Shader *shader);

	GLuint geometryBuffers[3];
	GLuint facenormalsBuffers[2];
	GLuint vertexnormalsBuffers[2];
	GLuint vaos[3];
	GLuint indexBuffers[2];

	bool ready;
};

}

#endif // MESH_HPP
