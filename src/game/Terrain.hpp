#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "../e3e/Mesh.hpp"

#include "Map.hpp"

class Terrain : public e3e::Mesh
{
public:
	Terrain();

	void initFromMap(const Map &map);
	Map::Cell getCell(float x, float y) const;


private:

	void bump();

	float cellSize;

	Map mMap;
};

#endif // TERRAIN_HPP
