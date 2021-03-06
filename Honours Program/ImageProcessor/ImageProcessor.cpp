// ImageProcessor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "SDLSetup.h"
#include "TopDownRenderer.h"
#include "shaderTools.h"
#include "OBJ.h"

#include <SDL.h>
#include <SDL_image.h>

#include <sstream>



// light attenuation
float attConstant = 1.0f;
float attLinear = 0.1f;
float attQuadratic = 0.1f;

lightStruct globalLight{
{ 0.4f, 0.4f, 0.4f, 1.0f }, // ambient
{ 1.0f, 1.0f, 1.0f, 1.0f }, // diffuse
{ 1.0f, 1.0f, 1.0f, 1.0f }, // specular
{ 0.0, -5.0f, -0.5f, 1.0f }  // position
};


materialStruct material
{
	{ 0.5f, 0.5f, 0.5f, 1.0f }, // ambient
	{ 0.5f, 0.5f, 0.5f, 1.0f }, // diffuse
	{ 0.8f, 0.8f, 0.8f, 1.0f }, // specular
	1.0f  // shininess
};








void OutputAsPNG(int w, int h, std::string outputName)
{
	SDL_Surface * image;
	std::vector<char> pixels(w * h * 3);

	//Buffer Read
	glReadBuffer(GL_BACK);
	glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

	//write to PNG using SDL
	Uint32 rmask, gmask, bmask, amask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN //I took this code from somewhere
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	image =
		SDL_CreateRGBSurface(0,
			w,
			h,
			24,
			rmask,
			gmask,
			bmask,
			amask);

	image->pixels = pixels.data();
	IMG_SavePNG(image, outputName.data());

	SDL_FreeSurface(image);
}






int main(int argc, char *argv[])
{
	//Cretae window and context
	SDLSetup *sdlGlewObject = new SDLSetup();
	sdlGlewObject->createWindow();
	sdlGlewObject->setupRenderContext();


	//Inititalise shader and renderer
	GLuint shader = ShaderTools::loadShader("simpleVert.vert", "simpleFrag.frag");
	TopDownRenderer* render = new TopDownRenderer(shader);
	ShaderTools::setAttenuation(shader, attConstant,attLinear,attQuadratic);
	ShaderTools::setLight(shader, globalLight);
	ShaderTools::setMaterial(shader, material);


	//Fractal model
	OBJ* fractal = new OBJ();
	fractal->setTransform(glm::vec3(-3, -8, 3), glm::vec3(1, 0, 0), glm::vec3(1, 1, 1), 0);
	fractal->createMesh(100, 100, 0.05, "Heights_0.5_0.txt");
	fractal->degrees = 180;

	int count = 0;

	//game loop

	while (sdlGlewObject->running)
	{ 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sdlGlewObject->pollEvent();
	
		
		
		//Draw
		render->draw(fractal);
		//fractal->degrees += 0.02;

		//Moing Light
		///globalLight.position[2] += 0.001;
		///ShaderTools::setLight(shader, globalLight);
		
			
		//Output PNG Image
		std::stringstream num;
		num << count;
		///OutputAsPNG(800, 600, "output" + num.str() + ".png");
		
		sdlGlewObject->swapWindow();

		count++;
	}

	sdlGlewObject->deleteContext();
    return 0;
}













/*


//The fractal model has only faces, needs reproduce properly
//i think. Don't forget you need the (X,z) uniform grid to accompany
//the produced Y values.
std::vector<GLfloat> tmpHeights;

//Load x and z grid values (lengh, depth, stride).
loadGrid(3, 3, 0.2);

//Generate the height values.
///float* heightValues = fileLoader::loadHeightMatrix();

for (int i = 0; i < 9; i++)
{
///getline(fileIn, heightString, ' ');
///extractedVal = atof(heightString.c_str());
///heightVal[i] = extractedVal*10;
tmpHeights.push_back(i * 0.2);
}

//Combine grid with height values creating the vertices.
std::vector<GLfloat> verts;
for (int i = 0; i < 9; i++)
{
verts.push_back(horizGridPoints[i]);

verts.push_back(tmpHeights[i]);

verts.push_back(vertGridPoints[i]);
}



GLuint meshid = GlewTools::createMesh(verts.size() / 3, verts.data(), nullptr,
nullptr, nullptr, NULL, nullptr);


OBJ* fractal = new OBJ();
fractal->setTransform(glm::vec3(0, -10, 0), glm::vec3(1, 0, 0), glm::vec3(1, 1, 1), 0);
fractal->meshID = meshid;
fractal->vertices = verts;

*/
