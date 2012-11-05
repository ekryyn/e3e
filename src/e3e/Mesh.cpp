#include "Mesh.hpp"

e3e::Mesh::Mesh()
{
	glGenBuffers(2, geometryBuffers);
	glGenBuffers(2, facenormalsBuffers);
	glGenVertexArrays(2, vaos);
	glGenBuffers(2, indexBuffers);
}

void e3e::Mesh::transformsQuadsToTris()
{
	std::vector<e3e::Face> output;
	for(std::vector<e3e::Face>::iterator itFace = faces.begin();
		 itFace != faces.end();
		 itFace++)
	{
		e3e::Face f = *itFace;
		if(f.nbIndices() == 3) {
			output.push_back(f);
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
			}
		}
	}
	faces = output;
}

void e3e::Mesh::initGeometry()
{
	// first, make sure there's no quad
	transformsQuadsToTris();

	/*
	 * Initializing data arrays
	 */
	unsigned int k;
	float positions[vertices.size()*3];
	float colors[vertices.size()*3];
	unsigned int tri_indexes[faces.size()*3];

	k = 0;
	for(unsigned int i=0; i<vertices.size(); i++) {
		colors[k] = diffuses[i].r;
		positions[k++] = vertices[i].x;
		colors[k] = diffuses[i].g;
		positions[k++] = vertices[i].y;
		colors[k] = diffuses[i].b;
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
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, geometryBuffers[COLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(COLOR, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[GEOMETRY]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tri_indexes), tri_indexes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void e3e::Mesh::initNormals(WiseType wisetype)
{
	unsigned int k = 0;
	float normalScale = .3f;
	float normalPositions[3*faces.size()*2];
	float normalColors[3*faces.size()*2];
	for(unsigned int i=0; i<faces.size(); i++)
	{
		e3e::Vector3d b, p;
		b = faceCenter(faces[i]);
		p = b+(faceNormal(faces[i], wisetype)*normalScale);
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

	glBindVertexArray(vaos[NORMALS]);
	glBindBuffer(GL_ARRAY_BUFFER, facenormalsBuffers[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normalPositions), normalPositions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, facenormalsBuffers[COLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normalColors), normalColors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(COLOR, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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

e3e::Vector3d e3e::Mesh::faceNormal(e3e::Face f, WiseType wisetype)
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

	glBindVertexArray(vaos[NORMALS]);
	glDrawArrays(GL_LINES, 0, 2*faces.size());
	glBindVertexArray(0);
}

e3e::Mesh::~Mesh()
{
	glDeleteBuffers(2, geometryBuffers);
	glDeleteBuffers(2, facenormalsBuffers);
	glDeleteVertexArrays(2, vaos);
	glDeleteBuffers(2, indexBuffers);
}
