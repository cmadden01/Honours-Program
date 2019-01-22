#pragma once
#include <fstream>
#include <iostream>
#include <GL/glew.h>

#include <glm.hpp>
#include <vector>
#include <String>


namespace fileLoader
{
	char* loadFile(const char *fname, GLint &fSize);
	float* loadHeightMatrix(int dataCount, std::string heightFile);
}
