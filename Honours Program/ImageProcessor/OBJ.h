#pragma once
#include "stdafx.h"

#include <vector>
#include <glm.hpp>
#include <String>

#include <gtc/type_ptr.hpp>
#include "GlewTools.h"
#include "OBJ_Import.h"
#include "fileLoader.h"

class OBJ
{
public:
	OBJ(){}

	OBJ(const char* fName)
	{
		loadFromFile(fName);
	}

	void setTransform(glm::vec3 pos, glm::vec3 axi, glm::vec3 sca, float deg);
	void loadFromFile(const char* fName);
	void createMesh(int w, int h, float stride, std::string heightFile);

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	std::vector<GLfloat> faceNormals;		
	std::vector<GLfloat> vertexNormals;		

	glm::vec3 position;
	glm::vec3 rotation;
	float degrees;
	glm::vec3 scale;
	GLuint meshID;
	
private:
	OBJ_Import importer;

	void LoadVertices(std::string heightFile);
	void CreateIndices();
	void CreateFaceNormals();
	void CreateVertexNormals();

	int height;
	int width;
	float stride;
	int numOfVerts;
};


