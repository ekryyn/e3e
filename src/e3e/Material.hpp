#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Color.hpp"
#include "Texture.hpp"

namespace e3e
{

class Material
{
public:

	typedef struct
	{
		float diffuse;
	} Influence;

	Material();

	Color diffuse;
	Texture texture;

	Influence textureInfluence;

};

}

#endif // MATERIAL_HPP
