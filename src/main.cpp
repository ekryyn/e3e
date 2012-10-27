#include "e3e/Application.hpp"

int main(void)
{
	e3e::Application *app = e3e::Application::getInstance();
	app->run();

	return 0;
}
