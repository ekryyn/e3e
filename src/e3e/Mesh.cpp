#include "Mesh.hpp"

e3e::Mesh::Mesh() :
	nbVertices(0),
	vertices(NULL),
	diffuses(NULL),
	nbQuads(0),
	quads(NULL),
	nbTris(0),
	tris(NULL)
{
	glGenBuffers(2, dataBuffers);
	glGenVertexArrays(2, vaos);
	glGenBuffers(2, indexBuffers);
}

void e3e::Mesh::init()
{
	/*
	 * Initializing data arrays
	 */
	unsigned int k;
	float positions[nbVertices*3];
	float colors[nbVertices*3];
	unsigned int quad_indexes[4*nbQuads];
	unsigned int tri_indexes[3*nbTris];

	k = 0;
	for(unsigned int i=0; i<nbVertices; i++){
		colors[k] = diffuses[i].r;
		positions[k++] = vertices[i].x;
		colors[k] = diffuses[i].g;
		positions[k++] = vertices[i].y;
		colors[k] = diffuses[i].b;
		positions[k++] = vertices[i].z;
	}

	k = 0;
	for(unsigned int i=0; i<nbQuads; i++){
		if(quads[i].nbIndices == 4){
			quad_indexes[k++] = quads[i].indices[0];
			quad_indexes[k++] = quads[i].indices[1];
			quad_indexes[k++] = quads[i].indices[2];
			quad_indexes[k++] = quads[i].indices[3];
		}
	}

	k = 0;
	for(unsigned int i=0; i<nbTris; i++){
		if(tris[i].nbIndices == 3){
			tri_indexes[k++] = tris[i].indices[0];
			tri_indexes[k++] = tris[i].indices[1];
			tri_indexes[k++] = tris[i].indices[2];
		}
	}

	/*
	 * creating VAO states
	 *
	 * (do it twice : one for quads, one for tris)
	 * This seems to be a lot of duplication.
	 * In a perfect world, I'd like to have only one state;
	 * But I do not know how to distinguish the drawing mode (TRIANGLES or QUADS)
	 */
	_initVao(QUADS, positions, sizeof(positions), colors, sizeof(colors), quad_indexes, sizeof(quad_indexes));
	_initVao(TRIS, positions, sizeof(positions), colors, sizeof(colors), tri_indexes, sizeof(tri_indexes));


}

void e3e::Mesh::_initVao(FaceType type, float *positions, size_t posSize, float *colors, size_t colSize, unsigned int *indexes, size_t indSize)
{
	glBindVertexArray(vaos[type]);
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffers[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, posSize, positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffers[COLOR]);
	glBufferData(GL_ARRAY_BUFFER, colSize, colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[type]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize, indexes, GL_STATIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void e3e::Mesh::render()
{
	/*
	 * Time to render twice... Like I said, I can't find a way
	 * to draw different types of primitives without this
	 */

	glBindVertexArray(vaos[QUADS]);
	glDrawElements(GL_QUADS, 4*nbQuads, GL_UNSIGNED_INT, 0);

	glBindVertexArray(vaos[TRIS]);
	glDrawElements(GL_TRIANGLES, 3*nbTris, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

e3e::Mesh::~Mesh()
{
	glDeleteBuffers(2, dataBuffers);
	glDeleteVertexArrays(2, vaos);
	glDeleteBuffers(2, indexBuffers);
}
