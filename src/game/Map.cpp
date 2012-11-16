#include "Map.hpp"

Map::Map()
{
}

Map::Map(const std::vector< std::vector< Map::Cell > > &cellMap)
{
	width = cellMap[0].size();
	height = cellMap.size();
	cells = cellMap;

	visited.resize(height, std::vector<bool>(width));
	for(unsigned int i=0; i<height; i++)
		for(unsigned int j=0; j<width; j++)
			visited[i][j] = false;
}

bool Map::isVisited(unsigned int i, unsigned int j)
{
	return visited[i][j];
}

void Map::setVisited(unsigned int i, unsigned int j, bool val)
{
	visited[i][j] = val;
}

Map::Cell Map::nextPathCellFrom(Cell current)
{
	Cell left = current, top = current, right = current, bottom = current;
	if(current.posI > 0)
		top.posI -= 1;
	if(current.posI < height-1)
		bottom.posI += 1;
	if(current.posJ > 0)
		left.posJ -= 1;
	if(current.posJ < width-1)
		right.posJ += 1;

	if((cells[left.posI][left.posJ].type & Map::PATH) == Map::PATH
			&& !visited[left.posI][left.posJ])
		return left;
	else if((cells[right.posI][right.posJ].type & Map::PATH) == Map::PATH
			  && !visited[right.posI][right.posJ])
		return right;
	else if((cells[top.posI][top.posJ].type & Map::PATH) == Map::PATH
			  && !visited[top.posI][top.posJ])
		return top;
	else if((cells[bottom.posI][bottom.posJ].type & Map::PATH) == Map::PATH
			  && !visited[bottom.posI][bottom.posJ])
		return bottom;

	return current;

}

Map::Cell Map::getCell(unsigned int i, unsigned int j)
{
	return cells[i][j];
}

std::vector<Map::Cell> Map::getDoors()
{
	std::vector<Cell> res;
	for(unsigned int i=0; i<height; i++)
	{
		for(unsigned int j=0; j<width; j++)
		{
			Cell c = cells[i][j];
			if(c.type == Map::DOOR)
				res.push_back(c);
		}
	}
	return res;
}
