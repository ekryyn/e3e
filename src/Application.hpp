#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <ctime>
#include <map>

#include "e3e/Color.hpp"
#include "e3e/Singleton.hpp"
#include "e3e/Scene.hpp"
#include "EventListener.hpp"
#include "FPSCamera.hpp"


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
	FPSCamera *camera;
};

#endif // APPLICATION_HPP
