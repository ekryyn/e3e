#include "Terrain.hpp"

#include "../e3e/Color.hpp"
#include "../e3e/Vector2d.hpp"
#include "../e3e/Vector3d.hpp"

Terrain::Terrain() :
	cellSize(3.f),
	sub(4)
{
}

Map::Cell Terrain::getCell(float x, float y) const
{
	unsigned int i, j;

	i = y / cellSize * -1;
	j = x / cellSize;

	return mMap.getCell(i, j);
}

void Terrain::initFromMap(const Map &map)
{
	mMap = map;

	unsigned int tw = 50 * map.width, th = 50 * map.height;

	// Creating mesh
	// .. vertices
	for(unsigned int i = 0; i <= map.height * sub; i++)
	{
		for(unsigned int j = 0; j <= map.width * sub; j++)
		{
			e3e::Vector3d v(0,0,0);
			v.x = j * (cellSize / sub);
			v.y = i * (cellSize / sub) * -1;

			/*
			if(i != map.height * sub && j != map.width * sub)
			{
				Map::Cell cell = getCell(v.x, v.y);
				Map::Cell prevx_cell = getCell(v.x - cellSize/sub, v.y);
				Map::Cell prevy_cell = getCell(v.x, v.y + cellSize/sub);
				if(cell.type == Map::PATH ||
						prevx_cell.type == Map::PATH ||
						prevy_cell.type == Map::PATH)
				{
					v.z = -cellSize/3.f;
				}
			}
			*/

			vertices.push_back(v);

			e3e::Vector3d n(0,0,1);
			vertexNormals.push_back(n);

			e3e::Vector2d uv;
			uv.x = ((float) j)/((float) map.width * sub);
			uv.y = 1.f - ( ((float) i) / ((float) map.height * sub) );
			uvCoords.push_back(uv);

		}
	}

	// .. assembling faces
	for(unsigned int i = 0; i < map.height * sub; i++)
	{
		for(unsigned int j = 0; j < map.width * sub; j++)
		{
			unsigned int ci = i*((map.width * sub)+1) + j;
			e3e::Face f;
			f.indices.push_back(ci + 0); f.indices.push_back(ci + 1);
			f.indices.push_back(ci + ((map.width * sub)+1) + 1); f.indices.push_back(ci + ((map.width * sub)+1));
			faces.push_back(f);
		}
	}


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


	// generating texture :
	SDL_Rect cellImgPosition;
	for(unsigned int i = 0; i < map.height; i++)
	{
		for(unsigned int j = 0; j < map.width; j++)
		{
			// texture blit
			cellImgPosition.y = i*50;
			cellImgPosition.x = j*50;

			current_surface = map.getCell(i,j).type == Map::GROUND ? green_surface : yellow_surface;
			SDL_BlitSurface(current_surface, NULL, texture_surface, &cellImgPosition);
		}
	}

	// test export
	SDL_SaveBMP(texture_surface, "EXPORT_col.bmp");

	material.texture.loadTexture(texture_surface);

	SDL_FreeSurface(texture_surface);
	SDL_FreeSurface(yellow_surface);
	SDL_FreeSurface(green_surface);

	normal_state.vertex_normals_ok = true;
//	subdivideQuads();


//	material.diffuse = e3e::Color(1,0,0);
//	normal_state.draw_vertex_normals = true;
//	normal_state.draw_face_normals = true;

	initGeometry(false);
	initOpenGL();
}
