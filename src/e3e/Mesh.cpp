#include "Mesh.hpp"

e3e::Mesh::Mesh()
{
	glGenBuffers(2, dataBuffers);
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

void e3e::Mesh::init()
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

	glBindVertexArray(vaos[TRIS]);
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffers[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffers[COLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[TRIS]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tri_indexes), tri_indexes, GL_STATIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void e3e::Mesh::render()
{

	glBindVertexArray(vaos[TRIS]);
	glDrawElements(GL_TRIANGLES, 3*faces.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

e3e::Mesh::~Mesh()
{
	glDeleteBuffers(2, dataBuffers);
	glDeleteVertexArrays(2, vaos);
	glDeleteBuffers(2, indexBuffers);
}
