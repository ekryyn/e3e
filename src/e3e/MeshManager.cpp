#include "MeshManager.hpp"

#include "Color.hpp"
#include "Vector3d.hpp"

e3e::MeshManager::MeshManager()
{
}

e3e::Mesh* e3e::MeshManager::createCube(float size)
{
	e3e::Mesh *cube = new e3e::Mesh();

	e3e::Vector3d v1, v2, v3, v4;
	e3e::Vector3d v5, v6, v7, v8;

	float offX = 0, offY = 0, offZ = 0;

	float scale = size/2.f;

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

	std::vector<e3e::Vector3d> &vertices = cube->vertices;
	std::vector<e3e::Face> &faces = cube->faces;
	std::vector<e3e::Color> &diffuses = cube->diffuses;

	vertices.push_back(v1); vertices.push_back(v2); vertices.push_back(v3); vertices.push_back(v4);
	vertices.push_back(v5); vertices.push_back(v6); vertices.push_back(v7); vertices.push_back(v8);


	e3e::Face f;
	f = e3e::Face(); f.indices.push_back(0); f.indices.push_back(1); f.indices.push_back(2); f.indices.push_back(3);
	faces.push_back(f);
	f = e3e::Face(); f.indices.push_back(0); f.indices.push_back(4); f.indices.push_back(5); f.indices.push_back(1);
	faces.push_back(f);
	f = e3e::Face(); f.indices.push_back(0); f.indices.push_back(3); f.indices.push_back(7); f.indices.push_back(4);
	faces.push_back(f);
	f = e3e::Face(); f.indices.push_back(6); f.indices.push_back(5); f.indices.push_back(4); f.indices.push_back(7);
	faces.push_back(f);
	f = e3e::Face(); f.indices.push_back(6); f.indices.push_back(7); f.indices.push_back(3); f.indices.push_back(2);
	faces.push_back(f);
	f = e3e::Face(); f.indices.push_back(6); f.indices.push_back(2); f.indices.push_back(1); f.indices.push_back(5);
	faces.push_back(f);

	for(unsigned int i=0; i<vertices.size(); i++){
		diffuses.push_back( (i%2==0) ? e3e::Color(1,0,0) : e3e::Color(0,0,1) );
	}

	cube->initGeometry();
	cube->initOpenGL();

	return cube;
}
