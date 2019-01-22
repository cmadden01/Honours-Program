#pragma once
#include "stdafx.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


class Camera
{
public:
	Camera() {};

	Camera(glm::vec3 up, glm::vec3 eye, glm::vec3 att)
	{
		this->up = up;
		this->eye = eye;
		this->at = att;

		view = glm::lookAt(eye, at, up);
	}

	glm::mat4 view;

private:
	glm::vec3 up;
	glm::vec3 eye;
	glm::vec3 at;
};
