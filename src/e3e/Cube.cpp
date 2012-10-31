#include "Cube.hpp"

e3e::Cube::Cube()
{
	e3e::Vector3d v1, v2, v3, v4;
	e3e::Vector3d v5, v6, v7, v8, v9;

	float offX = 0, offY = 0, offZ = 0;

	float scale = .5;

	v1.x = -scale + offX;
	v1.y = -scale + offY;
	v1.z = -scale + offZ;

	v2.x = scale + offX;
	v2.y = -scale + offY;
	v2.z = -scale + offZ;

	v3.x = scale + offX;
	v3.y = scale + offY;
	v3.z = -scale + offZ;

	v4.x = -scale + offX;
	v4.y = scale + offY;
	v4.z = -scale + offZ;

	v5.x = -scale + offX;
	v5.y = -scale + offY;
	v5.z = scale + offZ;

	v6.x = scale + offX;
	v6.y = -scale + offY;
	v6.z = scale + offZ;

	v7.x = scale + offX;
	v7.y = scale + offY;
	v7.z = scale + offZ;

	v8.x = -scale + offX;
	v8.y = scale + offY;
	v8.z = scale + offZ;

	v9.x = 0;
	v9.y = 2*scale;
	v9.z = 0;

	unsigned int i, k = 0;

	i = 0;
	vertices = new e3e::Vector3d[9];
	vertices[i++] = v1; vertices[i++] = v2; vertices[i++] = v3; vertices[i++] = v4;
	vertices[i++] = v5; vertices[i++] = v6; vertices[i++] = v7; vertices[i++] = v8;
	vertices[i++] = v9;
	nbVertices = 9;

	i = 0;
	quads = new e3e::Face[6];
	quads[i] = e3e::Face(); quads[i].indices = new unsigned int[4];
	quads[i++].nbIndices = 4;
	quads[i] = e3e::Face(); quads[i].indices = new unsigned int[4];
	quads[i++].nbIndices = 4;
	quads[i] = e3e::Face(); quads[i].indices = new unsigned int[4];
	quads[i++].nbIndices = 4;
	quads[i] = e3e::Face(); quads[i].indices = new unsigned int[4];
	quads[i++].nbIndices = 4;
	quads[i] = e3e::Face(); quads[i].indices = new unsigned int[4];
	quads[i++].nbIndices = 4;
	quads[i] = e3e::Face(); quads[i].indices = new unsigned int[4];
	quads[i++].nbIndices = 4;

	i=0;
	k = 0;
	quads[i].indices[k++] = 0; quads[i].indices[k++] = 1; quads[i].indices[k++] = 2; quads[i++].indices[k++] = 3;
	k = 0;
	quads[i].indices[k++] = 0; quads[i].indices[k++] = 1; quads[i].indices[k++] = 5; quads[i++].indices[k++] = 4;
	k = 0;
	quads[i].indices[k++] = 0; quads[i].indices[k++] = 4; quads[i].indices[k++] = 7; quads[i++].indices[k++] = 3;
	k = 0;
	quads[i].indices[k++] = 6; quads[i].indices[k++] = 5; quads[i].indices[k++] = 4; quads[i++].indices[k++] = 7;
	k = 0;
	quads[i].indices[k++] = 6; quads[i].indices[k++] = 7; quads[i].indices[k++] = 3; quads[i++].indices[k++] = 2;
	k = 0;
	quads[i].indices[k++] = 6; quads[i].indices[k++] = 5; quads[i].indices[k++] = 1; quads[i++].indices[k++] = 2;

	nbQuads = 6;

	// testing tris
	i=0;
	tris = new e3e::Face[4];
	tris[i] = e3e::Face(); tris[i].indices = new unsigned int[3];
	tris[i++].nbIndices = 3;
	tris[i] = e3e::Face(); tris[i].indices = new unsigned int[3];
	tris[i++].nbIndices = 3;
	tris[i] = e3e::Face(); tris[i].indices = new unsigned int[3];
	tris[i++].nbIndices = 3;
	tris[i] = e3e::Face(); tris[i].indices = new unsigned int[3];
	tris[i++].nbIndices = 3;

	i=0;
	k = 0;
	tris[i].indices[k++] = 8; tris[i].indices[k++] = 3; tris[i++].indices[k++] = 2;
	k = 0;
	tris[i].indices[k++] = 8; tris[i].indices[k++] = 3; tris[i++].indices[k++] = 7;
	k = 0;
	tris[i].indices[k++] = 8; tris[i].indices[k++] = 7; tris[i++].indices[k++] = 6;
	k = 0;
	tris[i].indices[k++] = 8; tris[i].indices[k++] = 6; tris[i++].indices[k++] = 2;

	nbTris = 4;

	// testing diffuses
	diffuses = new e3e::Color[nbVertices];
	for(i=0; i<nbVertices; i++){
		diffuses[i] = (i%2==0) ? e3e::Color(1,0,0) : e3e::Color(0,0,1);
		if(i==8) diffuses[i] = e3e::Color(0,1,0);
	}


	init();

}


