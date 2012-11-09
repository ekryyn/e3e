#include "MeshManager.hpp"

#include <cmath>
#include <iostream>

#include "Color.hpp"
#include "Vector2d.hpp"
#include "Vector3d.hpp"

e3e::MeshManager::MeshManager()
{
}

e3e::Mesh* e3e::MeshManager::createUVSphere()
{
	e3e::Mesh *sphere = new e3e::Mesh();

	unsigned int nbSlices = 64, nbStacks = 32;
	float radius = 1.f;
	e3e::Color color(.8, 0, 0);

	float tdelta = 360.f/nbSlices;
	float pdelta = 180.f/nbStacks;

	sphere->vertexNormals.clear();
	// positionne les vertices
	for( float phi = -90; phi <= 90; phi += pdelta )
	{
		for( float theta = 0; theta <= 360; theta += tdelta)
		{
			e3e::Vector3d v;
			v.x = radius * cos(phi*M_PI/180.f) * cos(theta*M_PI/180.f);
			v.y = radius * cos(phi*M_PI/180.f) * sin(theta*M_PI/180.f);
			v.z = radius * sin(phi*M_PI/180.f);
			sphere->vertices.push_back(v);
			e3e::Vector3d n = v.normalize();
			sphere->vertexNormals.push_back(n);

			sphere->diffuses.push_back(color);

			//			std::cout << "UV  " << theta/360.f << " : " << (phi+90.f)/180.f << std::endl;
			e3e::Vector2d uvc( theta/360.f , (phi+90.f)/180.f );
			sphere->uvCoords.push_back( uvc );
		}
	}

	// création des faces
	for(unsigned int i = 0; i<nbStacks; i++)
	{
		for(unsigned int j = 0; j<=nbSlices; j++)
		{
			e3e::Face f;
			unsigned int _j = j+1; if(_j>nbSlices) _j -= nbSlices;
			f.indices.push_back(i*(nbSlices+1) + j);
			f.indices.push_back(i*(nbSlices+1) + _j);
			f.indices.push_back((i+1)*(nbSlices+1) + _j);
			f.indices.push_back((i+1)*(nbSlices+1) + j);
			sphere->faces.push_back(f);
		}
	}

	//	sphere->testTexture = SGLUtils::loadTexture("tex/earth.jpg");
	sphere->texture.loadTexture("tex/earth.jpg");

	sphere->normal_state.vertex_normals_ok = true;
	//	sphere->normal_state.draw_vertex_normals = true;
	sphere->initGeometry(false);
	sphere->initOpenGL();

	return sphere;
}

e3e::Node* e3e::MeshManager::createNodeFromFile(const std::string &filename)
{
	Assimp::Importer aimporter;
	const aiScene *ascene = aimporter.ReadFile(filename,
															 aiProcess_CalcTangentSpace       |
															 aiProcess_JoinIdenticalVertices  |
															 aiProcess_SortByPType);
	e3e::Node *rootNode = new e3e::Node();

	// create nodes
	aiNode *aroot = ascene->mRootNode;
	for (unsigned int n = 0; n<aroot->mNumChildren; n++)
	{
		aiNode *anode = aroot->mChildren[n];
//		aiMatrix4x4 nTrans = aroot->mTransformation;
		for(unsigned m=0; m<anode->mNumMeshes; m++)
		{
			e3e::Node *_node = new e3e::Node();

			// retrieve mesh information
			unsigned int mind = anode->mMeshes[m];
			aiMesh *amesh = ascene->mMeshes[mind];

			_node->attachEntity( createMeshFromAssimp(amesh) );
			rootNode->addChildNode(_node);
		}
	}

	return rootNode;
}

e3e::Mesh* e3e::MeshManager::createMeshFromAssimp(aiMesh *amesh)
{
	e3e::Mesh *mesh = new e3e::Mesh();

	unsigned int nbFaces = amesh->mNumFaces;
	unsigned int nbVertices = amesh->mNumVertices;

	e3e::Color testDiffuse(.8, 0, 0);

	for(unsigned int vi = 0; vi<nbVertices; vi++)
	{
		aiVector3D av = amesh->mVertices[vi];
		aiVector3D an = amesh->mNormals[vi];

		mesh->vertices.push_back( e3e::Vector3d(av.x, av.y, av.z) );
		mesh->vertexNormals.push_back( e3e::Vector3d(an.x, an.y, an.z) );
		mesh->diffuses.push_back(testDiffuse);
	}

	for(unsigned int fi = 0; fi<nbFaces; fi++)
	{
		aiFace af = amesh->mFaces[fi];
		e3e::Face f;
		for(unsigned int j=0; j<af.mNumIndices; j++)
		{
			f.indices.push_back(af.mIndices[j]);
		}
		mesh->faces.push_back(f);
	}

	mesh->normal_state.vertex_normals_ok = true;
	mesh->normal_state.draw_vertex_normals = true;
	mesh->initGeometry(false);
	mesh->initOpenGL();

	return mesh;
}

e3e::Mesh* e3e::MeshManager::createPlane()
{
	e3e::Mesh *plane = new Mesh();

	plane->vertices.push_back( e3e::Vector3d(-1, 1, 0) );
	plane->vertices.push_back( e3e::Vector3d(1, 1, 0) );
	plane->vertices.push_back( e3e::Vector3d(1, -1, 0) );
	plane->vertices.push_back( e3e::Vector3d(-1, -1, 0) );

	plane->uvCoords.push_back( e3e::Vector2d(0,1) );
	plane->uvCoords.push_back( e3e::Vector2d(1,1) );
	plane->uvCoords.push_back( e3e::Vector2d(1,0) );
	plane->uvCoords.push_back( e3e::Vector2d(0,0) );

	plane->diffuses.push_back( e3e::Color(1,0,0) );
	plane->diffuses.push_back( e3e::Color(1,0,0) );
	plane->diffuses.push_back( e3e::Color(1,0,0) );
	plane->diffuses.push_back( e3e::Color(1,0,0) );

	e3e::Face f;
	f.indices.push_back(0); f.indices.push_back(1); f.indices.push_back(2); f.indices.push_back(3);
	plane->faces.push_back(f);

	//	plane->testTexture = SGLUtils::loadTexture("tex/earth.jpg");
	plane->texture.loadTexture("tex/test.jpg");

	plane->normal_state.draw_vertex_normals = true;
	plane->initGeometry();
	plane->initOpenGL();

	return plane;
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

	cube->initGeometry();
	cube->initOpenGL();

	return cube;
}
