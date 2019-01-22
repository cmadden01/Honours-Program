#pragma once
//Shader.h
//Utility functions for shader programs.

#include "GlewTools.h"

#include <glm.hpp>
#include <gtc/type_ptr.hpp>


namespace ShaderTools
{
	GLuint loadShader(const char* vert, const char* frag);
	void setProjection(GLuint shaderID, glm::mat4 projection);
	void setMVP(GLuint shaderID, glm::mat4 stack);
	void setLight(GLuint shaderID, lightStruct light);
	void setMaterial(const GLuint program, const materialStruct material);

	void setAttenuation(const GLuint program, float, float,float);
}





