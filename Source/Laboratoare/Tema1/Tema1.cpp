#include "Tema1.h"
#include "MyObject2D.h"
#include <time.h>

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

float birdBodyLength = 30.0f;
float birdBodyWidth = 30.0f;
float birdPositionX = 150.0f;
float birdPositionY = 350.0f;
float beakLength = 12.0f;
float beakWidth = 9.0f;
float birdSpeed = 0.0f;
float birdAcceleration;
float birdAngle = 0.0f;
float pipeSpeed = 0.0f;
float timeUntilNextPipe = 2.0f;
float pipeWidth = 160.0f;
float pipeSpace = 200.0f;
Mesh** pipes;
float* pipePositions;
float* lowerPipeHeight;
int numberOfPipes = 0;
bool betweenPipes = false;
int score = 0;
bool started = false;

void Tema1::Init()
{
	srand(time(NULL));

	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);


	glm::vec3 corner = glm::vec3(0, 0, 0);

	//cout << resolution.x << " x " << resolution.y << endl;
	pipes = (Mesh**)malloc(7 * sizeof(Mesh*));
	pipePositions = (float*)malloc(7 * sizeof(float));
	lowerPipeHeight = (float*)malloc(7 * sizeof(float));

	Mesh* bird = MyObject2D::CreateBird("bird", corner, birdBodyLength, birdBodyWidth, beakWidth, beakLength);
	AddMeshToList(bird);
	Mesh* background = MyObject2D::CreateRectangle("background", corner, (float)resolution.x, (float)resolution.y, glm::vec3(0, 0, 1));
	AddMeshToList(background);


}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	glm::vec3 corner = glm::vec3(0, 0, 0);

	/*if(!started)*/ {//verific posibile coliziuni, si inchei jocul in consecinta(width si length au ajuns sa fie egale ca sa simplific coliziunea)
		float hitboxDimesnion = sqrt(birdBodyLength * birdBodyLength + birdBodyWidth * birdBodyWidth);
		if (birdPositionY - hitboxDimesnion / 2 < 0) {
			cout << "Game over! Your final score is " << score << "!";
			free(pipes);
			free(pipePositions);
			free(lowerPipeHeight);
			exit(0);
		}
		else if (birdPositionY + hitboxDimesnion / 2 > 720) {
			cout << "Game over! Your final score is " << score << "!";
			free(pipes);
			free(pipePositions);
			free(lowerPipeHeight);
			exit(0);
		}
		else {
			for (int i = 1; i <= numberOfPipes; i++) {
				if (birdPositionX + (hitboxDimesnion / 2) > pipePositions[i] && birdPositionX - (hitboxDimesnion / 2) < pipePositions[i] + pipeWidth) {
					if (!(birdPositionY - (hitboxDimesnion / 2) > lowerPipeHeight[i] && birdPositionY + (hitboxDimesnion / 2) < lowerPipeHeight[i] + pipeSpace)) {
						cout << "Game over! Your final score is " << score << "!";
						free(pipes);
						free(pipePositions);
						free(lowerPipeHeight);
						exit(0);
					}
				}

			}
		}
	}


	{//calculez viteza pe axa OY si rotatia pasarii
		birdSpeed -= deltaTimeSeconds * birdAcceleration;
		birdPositionY += (birdSpeed * deltaTimeSeconds - birdAcceleration * deltaTimeSeconds * deltaTimeSeconds / 2);
		if (birdSpeed >= 350) {
			birdAngle = 3.14 / 4;
		}
		else if (birdSpeed <= -400) {
			birdAngle = -3.14 / 4;
		}
		else {
			birdAngle = (3.14 / 1500) * birdSpeed + 3.14 / 60;
		}

	}


	if (started) {//deplasez cu viteza constanta si afisez pipe-urile 
		for (int i = 1; i <= numberOfPipes; i++) {
			pipePositions[i] -= (pipeSpeed)*deltaTimeSeconds;
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(pipePositions[i], 0);
			RenderMesh2D(pipes[i], shaders["VertexColor"], modelMatrix);

		}
	}



	{//verific trecerea de la spatiul dintre 2 pipe-uri la spatiu liber(se mareste punctajul daca e cazul)
		if (betweenPipes == false) {
			for (int i = 1; i <= numberOfPipes; i++) {
				if (birdPositionX >= pipePositions[i] && birdPositionX <= pipePositions[i] + pipeWidth) {
					betweenPipes = true;
					break;
				}
			}
		}
		else {
			for (int i = 1; i < numberOfPipes; i++) {
				if (birdPositionX >= pipePositions[i] + pipeWidth && birdPositionX <= pipePositions[i + 1]) {
					betweenPipes = false;
					score++;
					cout << "Score +1 : " << score << endl;
					break;
				}
			}
		}
	}

	if (started) {//generez pipe-uri cu spatiul dintre ele pozitionat la intamplare, la interval regulat
		timeUntilNextPipe -= deltaTimeSeconds;
		if (timeUntilNextPipe <= 0) {
			numberOfPipes += 1;

			float lph = rand() % 300 + 150;
			lowerPipeHeight[numberOfPipes] = lph;

			pipes[numberOfPipes] = MyObject2D::CreatePipes("pipe", corner, lph, pipeWidth, pipeSpace);

			pipePositions[numberOfPipes] = 1280.0f;

			timeUntilNextPipe = 1.2f;

		}

	}

	if (started) {//ma asigur ca nu pastrez pipe-uri in plus, si nu le afisez
		if (numberOfPipes == 6) {
			for (int i = 1; i < numberOfPipes; i++) {
				pipes[i] = pipes[i + 1];
				lowerPipeHeight[i] = lowerPipeHeight[i + 1];
				pipePositions[i] = pipePositions[i + 1];
			}
			numberOfPipes--;
		}
	}

	{//afisez pasarea
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(birdPositionX, birdPositionY);
		modelMatrix *= Transform2D::Rotate(birdAngle);
		RenderMesh2D(meshes["bird"], shaders["VertexColor"], modelMatrix);
	}


	{//afisez fundalul
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["background"], shaders["VertexColor"], modelMatrix);
	}
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema1::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE && !started) {
		birdAcceleration = 660.0f;
		pipeSpeed = 320.0f;
		birdSpeed = 350.0f;
		started = true;
	}
	else if (key == GLFW_KEY_SPACE && started) {
		birdSpeed = 350.0f;
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
