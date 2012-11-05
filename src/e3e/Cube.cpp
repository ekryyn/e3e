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


	vertices.push_back(v1); vertices.push_back(v2); vertices.push_back(v3); vertices.push_back(v4);
	vertices.push_back(v5); vertices.push_back(v6); vertices.push_back(v7); vertices.push_back(v8);


	e3e::Face f;

	f = e3e::Face(); f.indices.push_back(0); f.indices.push_back(1); f.indices.push_back(2); f.indices.push_back(3);
	faces.push_back(f);
	f = e3e::Face(); f.indices.push_back(0); f.indices.push_back(1); f.indices.push_back(5); f.indices.push_back(4);
	faces.push_back(f);
	f = e3e::Face(); f.indices.push_back(0); f.indices.push_back(4); f.indices.push_back(7); f.indices.push_back(3);
	faces.push_back(f);
	f = e3e::Face(); f.indices.push_back(6); f.indices.push_back(5); f.indices.push_back(4); f.indices.push_back(7);
	faces.push_back(f);
	f = e3e::Face(); f.indices.push_back(6); f.indices.push_back(7); f.indices.push_back(3); f.indices.push_back(2);
	faces.push_back(f);
	f = e3e::Face(); f.indices.push_back(6); f.indices.push_back(5); f.indices.push_back(1); f.indices.push_back(2);
	faces.push_back(f);


	// testing diffuses
	for(unsigned int i=0; i<vertices.size(); i++){
		diffuses.push_back( (i%2==0) ? e3e::Color(1,0,0) : e3e::Color(0,0,1) );
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
