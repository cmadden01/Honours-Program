#pragma once
#include "stdafx.h"
#include <GL/glew.h>
#include "fileLoader.h"
#include <iostream>

#define RT3D_VERTEX		0
#define RT3D_COLOUR		1
#define RT3D_NORMAL		2
#define RT3D_TEXCOORD   3
#define RT3D_INDEX		4

//Light definition
struct lightStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat position[4];
};

struct materialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
};

namespace GlewTools
{
	void printShaderError(const GLint shader);
	GLuint initShaders(const char *vertFile, const char *fragFile);
	void setUniformMatrix4fv(const GLuint program, const char* uniformName, const GLfloat *data);
	void setLight(const GLuint program, const lightStruct light);

	void drawMesh(const GLuint mesh, const GLuint numVerts, const GLuint primitive);
	void drawIndexedMesh(const GLuint mesh, const GLuint indexCount, const GLuint primitive);

	GLuint createMesh(const GLuint numVerts, const GLfloat* vertices, const GLfloat* colours,
		const GLfloat* normals, const GLfloat* texcoords, const GLuint indexCount, const GLuint* indices);





}
