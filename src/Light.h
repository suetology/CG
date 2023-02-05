#pragma once

#include <glm/glm.hpp>

struct LightSource
{
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 lightColor;
	float ambientStrength;
};