void e3e::Cube::render()
{
	e3e::Mesh::render();
//	e3e::Vector3d v1, v2, v3, v4;
//	e3e::Vector3d v5, v6, v7, v8;

//	float offX, offY, offZ = 0;
////	offY = 0;
////	offX = -2;

//	float scale = .5;

//	v1.x = -scale + offX;
//	v1.y = -scale + offY;
//	v1.z = -scale + offZ;

//	v2.x = scale + offX;
//	v2.y = -scale + offY;
//	v2.z = -scale + offZ;

//	v3.x = scale + offX;
//	v3.y = scale + offY;
//	v3.z = -scale + offZ;

//	v4.x = -scale + offX;
//	v4.y = scale + offY;
//	v4.z = -scale + offZ;

//	v5.x = -scale + offX;
//	v5.y = -scale + offY;
//	v5.z = scale + offZ;

//	v6.x = scale + offX;
//	v6.y = -scale + offY;
//	v6.z = scale + offZ;

//	v7.x = scale + offX;
//	v7.y = scale + offY;
//	v7.z = scale + offZ;

//	v8.x = -scale + offX;
//	v8.y = scale + offY;
//	v8.z = scale + offZ;

//	glBegin(GL_QUADS);

//	glVertex4d(v1.x, v1.y, v1.z, 1.f);
//	glVertex4d(v2.x, v2.y, v2.z, 1.f);
//	glVertex4d(v3.x, v3.y, v3.z, 1.f);
//	glVertex4d(v4.x, v4.y, v4.z, 1.f);

//	glVertex4d(v1.x, v1.y, v1.z, 1.f);
//	glVertex4d(v2.x, v2.y, v2.z, 1.f);
//	glVertex4d(v6.x, v6.y, v6.z, 1.f);
//	glVertex4d(v5.x, v5.y, v5.z, 1.f);

//	glVertex4d(v2.x, v2.y, v2.z, 1.f);
//	glVertex4d(v3.x, v3.y, v3.z, 1.f);
//	glVertex4d(v7.x, v7.y, v7.z, 1.f);
//	glVertex4d(v6.x, v6.y, v6.z, 1.f);

//	glVertex4d(v3.x, v3.y, v3.z, 1.f);
//	glVertex4d(v4.x, v4.y, v4.z, 1.f);
//	glVertex4d(v8.x, v8.y, v8.z, 1.f);
//	glVertex4d(v7.x, v7.y, v7.z, 1.f);

//	glVertex4d(v4.x, v4.y, v4.z, 1.f);
//	glVertex4d(v1.x, v1.y, v1.z, 1.f);
//	glVertex4d(v5.x, v5.y, v5.z, 1.f);
//	glVertex4d(v8.x, v8.y, v8.z, 1.f);

//	glVertex4d(v5.x, v5.y, v5.z, 1.f);
//	glVertex4d(v6.x, v6.y, v6.z, 1.f);
//	glVertex4d(v7.x, v7.y, v7.z, 1.f);
//	glVertex4d(v8.x, v8.y, v8.z, 1.f);

//	glEnd();
}
