#include "MyObject2D.h"

#include <Core/Engine.h>
#include <math.h>

Mesh* MyObject2D::CreateBird(std::string name, glm::vec3 center, float length, float width, float beakBase, float beakLength)
{

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center + glm::vec3(length / 2 - beakBase, beakBase, 0), glm::vec3(1, 0, 0)),
		VertexFormat(center + glm::vec3(length / 2 - beakBase / 2 , beakBase, 0), glm::vec3(1, 0, 0)),
		VertexFormat(center + glm::vec3(length / 2 - beakBase / 2, 3 * beakBase / 2, 0), glm::vec3(1, 0, 0)),
		VertexFormat(center + glm::vec3(length / 2 - beakBase, 3 * beakBase / 2, 0), glm::vec3(1, 0, 0)),

		VertexFormat(center, glm::vec3(1, 1, 0)),
		VertexFormat(center + glm::vec3(-length / 2, width / 2, 0), glm::vec3(1, 1, 0)),
		VertexFormat(center + glm::vec3(length / 2, width / 2, 0), glm::vec3(1, 1, 0)),
		VertexFormat(center + glm::vec3(length / 2, -width / 2, 0), glm::vec3(1, 1, 0)),
		VertexFormat(center + glm::vec3(-length / 2, -width / 2, 0), glm::vec3(1, 1, 0)),

		VertexFormat(center + glm::vec3(length / 2, -beakBase / 2, 0), glm::vec3(1, 0, 0)),
		VertexFormat(center + glm::vec3(length / 2 + beakLength, 0, 0), glm::vec3(1, 0, 0)),
		VertexFormat(center + glm::vec3(length / 2, beakBase / 2, 0), glm::vec3(1, 0, 0)),

		
	};

	Mesh* bird = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2,
											0, 2, 3,
											4, 6, 5,
											4, 7, 6,
											4, 8, 7,
											9, 10, 11};

	bird->InitFromData(vertices, indices);
	return bird;
}

Mesh* MyObject2D::CreateRectangle(std::string name, glm::vec3 leftBottomVertice, float length, float width, glm::vec3 color)
{
	glm::vec3 corner = leftBottomVertice;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, width, 0), color),
		VertexFormat(corner + glm::vec3(0, width, 0), color),

	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 2, 3, 0};

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}

Mesh* MyObject2D::CreateTriangle(std::string name, glm::vec3 leftBottomVertice, float height, float base, glm::vec3 color)
{

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(leftBottomVertice, color),
		VertexFormat(leftBottomVertice + glm::vec3(height, base / 2, 0), color),
		VertexFormat(leftBottomVertice + glm::vec3(0, base, 0), color),
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2};

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* MyObject2D::CreatePipes(std::string name, glm::vec3 leftBottomVertice, float lowerPipeHeight, float pipeWidth, float space) {
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(leftBottomVertice, glm::vec3(0, 1, 0)),
		VertexFormat(leftBottomVertice + glm::vec3(pipeWidth, 0, 0), glm::vec3(0, 1, 0)),
		VertexFormat(leftBottomVertice + glm::vec3(pipeWidth, lowerPipeHeight, 0), glm::vec3(0, 1, 0)),
		VertexFormat(leftBottomVertice + glm::vec3(0, lowerPipeHeight, 0), glm::vec3(0, 1, 0)),

		VertexFormat(leftBottomVertice + glm::vec3(0, space + lowerPipeHeight, 0), glm::vec3(0, 1, 0)),
		VertexFormat(leftBottomVertice + glm::vec3(pipeWidth, space + lowerPipeHeight, 0), glm::vec3(0, 1, 0)),
		VertexFormat(leftBottomVertice + glm::vec3(pipeWidth, 1280, 0), glm::vec3(0, 1, 0)),
		VertexFormat(leftBottomVertice + glm::vec3(0, 1280, 0), glm::vec3(0, 1, 0)),
	};

	Mesh* pipes = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2,
											0, 2, 3,
											4, 5, 6,
											4, 6, 7};
	pipes->InitFromData(vertices, indices);
	return pipes;
}

