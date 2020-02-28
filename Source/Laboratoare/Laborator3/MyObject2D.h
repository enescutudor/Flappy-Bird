#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace MyObject2D {
	Mesh* CreateBird(std::string name, glm::vec3 leftBottomVertice, float length, float width, float beakBase, float beakLength);
	Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomVertice, float length, float width, glm::vec3 color);
	Mesh* CreateTriangle(std::string name, glm::vec3 leftBottomVertice, float height, float base, glm::vec3 color);
	Mesh* CreatePipes(std::string name, glm::vec3 leftBottomVertic, float lowerPipeHeight, float pipeWidth, float space);
}
