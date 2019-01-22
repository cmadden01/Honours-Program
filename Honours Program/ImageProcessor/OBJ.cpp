#include "stdafx.h"
#include "OBJ.h"


//loads OBJ format 
void OBJ::loadFromFile(const char* fName)
{
	std::vector<GLfloat> tmpVertices;
	std::vector<GLfloat> tmpNorms;
	std::vector<GLfloat> tmpTexcoords;
	std::vector<GLuint> tmpIndices;
	
	importer.loadObj(fName, tmpVertices, tmpNorms, tmpTexcoords, tmpIndices);

	meshID = GlewTools::createMesh(tmpVertices.size(), tmpVertices.data(), nullptr,
		tmpNorms.data(), nullptr, tmpIndices.size(), tmpIndices.data());

	vertices = tmpVertices;
	indices = tmpIndices;
	vertexNormals = tmpNorms;
}

void OBJ::setTransform(glm::vec3 pos, glm::vec3 axi, glm::vec3 scal, float deg)
{
	position = pos;
	rotation= axi;
	degrees = deg;
	scale = scal;
}

void OBJ::LoadVertices(std::string heightFile)
{
	std::vector<GLfloat> vertGridPoints;
	std::vector<GLfloat> horizGridPoints;
	

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			vertGridPoints.push_back(stride * y);
			horizGridPoints.push_back(stride * x);
		}
	}

	float* gridHeights = fileLoader::loadHeightMatrix(numOfVerts, heightFile);

	for (int i = 0; i < numOfVerts; i++)
	{
		vertices.push_back(horizGridPoints[i]);
		vertices.push_back(gridHeights[i]);
		vertices.push_back(vertGridPoints[i]);
	}
}

void OBJ::CreateIndices()
{
	int loopCount = numOfVerts - width - 1;;

	for (int i = 0; i < loopCount; i++)
	{
		int FirstSkip = width - 1;
		int NextSkip = width;
		int LoopMax = FirstSkip * (height + 1);

		for (int x = FirstSkip; x <= LoopMax; x += NextSkip)
		{
			if (i == x)
			{
				i++;
			}
		}


		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + width + 1);

		indices.push_back(i);
		indices.push_back(i + width + 1);
		indices.push_back(i + width);
	}
}

void OBJ::CreateFaceNormals()
{
	float p1;
	float p2;
	float p3;

	glm::vec3 u;
	glm::vec3 v;

	faceNormals.resize(indices.size());

	for (int i = 0; i < indices.size() - 2; i += 3)
	{
		//the Index of the vertices for the current face
		int i1 = indices[i];
		int i2 = indices[i + 1];
		int i3 = indices[i + 2];

		//Store the 3 vertices of the face using the indeces to access the verts container
		glm::vec3 p1(vertices[i1 * 3], vertices[i1 * 3 + 1], vertices[i1 * 3 + 2]);
		glm::vec3 p2(vertices[i2 * 3], vertices[i2 * 3 + 1], vertices[i2 * 3 + 2]);
		glm::vec3 p3(vertices[i3 * 3], vertices[i3 * 3 + 1], vertices[i3 * 3 + 2]);

		//Calculate normal
		u = p2 - p1;
		v = p3 - p1;

		glm::vec3 faceNorm = glm::normalize(glm::cross(u, v));

		//Store Normal
		faceNormals[i] = faceNorm.x;
		faceNormals[i + 1] = faceNorm.y;
		faceNormals[i + 2] = faceNorm.z;
	}
}

void OBJ::CreateVertexNormals()
{
	for (int i = 0; i < vertices.size() / 3; i++)
	{
		std::vector<glm::vec3> normals;

		for (int x = 0; x < indices.size() - 2; x += 3)
		{
			if (indices[x] == i | indices[x + 1] == i | indices[x + 2] == i)
			{
				normals.push_back(glm::vec3(faceNormals[x], faceNormals[x + 1], faceNormals[x + 2]));
			}
		}

		glm::vec3 normalSum(0, 0, 0);

		for (int y = 0; y < normals.size(); y++)
		{
			normalSum += normals[y];
		}

		glm::vec3 vertextNormal = normalSum / glm::vec3(normals.size());

		vertexNormals.push_back(vertextNormal.x);
		vertexNormals.push_back(vertextNormal.y);
		vertexNormals.push_back(vertextNormal.z);
	}


	
}

void OBJ::createMesh(int w, int h, float stride, std::string heightFile)
{
	width = w;
	height = h;
	numOfVerts = w * h;
	this->stride = stride;

	LoadVertices(heightFile);
	CreateIndices();
	CreateFaceNormals();
	CreateVertexNormals();

	meshID = GlewTools::createMesh(vertices.size()/3, vertices.data(), nullptr,
		vertexNormals.data(), nullptr, indices.size(), indices.data());

}


