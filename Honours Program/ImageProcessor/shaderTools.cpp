#include "stdafx.h"
#include "shaderTools.h"

namespace ShaderTools
{
	GLuint loadShader(const char* vert, const char* frag)
	{
		return GlewTools::initShaders(vert, frag);
	}

	void setProjection(GLuint shaderID, glm::mat4 projection)
	{
		GlewTools::setUniformMatrix4fv(shaderID, "projection", glm::value_ptr(projection));
	}

	void setMVP(GLuint shaderID, glm::mat4 stack)
	{
		GlewTools::setUniformMatrix4fv(shaderID, "modelview", glm::value_ptr(stack));
	}

	void setLight(GLuint shaderID, lightStruct light)
	{
		GlewTools::setLight(shaderID, light);
	}

	void setMaterial(const GLuint program, const materialStruct material) {
		// pass in material data to shader 
		int uniformIndex = glGetUniformLocation(program, "material.ambient");
		glUniform4fv(uniformIndex, 1, material.ambient);
		uniformIndex = glGetUniformLocation(program, "material.diffuse");
		glUniform4fv(uniformIndex, 1, material.diffuse);
		uniformIndex = glGetUniformLocation(program, "material.specular");
		glUniform4fv(uniformIndex, 1, material.specular);
		uniformIndex = glGetUniformLocation(program, "material.shininess");
		glUniform1f(uniformIndex, material.shininess);
	}

	void setAttenuation(const GLuint program, float con, float lin , float quad)
	{
		GLuint uniformIndex;
		// set light attenuation shader uniforms
		uniformIndex = glGetUniformLocation(program, "attConst");
		glUniform1f(uniformIndex, con);
		uniformIndex = glGetUniformLocation(program, "attLinear");
		glUniform1f(uniformIndex, lin);
		uniformIndex = glGetUniformLocation(program, "attQuadratic");
		glUniform1f(uniformIndex, quad);
	}
		

}

