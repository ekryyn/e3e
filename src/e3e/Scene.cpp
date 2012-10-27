#include "Scene.hpp"

e3e::Scene::Scene()
{
}


void e3e::Scene::drawAxis(float scale)
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3ub(0,0,255);
	glVertex3f(0,0,0);
	glVertex3f(0,0,scale);
	glColor3ub(0,255,0);
	glVertex3f(0,0,0);
	glVertex3f(0,scale,0);
	glColor3ub(255,0,0);
	glVertex3f(0,0,0);
	glVertex3f(scale,0,0);
	glColor3ub(255,255,255);
	glEnd();
	glEnable(GL_LIGHTING);
}

void e3e::Scene::render()
{

	drawAxis(.9f);
}
