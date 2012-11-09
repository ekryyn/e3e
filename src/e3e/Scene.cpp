#include "Scene.hpp"
#include "Vector3d.hpp"

#include "MeshManager.hpp"

e3e::Scene::Scene(int w, int h) :
	camera(NULL),
	w(w), h(h)
{
	projectionShader.loadVert("shaders/e3e.vert");
	projectionShader.loadFrag("shaders/e3e.frag");
	projectionShader.link();

	reloadProjectionMatrix();

	// add test cube
//	e3e::Node *parent = new e3e::Node(e3e::MeshManager::getInstance()->createUVSphere());
//	parent->translate(-2.5, 0, 0.5);

	e3e::Node *parent = e3e::MeshManager::getInstance()->createNodeFromFile("res/test.dae");

//	e3e::Node *parent2 = new e3e::Node(this, e3e::MeshManager::getInstance()->createCube(1));
//	parent2->translate(2.5, .5, 0);

	//	e3e::Node *child = new e3e::Node(this, new e3e::Cube());
	//	child->translate(2.2, 0, 0);
	//	parent->addChildNode(child);

	sceneNodes.push_back( parent );
//	sceneNodes.push_back( parent2 );
}

void e3e::Scene::setCamera(Camera *c)
{
	camera = c;
	reloadProjectionMatrix();
}

void e3e::Scene::reloadProjectionMatrix()
{
	if(camera)
	{
		GLint projectionMatrixUniform = projectionShader.getUniformLocation("projectionMatrix");

		e3e::Matrix4f pm = camera->getProjectionMatrix();

		float *pmcm = pm.createColumnMajorArray();

		projectionShader.use();
		glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, pmcm);

		delete pmcm;
	}
}

void e3e::Scene::cameraUpdated()
{
	this->reloadProjectionMatrix();
}

void e3e::Scene::applyMatrix()
{
	GLint worldTransformMatrixUniform = projectionShader.getUniformLocation("worldTransformMatrix");
	float *tcm = sceneMatrixStack.top()->createColumnMajorArray();

	projectionShader.use();
	glUniformMatrix4fv(worldTransformMatrixUniform, 1, GL_FALSE, tcm);

	delete tcm;
}

void e3e::Scene::drawAxis(float scale)
{
	float data[3*6*2]; unsigned int i=0;
	// pos
	data[i++] = 0; data[i++] = 0; data[i++] = 0;
	data[i++] = scale; data[i++] = 0; data[i++] = 0;
	data[i++] = 0; data[i++] = 0; data[i++] = 0;
	data[i++] = 0; data[i++] = scale; data[i++] = 0;
	data[i++] = 0; data[i++] = 0; data[i++] = 0;
	data[i++] = 0; data[i++] = 0; data[i++] = scale;
	//colors
	data[i++] = 1; data[i++] = 0; data[i++] = 0;
	data[i++] = 1; data[i++] = 0; data[i++] = 0;
	data[i++] = 0; data[i++] = 1; data[i++] = 0;
	data[i++] = 0; data[i++] = 1; data[i++] = 0;
	data[i++] = 0; data[i++] = 0; data[i++] = 1;
	data[i++] = 0; data[i++] = 0; data[i++] = 1;

	// init //
	GLuint axis;
	glGenBuffers(1, &axis);
	glBindBuffer(GL_ARRAY_BUFFER, axis);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(data)/2));
	// draw//
	glDrawArrays(GL_LINES, 0, 6);
	// clean //
	glDeleteBuffers(1, &axis);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void e3e::Scene::render()
{
	static float time = 0.f;
	sceneMatrixStack.push();
	e3e::Matrix4f m = camera->lookAt(e3e::Vector3d(), e3e::Vector3d());
	sceneMatrixStack.transform(m);

	GLint timeUniform = projectionShader.getUniformLocation("time");
	glUniform1f(timeUniform, time += 0.005f);

	drawAxis(1.f);

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	std::vector<e3e::Node*>::iterator it;
	for(it = sceneNodes.begin(); it != sceneNodes.end(); it++)
	{
		(*it)->render(this, &projectionShader);
	}
	sceneMatrixStack.pop();
}

