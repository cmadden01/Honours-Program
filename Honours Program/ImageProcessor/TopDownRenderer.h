#pragma once
#include "stdafx.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Camera.h"
#include "OBJ.h"
#include <stack>

////
#include "shaderTools.h"
#include "GlewTools.h"
/////
#define DEG_TO_RADIAN 0.017453293

class TopDownRenderer
{
public:
	TopDownRenderer(GLuint shader);



	void draw(OBJ* object);
	
private:
	Camera* cam;
	GLuint shaderProgram;
	
	glm::mat4 projection;
	std::stack<glm::mat4> mvStack;
};
