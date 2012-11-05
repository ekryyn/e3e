#include "Mesh.hpp"

e3e::Mesh::Mesh() :
	ready(false)
{
	glGenBuffers(3, geometryBuffers);
	glGenBuffers(2, facenormalsBuffers);
	glGenBuffers(2, vertexnormalsBuffers);
	glGenVertexArrays(3, vaos);
	glGenBuffers(2, indexBuffers);
}

void e3e::Mesh::triangulate()
{
	std::vector<e3e::Face> output;
	std::vector<e3e::Vector3d> outputNormals;
	for(unsigned int fi=0; fi<faces.size(); fi++)
	{
		e3e::Face f = faces[fi];
		e3e::Vector3d nn(faceNormals[fi]);
		if(f.nbIndices() == 3) {
			output.push_back(f);
			outputNormals.push_back(nn);
		} else {
			if(f.nbIndices() == 4) {
				// if quad, creating 2 triangles from it
				e3e::Face t1, t2;
				t1.indices.push_back( f.indices[0] );
				t1.indices.push_back( f.indices[1] );
				t1.indices.push_back( f.indices[2] );
				t2.indices.push_back( f.indices[2] );
				t2.indices.push_back( f.indices[3] );
				t2.indices.push_back( f.indices[0] );

				output.push_back(t1);
				output.push_back(t2);
				outputNormals.push_back(nn);
				outputNormals.push_back(nn);
			}
		}
	}
	faces = output;
	faceNormals = outputNormals;
}

void e3e::Mesh::initGeometry()
{
	// compute normals //
	computeNormals(CW);

	// THEN triangulate.
	// (interpolated vertex normals should respect the initial quads geometry)

	triangulate();

	ready = true;

}

void e3e::Mesh::initOpenGL()
{
	if(ready)
	{
		initOpenGLGeometry();
		initOpenGLFaceNormals();
		initOpenGLVertexNormals();
	}
}

