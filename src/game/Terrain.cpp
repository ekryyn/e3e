#include "Terrain.hpp"

#include "../e3e/Color.hpp"
#include "../e3e/Vector3d.hpp"

Terrain::Terrain()
{
}

void Terrain::initFromMap(const Map &map)
{
	float cellSize = 1;

	unsigned int k = 0;

	for(unsigned int i = 0; i< map.height; i++)
	{
		for(unsigned int j = 0; j < map.width; j++)
		{
			e3e::Vector3d v1, v2, v3, v4;
			v1.z = 0; v2.z = 0; v3.z = 0; v4.z = 0;

			v1.x = j*cellSize; v1.y = i*cellSize;
			v2.x = (j+1)*cellSize; v2.y = i*cellSize;
			v3.x = (j+1)*cellSize; v3.y = (i+1)*cellSize;
			v4.x = j*cellSize; v4.y = (i+1)*cellSize;

			vertices.push_back(v1); vertices.push_back(v4);
			vertices.push_back(v3); vertices.push_back(v2);

			e3e::Vector3d n(0,0,1);
			vertexNormals.push_back(n); vertexNormals.push_back(n);
			vertexNormals.push_back(n); vertexNormals.push_back(n);

			e3e::Face f;
			f.indices.push_back( k++ ); f.indices.push_back( k++ );
			f.indices.push_back( k++ ); f.indices.push_back( k++ );

			faces.push_back(f);

		}
	}

	normal_state.vertex_normals_ok = true;
	subdivideQuads();
	subdivideQuads();
	subdivideQuads();

	material.diffuse = e3e::Color(1,0,0);
	normal_state.draw_vertex_normals = true;

	initGeometry(false);
	initOpenGL();
}
