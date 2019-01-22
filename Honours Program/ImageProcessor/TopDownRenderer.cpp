#include "stdafx.h"
#include "TopDownRenderer.h"

TopDownRenderer::TopDownRenderer(GLuint shader)
{

	cam = new Camera(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));  //top down
	shaderProgram = shader;

	projection = glm::perspective(float(60.0f*DEG_TO_RADIAN), 800.0f / 600.0f, 0.5f, 1000.0f);
	GlewTools::setUniformMatrix4fv(shader, "projection", glm::value_ptr(projection));

	glm::mat4 Identity(1.0);
	mvStack.push(Identity);
	mvStack.top() = cam->view;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void TopDownRenderer::draw(OBJ* object)
{

	glUseProgram(shaderProgram);
	mvStack.push(mvStack.top());

	//transform
	mvStack.top() = glm::translate(mvStack.top(), object->position);
	mvStack.top() = glm::rotate((mvStack.top()), float(object->degrees * DEG_TO_RADIAN), object->rotation);
	mvStack.top() = glm::scale(mvStack.top(), object->scale);

	ShaderTools::setMVP(shaderProgram, mvStack.top());

	GlewTools::drawIndexedMesh(object->meshID, object->indices.size(), GL_TRIANGLES);

	mvStack.pop();

}