void e3e::Mesh::initOpenGLGeometry()
{
	/*
	 * Initializing data arrays
	 */
	unsigned int k;
	float positions[vertices.size()*3];
	float normals[vertices.size()*3];
	float colors[vertices.size()*3];
	unsigned int tri_indexes[faces.size()*3];

	k = 0;
	for(unsigned int i=0; i<vertices.size(); i++) {
		colors[k] = diffuses[i].r;
		normals[k] = vertexNormals[i].x;
		positions[k++] = vertices[i].x;
		colors[k] = diffuses[i].g;
		normals[k] = vertexNormals[i].y;
		positions[k++] = vertices[i].y;
		colors[k] = diffuses[i].b;
		normals[k] = vertexNormals[i].z;
		positions[k++] = vertices[i].z;

	}

	k = 0;
	for(std::vector<e3e::Face>::iterator itFace = faces.begin();
		 itFace != faces.end();
		 itFace++)
	{
		// Ensure that's a triangle
		if( (*itFace).nbIndices() == 3 ) {
			tri_indexes[k++] = (*itFace).indices[0];
			tri_indexes[k++] = (*itFace).indices[1];
			tri_indexes[k++] = (*itFace).indices[2];
		}
	}

	glBindVertexArray(vaos[GEOMETRY]);

	glBindBuffer(GL_ARRAY_BUFFER, geometryBuffers[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION);
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, geometryBuffers[NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMAL);
	glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, geometryBuffers[COLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(COLOR);
	glVertexAttribPointer(COLOR, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[GEOMETRY]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tri_indexes), tri_indexes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void e3e::Mesh::initOpenGLFaceNormals()
{
	unsigned int k = 0;
	float normalScale = .3f;
	float normalPositions[3*faces.size()*2];
	float normalColors[3*faces.size()*2];
	for(unsigned int i=0; i<faces.size(); i++)
	{
		e3e::Vector3d fn = faceNormals[i];
		e3e::Vector3d b, p;
		b = faceCenter(faces[i]);
		p = b + (fn*normalScale);
		normalColors[k] = 0;
		normalPositions[k++] = b.x;
		normalColors[k] = 1;
		normalPositions[k++] = b.y;
		normalColors[k] = 1;
		normalPositions[k++] = b.z;
		normalColors[k] = 0;
		normalPositions[k++] = p.x;
		normalColors[k] = 1;
		normalPositions[k++] = p.y;
		normalColors[k] = 1;
		normalPositions[k++] = p.z;
	}

	glBindVertexArray(vaos[FACE_NORMALS]);
	glBindBuffer(GL_ARRAY_BUFFER, facenormalsBuffers[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normalPositions), normalPositions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION);
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, facenormalsBuffers[COLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normalColors), normalColors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(COLOR);
	glVertexAttribPointer(COLOR, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void e3e::Mesh::initOpenGLVertexNormals()
{
	unsigned int k = 0;
	float normalScale = .3f;
	float normalPositions[3*vertices.size()*2];
	float normalColors[3*vertices.size()*2];
	for(unsigned int i=0; i<vertices.size(); i++)
	{
		e3e::Vector3d vn = vertexNormals[i];
		e3e::Vector3d b, p;
		b = vertices[i];
		p = b + (vn*normalScale);
		normalColors[k] = .5;
		normalPositions[k++] = b.x;
		normalColors[k] = .5;
		normalPositions[k++] = b.y;
		normalColors[k] = 1;
		normalPositions[k++] = b.z;
		normalColors[k] = .5;
		normalPositions[k++] = p.x;
		normalColors[k] = .5;
		normalPositions[k++] = p.y;
		normalColors[k] = 1;
		normalPositions[k++] = p.z;
	}

	glBindVertexArray(vaos[VERTEX_NORMAL]);

	glBindBuffer(GL_ARRAY_BUFFER, vertexnormalsBuffers[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normalPositions), normalPositions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION);
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexnormalsBuffers[COLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normalColors), normalColors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(COLOR);
	glVertexAttribPointer(COLOR, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void e3e::Mesh::computeNormals(WiseType wisetype)
{
	faceNormals.clear();

	for(unsigned int i=0; i<faces.size(); i++)
	{
		e3e::Vector3d fn(faceNormal(faces[i], wisetype));
		faceNormals.push_back(fn);
	}

	// compute sharing map //
	std::map<unsigned int, std::vector<unsigned int> > sharingMap;
	for(unsigned int vi=0; vi < vertices.size(); vi++)
	{
		// for each vertex, find faces composed by it
		std::vector<unsigned int> list;
		for(unsigned int fi=0; fi < faces.size(); fi++)
		{
			e3e::Face f(faces[fi]);

			for(unsigned int i=0; i<f.nbIndices(); i++)
			{
				if(f.indices[i] == vi)
				{
					list.push_back(fi);
					break;
				}
			}
		}
		sharingMap[vi] = list;
	}

	vertexNormals.clear();
	for(unsigned int vi=0; vi<vertices.size(); vi++)
	{
		e3e::Vector3d vn(0,0,0);
		std::vector<unsigned int> faceList = sharingMap[vi];
		for(unsigned int fi=0; fi<faceList.size(); fi++)
		{
			vn += faceNormals[faceList[fi]];
		}
		vn.normalize();
		vertexNormals.push_back(vn);
	}
}

e3e::Vector3d e3e::Mesh::faceCenter(e3e::Face f)
{
	e3e::Vector3d result(0,0,0);
	for (unsigned int i=0; i<f.nbIndices(); i++)
	{
		result += vertices[f.indices[i]];
	}
	result /= f.nbIndices();
	return result;
}

e3e::Vector3d e3e::Mesh::faceNormal(const e3e::Face &f, WiseType wisetype)
{
	e3e::Vector3d result(0,0,0);

	if(f.nbIndices() >= 3)
	{
		e3e::Vector3d v1, v2;
		v1 = vertices[f.indices[1]] - vertices[f.indices[0]];
		v2 = vertices[f.indices[2]] - vertices[f.indices[0]];
		if(wisetype == CW)
			result = v2.crossProduct(v1);
		else
			result = v1.crossProduct(v2);
		result.normalize();
	}

	return result;
}

void e3e::Mesh::render()
{

	glBindVertexArray(vaos[GEOMETRY]);
	glDrawElements(GL_TRIANGLES, 3*faces.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindVertexArray(vaos[FACE_NORMALS]);
	glDrawArrays(GL_LINES, 0, 2*faces.size());
	glBindVertexArray(0);

	glBindVertexArray(vaos[VERTEX_NORMAL]);
	glDrawArrays(GL_LINES, 0, 2*vertices.size());
	glBindVertexArray(0);
}

e3e::Mesh::~Mesh()
{
	glDeleteBuffers(3, geometryBuffers);
	glDeleteBuffers(2, facenormalsBuffers);
	glDeleteBuffers(2, vertexnormalsBuffers);
	glDeleteVertexArrays(3, vaos);
	glDeleteBuffers(2, indexBuffers);
}
