#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>

class Map
{
public:
	enum Type
	{
		GROUND = 0,
		PATH = 1,
		DOOR = 2,
		HOME = 3,
		ROCK = 4,
		ERR = 99
	};

	struct Cell
	{
		Type type;
		unsigned int posI;
		unsigned int posJ;
	};

	Map();
	Map(const std::vector< std::vector< Map::Cell > > &cellMap);

	std::vector<Cell> getDoors();
	Cell nextPathCellFrom(Cell current);

	void setVisited(unsigned int i, unsigned int j, bool val);
	bool isVisited(unsigned int i, unsigned int j);


	Cell getCell(unsigned int i, unsigned int j) const;

	unsigned int width, height;

private:
	std::vector< std::vector< Cell > > cells;
	std::vector< std::vector< bool > > visited;
};

#endif // MAP_HPP
