#include "Mesh.hpp"

e3e::Mesh::Mesh()
{

}

void e3e::Mesh::render()
{

	e3e::Vector3d v1, v2, v3, v4;
	e3e::Vector3d v5, v6, v7, v8;

	float offX, offY, offZ = 0;
//	offY = 0;
//	offX = -2;

	float scale = 1;

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

	glBegin(GL_QUADS);

	glColor3ub(255,0,255);
	glVertex4d(v1.x, v1.y, v1.z, 1.f);
	glVertex4d(v2.x, v2.y, v2.z, 1.f);
	glVertex4d(v3.x, v3.y, v3.z, 1.f);
	glVertex4d(v4.x, v4.y, v4.z, 1.f);

	glVertex4d(v1.x, v1.y, v1.z, 1.f);
	glVertex4d(v2.x, v2.y, v2.z, 1.f);
	glVertex4d(v6.x, v6.y, v6.z, 1.f);
	glVertex4d(v5.x, v5.y, v5.z, 1.f);

	glVertex4d(v2.x, v2.y, v2.z, 1.f);
	glVertex4d(v3.x, v3.y, v3.z, 1.f);
	glVertex4d(v7.x, v7.y, v7.z, 1.f);
	glVertex4d(v6.x, v6.y, v6.z, 1.f);

	glVertex4d(v3.x, v3.y, v3.z, 1.f);
	glVertex4d(v4.x, v4.y, v4.z, 1.f);
	glVertex4d(v8.x, v8.y, v8.z, 1.f);
	glVertex4d(v7.x, v7.y, v7.z, 1.f);

	glVertex4d(v4.x, v4.y, v4.z, 1.f);
	glVertex4d(v1.x, v1.y, v1.z, 1.f);
	glVertex4d(v5.x, v5.y, v5.z, 1.f);
	glVertex4d(v8.x, v8.y, v8.z, 1.f);

	glVertex4d(v5.x, v5.y, v5.z, 1.f);
	glVertex4d(v6.x, v6.y, v6.z, 1.f);
	glVertex4d(v7.x, v7.y, v7.z, 1.f);
	glVertex4d(v8.x, v8.y, v8.z, 1.f);

	glEnd();
}
