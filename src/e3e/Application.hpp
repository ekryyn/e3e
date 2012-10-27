#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <ctime>
#include <map>

#include "Color.hpp"
#include "EventListener.hpp"
#include "Singleton.hpp"
#include "Scene.hpp"

namespace e3e
{

class Application : public EventListener, public Singleton<Application>
{
	friend class Singleton<Application>;
public:

	float frameTime();

	void run();

	virtual void onEvent(const sf::Event &event);
	void resetMouse();

	inline int getWidth(){ return w; }
	inline int getHeight(){ return h; }

private:
	Application();
	int w, h;
	float _time;
	float lastTime;

	bool running;

	sf::Window *window;
	e3e::Color fillColor;

	e3e::Scene *currentScene;
};

}

#endif // APPLICATION_HPP
