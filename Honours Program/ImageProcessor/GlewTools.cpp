#include "stdafx.h"
#include "GlewTools.h"


namespace GlewTools
{
	void printShaderError(const GLint shader) {
		int maxLength = 0;
		int logLength = 0;
		GLchar *logMessage;

		// Find out how long the error message is
		if (!glIsShader(shader))
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		else
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		if (maxLength > 0) { // If message has some contents
			logMessage = new GLchar[maxLength];
			if (!glIsShader(shader))
				glGetProgramInfoLog(shader, maxLength, &logLength, logMessage);
			else
				glGetShaderInfoLog(shader, maxLength, &logLength, logMessage);
			std::cout << "Shader Info Log:" << std::endl << logMessage << std::endl;
			delete[] logMessage;
		}
		// should additionally check for OpenGL errors here
	}


	GLuint initShaders(const char *vertFile, const char *fragFile) {
		GLuint p, f, v;

		char *vs, *fs;

		v = glCreateShader(GL_VERTEX_SHADER);
		f = glCreateShader(GL_FRAGMENT_SHADER);

		// load shaders & get length of each
		GLint vlen;
		GLint flen;
		vs = fileLoader::loadFile(vertFile, vlen);
		fs = fileLoader::loadFile(fragFile, flen);

		const char * vv = vs;
		const char * ff = fs;

		glShaderSource(v, 1, &vv, &vlen);
		glShaderSource(f, 1, &ff, &flen);

		GLint compiled;

		glCompileShader(v);
		glGetShaderiv(v, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			std::cout << "Vertex shader not compiled." << std::endl;
			printShaderError(v);
		}

		glCompileShader(f);
		glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			std::cout << "Fragment shader not compiled." << std::endl;
			printShaderError(f);
		}

		p = glCreateProgram();

		glAttachShader(p, v);
		glAttachShader(p, f);

		glBindAttribLocation(p, RT3D_VERTEX, "in_Position");
		glBindAttribLocation(p, RT3D_COLOUR, "in_Color");
		glBindAttribLocation(p, RT3D_NORMAL, "in_Normal");
		glBindAttribLocation(p, RT3D_TEXCOORD, "in_TexCoord");

		glLinkProgram(p);
		glUseProgram(p);

		delete[] vs; // dont forget to free allocated memory
		delete[] fs; // we allocated this in the loadFile function...

		return p;
	}


	void setUniformMatrix4fv(const GLuint program, const char* uniformName, const GLfloat *data) {
		int uniformIndex = glGetUniformLocation(program, uniformName);
		glUniformMatrix4fv(uniformIndex, 1, GL_FALSE, data);
	}



	void setLight(const GLuint program, const lightStruct light) {
		// pass in light data to shader
		

		int uniformIndex = glGetUniformLocation(program, "light.ambient");
		glUniform4fv(uniformIndex, 1, light.ambient);
		uniformIndex = glGetUniformLocation(program, "light.diffuse");
		glUniform4fv(uniformIndex, 1, light.diffuse);
		uniformIndex = glGetUniformLocation(program, "light.specular");
		glUniform4fv(uniformIndex, 1, light.specular);
		uniformIndex = glGetUniformLocation(program, "lightPosition");
		glUniform4fv(uniformIndex, 1, light.position);
	}

	


	void drawMesh(const GLuint mesh, const GLuint numVerts, const GLuint primitive) {
		glBindVertexArray(mesh);	// Bind mesh VAO
		glDrawArrays(primitive, 0, numVerts);	// draw first vertex array object
		glBindVertexArray(0);
	}


	void drawIndexedMesh(const GLuint mesh, const GLuint indexCount, const GLuint primitive) {
		glBindVertexArray(mesh);	// Bind mesh VAO
		glDrawElements(primitive, indexCount, GL_UNSIGNED_INT, 0);	// draw VAO 
		glBindVertexArray(0);
	}

	GLuint createMesh(const GLuint numVerts, const GLfloat* vertices, const GLfloat* colours,
		const GLfloat* normals, const GLfloat* texcoords, const GLuint indexCount, const GLuint* indices) {
		GLuint VAO;
		// generate and set up a VAO for the mesh
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		GLuint *pMeshBuffers = new GLuint[5];


		if (vertices == nullptr) {
			// cant create a mesh without vertices... oops
			//exitFatalError("Attempt to create a mesh with no vertices");
		}

		// generate and set up the VBOs for the data
		GLuint VBO;
		glGenBuffers(1, &VBO);

		// VBO for vertex data
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 3 * numVerts * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)RT3D_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(RT3D_VERTEX);
		pMeshBuffers[RT3D_VERTEX] = VBO;


		// VBO for colour data
		if (colours != nullptr) {
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, 3 * numVerts * sizeof(GLfloat), colours, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)RT3D_COLOUR, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(RT3D_COLOUR);
			pMeshBuffers[RT3D_COLOUR] = VBO;
		}

		// VBO for normal data
		if (normals != nullptr) {
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, 3 * numVerts * sizeof(GLfloat), normals, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)RT3D_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(RT3D_NORMAL);
			pMeshBuffers[RT3D_NORMAL] = VBO;
		}

		// VBO for tex-coord data
		if (texcoords != nullptr) {
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, 2 * numVerts * sizeof(GLfloat), texcoords, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)RT3D_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(RT3D_TEXCOORD);
			pMeshBuffers[RT3D_TEXCOORD] = VBO;
		}

		if (indices != nullptr && indexCount > 0) {
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);
			pMeshBuffers[RT3D_INDEX] = VBO;
		}
		// unbind vertex array
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		// return the identifier needed to draw this mesh

		//vertexArrayMap.insert(pair<GLuint, GLuint *>(VAO, pMeshBuffers));

		return VAO;
	}

}
