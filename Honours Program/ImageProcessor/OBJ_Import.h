#pragma once
#include "stdafx.h"
#include <Vector>
#include "fileLoader.h"


#include "GL/glew.h"

class OBJ_Import
{
private:
	
public:

	void loadObj(const char* filename, std::vector<GLfloat> &verts, std::vector<GLfloat> &norms,
		std::vector<GLfloat> &texcoords, std::vector<GLuint> &indices);

	char* loadFile(const char *fname, GLint &fSize);
};
