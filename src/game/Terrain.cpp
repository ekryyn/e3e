#include "Terrain.hpp"

#include "../e3e/Color.hpp"
#include "../e3e/Vector2d.hpp"
#include "../e3e/Vector3d.hpp"

Terrain::Terrain()
{
}

void Terrain::initFromMap(const Map &map)
{
	float cellSize = 1;

	unsigned int k = 0;

	unsigned int tw = 50 * map.width, th = 50 * map.height;

	SDL_Surface *texture_surface, *yellow_surface, *green_surface;
	SDL_Surface *current_surface;

	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	texture_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, tw, th, 32, rmask, gmask, bmask, amask);

	yellow_surface = IMG_Load("res/yellow.png");
	green_surface = IMG_Load("res/green.png");

	SDL_Rect cellImgPosition;

	for(unsigned int i = 0; i< map.height; i++)
	{
		for(unsigned int j = 0; j < map.width; j++)
		{
			e3e::Vector3d v1, v2, v3, v4;
			e3e::Vector2d uv1, uv2, uv3, uv4;

			v1.z = 0; v2.z = 0; v3.z = 0; v4.z = 0;

			v1.x = j*cellSize; v1.y = i*cellSize*-1;
			v2.x = (j+1)*cellSize; v2.y = i*cellSize*-1;
			v3.x = (j+1)*cellSize; v3.y = (i+1)*cellSize*-1;
			v4.x = j*cellSize; v4.y = (i+1)*cellSize*-1;

			uv1.x = (float)j/map.width; uv1.y = 1.f - (float)(i+1)/map.height;
			uv2.x = (float)(j+1)/map.width; uv2.y = 1.f - (float)(i+1)/map.height;
			uv3.x = (float)(j+1)/map.width; uv3.y = 1.f - (float)(i)/map.height;
			uv4.x = (float)j/map.width; uv4.y = 1.f - (float)(i)/map.height;


			vertices.push_back(v1); vertices.push_back(v2);
			vertices.push_back(v3); vertices.push_back(v4);

			uvCoords.push_back(uv1); uvCoords.push_back(uv2);
			uvCoords.push_back(uv3); uvCoords.push_back(uv4);

			e3e::Vector3d n(0,0,1);
			vertexNormals.push_back(n); vertexNormals.push_back(n);
			vertexNormals.push_back(n); vertexNormals.push_back(n);

			e3e::Face f;
			f.indices.push_back( k++ ); f.indices.push_back( k++ );
			f.indices.push_back( k++ ); f.indices.push_back( k++ );

			faces.push_back(f);




			// texture blit
			cellImgPosition.y = i*50;
			cellImgPosition.x = j*50;

			current_surface = map.getCell(i,j).type == Map::GROUND ? green_surface : yellow_surface;
			SDL_BlitSurface(current_surface, NULL, texture_surface, &cellImgPosition);
		}
	}

	// test export
	SDL_SaveBMP(texture_surface, "EXPORT.bmp");

	material.texture.loadTexture(texture_surface);

	SDL_FreeSurface(texture_surface);
	SDL_FreeSurface(yellow_surface);
	SDL_FreeSurface(green_surface);

	normal_state.vertex_normals_ok = true;
	//subdivideQuads();


	material.diffuse = e3e::Color(1,0,0);
	normal_state.draw_vertex_normals = true;
	normal_state.draw_face_normals = true;

	initGeometry(false);
	initOpenGL();
}
