#include "Application.hpp"
#include <iostream>
#include <cstdio>
#include <sstream>
#include <cmath>

#include "EventManager.hpp"
#include "KeyRegister.hpp"

#include "game/Terrain.hpp"
#include "game/Map.hpp"
#include "game/MapFileReader.hpp"

Application::Application():
	w(800), h(600),
	_time(0),
	lastTime(0)
{
	srand(time(0));
	EventManager::getInstance()->subscribe(this);
	EventManager::getInstance()->subscribe(KeyRegister::getInstance());

	sf::WindowSettings settings;
	settings.DepthBits         = 16;
	settings.StencilBits       = 8;
	settings.AntialiasingLevel = 2;
	window = new sf::Window(sf::VideoMode(w, h, 16), "SFML OpenGL", sf::Style::Close, settings);

	fillColor = e3e::Color(.5,.5,.5);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
		glEnable (GL_BLEND);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);

	GLenum code;
	/* initialisation de GLEW */
	code = glewInit();
	if(code != GLEW_OK)
	{
		fprintf(stdout, "impossible d'initialiser GLEW : %s\n",
				  glewGetErrorString(code));
	}
	else
	{
		fprintf(stdout, "glew OK\n");
	}

	if(glCreateShader == NULL)
		std::cout << "shaders non supportes" << std::endl;
	else
		std::cout << "shaders OK" << std::endl;

	fflush(stdout);


	// default scene
	currentScene = new e3e::Scene(w,h);

	camera = new FPSCamera(w/float(h), 40);
	currentScene->setCamera(camera);

	EventManager::getInstance()->subscribe(camera);

	MapFileReader reader("res/map1.map");

	Terrain *terrain = new Terrain();
	terrain->initFromMap(reader.getMap());

	currentScene->addNode( new e3e::Node(terrain) );

}

void Application::run()
{

	sf::Clock frameClock, globalClock;

	running = true;


	frameClock.Reset();
	globalClock.Reset();

	float fps = 1/60.f;
	int frameCount = 0;

	window->ShowMouseCursor(true);

	while (running)
	{
		EventManager::getInstance()->captureEvent(window);

		float elapsedTime	= frameClock.GetElapsedTime();
		if(elapsedTime >= fps)
		{
			// -- OpenGL drawing
			glClearColor(fillColor.r, fillColor.g, fillColor.b, fillColor.a);
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			camera->move();

			currentScene->render();

			glFlush();
			// --

			window->Display();
			frameClock.Reset();
			frameCount++;
		}

		if(globalClock.GetElapsedTime() >= 1.f)
		{
			std::cout << "FPS: " << frameCount << std::endl;
			globalClock.Reset();
			frameCount = 0;
		}
	}
}


void Application::resetMouse()
{
	window->SetCursorPosition(w/2, h/2);
}


float Application::frameTime()
{
	return window->GetFrameTime();
}

void Application::onEvent(const sf::Event &event)
{
	switch(event.Type)
	{
	case sf::Event::Closed:
		running = false;
		break;

	case sf::Event::KeyReleased:
		if(event.Key.Code == sf::Key::Escape)
		{
			window->ShowMouseCursor(true);
			grabMouse(false);
		}
		break;

	case sf::Event::MouseButtonReleased:
		grabMouse(true);
		window->ShowMouseCursor(false);
		break;
	default:
		break;

	}
}


