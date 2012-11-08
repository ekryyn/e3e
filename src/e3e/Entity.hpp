#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Shader.hpp"

namespace e3e
{

class Entity
{
public:
	virtual void render(Shader *shader) = 0;
};

}

#endif // ENTITY_HPP
