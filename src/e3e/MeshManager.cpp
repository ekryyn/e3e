#include "MeshManager.hpp"

#include <cmath>

#include "Color.hpp"
#include "Vector3d.hpp"

e3e::MeshManager::MeshManager()
{
}

e3e::Mesh* e3e::MeshManager::createUVSphere()
{
	e3e::Mesh *sphere = new e3e::Mesh();

	unsigned int nbSlices = 32, nbStacks = 16;
	float radius = 1.f;
	e3e::Color color(.5, .5, .5);

	float tdelta = 360.f/nbSlices;
	float pdelta = 180.f/nbStacks;

	sphere->vertexNormals.clear();
	// positionne les vertices
	for( float phi = -90; phi <= 90; phi += pdelta )
	{
		for( float theta = 0; theta < 360; theta += tdelta)
		{
			e3e::Vector3d v;
			v.x = radius * cos(phi*M_PI/180.f) * cos(theta*M_PI/180.f);
			v.y = radius * sin(phi*M_PI/180.f);
			v.z = radius * cos(phi*M_PI/180.f) * sin(theta*M_PI/180.f);
			sphere->vertices.push_back(v);
			e3e::Vector3d n = v.normalize();
			sphere->vertexNormals.push_back(n);
			sphere->diffuses.push_back(color);
		}
	}

	// création des faces
	for(unsigned int i = 0; i<nbStacks; i++)
	{
		for(unsigned int j = 0; j<nbSlices; j++)
		{
			e3e::Face f;
			unsigned int _j = j+1; if(_j>=nbSlices) _j -= nbSlices;
			f.indices.push_back(i*nbSlices + j);
			f.indices.push_back(i*nbSlices + _j);
			f.indices.push_back((i+1)*nbSlices + _j);
			f.indices.push_back((i+1)*nbSlices + j);
			sphere->faces.push_back(f);
		}
	}

	sphere->drawFaceNormals = false;
	sphere->drawVertexNormals = false;

	sphere->computeNormals(false, Mesh::CW);
	sphere->initGeometry();
	sphere->initOpenGL();

	return sphere;
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
		diffuses.push_back( e3e::Color(.5,1,.5) );
	}

	cube->drawFaceNormals = false;
	cube->drawVertexNormals = false;

	cube->computeNormals(true);
	cube->initGeometry();
	cube->initOpenGL();

	return cube;
}
