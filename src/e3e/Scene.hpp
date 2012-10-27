#ifndef SCENE_HPP
#define SCENE_HPP

#include <GL/glew.h>

namespace e3e
{

class Scene
{
public:
	Scene();

	void drawAxis(float scale);
	void render();
};

}
#endif // SCENE_HPP
