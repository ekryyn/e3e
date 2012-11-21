#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "GL/glew.h"
#include <SDL.h>
#include <SDL_image.h>

namespace e3e
{

class Texture
{
public:
	Texture();

	void loadTexture(const char * filename, bool useMipMap=true);
	void loadTexture(SDL_Surface *surface, bool useMipMap=true);

	static SDL_Surface* flipSurface(SDL_Surface * surface);

	bool active;
	GLuint id;
};

}

#endif // TEXTURE_HPP
