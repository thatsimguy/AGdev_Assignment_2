#include <iostream>
using namespace std;

#include "introstate.h"
#include "GL\glew.h"
#include "../Application.h"
#include "LoadTGA.h"
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "../TextEntity.h"
#include "RenderHelper.h"
#include "../SpriteEntity.h"
#include "../EntityManager.h"

#include "KeyboardController.h"
#include "SceneManager.h"

//I need to improve on the Main Menu Thingy,shit it does not look lit enough 
//Main Menu Logic works , TIme for the Artsy partsy Stuff
//Intro State-> Menu State-> (1)GameState , (2)Instructions,(3)Exit



CMenuState::CMenuState()
{

}
CMenuState::~CMenuState()
{

}

void CMenuState::Init()
{
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("MENUSTATE_BKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("MENUSTATE_BKGROUND")->textureID = LoadTGA("Image//MenuState.tga");

	MeshBuilder::GetInstance()->GenerateQuad("ARROW", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("ARROW")->textureID = LoadTGA("Image//Arrow.tga");


	float halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;
	MenuStateBackground = Create::Sprite2DObject("MENUSTATE_BKGROUND", 
												 Vector3(halfWindowWidth, halfWindowHeight, 0.0f), 
												 Vector3(800.0f, 600.0f, 0.0f));
	Arrow = Create::Sprite2DObject("ARROW",
		Vector3(halfWindowWidth, halfWindowHeight, 2.f),
		Vector3(25.0f, 25.0f, 25.0f));

	cout << "CMenuState loaded\n" << endl;
}
void CMenuState::Update(double dt)
{
	

	EntityManager::GetInstance()->Update(dt);

	float halfWindowWidth = (float)Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = (float)Application::GetInstance().GetWindowHeight() / 2.0f;

	MenuStateBackground->SetPosition(Vector3(halfWindowWidth, halfWindowHeight, 0.f));
	MenuStateBackground->SetScale(Vector3((float)Application::GetInstance().GetWindowWidth(),
		(float)Application::GetInstance().GetWindowHeight(), 0.f));

	Arrow->SetPosition((Vector3(halfWindowWidth, halfWindowHeight, 2.f)));
	Arrow->SetScale(Vector3((float)Application::GetInstance().GetWindowWidth() / 32,
		(float)Application::GetInstance().GetWindowHeight() / 24, 0.f));

	//Delay timer to prevent spamming button
	Delay += (float)dt;
	if (Delay > 0.5f)
		Delay = 0.5f;


	//Selection of Type
	if(KeyboardController::GetInstance()->IsKeyDown(VK_UP) && Delay >= ButtonCooldown
		|| KeyboardController::GetInstance()->IsKeyDown('W') && Delay >= ButtonCooldown)
	{
		if (SelectedOptions == Quit)
			SelectedOptions = Instructions;
		else if (SelectedOptions == Instructions)
			SelectedOptions = GAME;
		else if (SelectedOptions == GAME)
			SelectedOptions = Quit;
		Delay = 0.0f;
	}
	if (KeyboardController::GetInstance()->IsKeyDown(VK_DOWN) && Delay >= ButtonCooldown
		|| KeyboardController::GetInstance()->IsKeyDown('S') && Delay >= ButtonCooldown)
	{
		if (SelectedOptions == GAME)
			SelectedOptions = Instructions;
		else if (SelectedOptions == Instructions)
			SelectedOptions = Quit;
		else if (SelectedOptions == Quit)
			SelectedOptions = GAME;
		Delay = 0.0f;
	}

	//Confirm selection
	if (KeyboardController::GetInstance()->IsKeyDown(VK_RETURN) && Delay >= ButtonCooldown)
	{
		if (SelectedOptions == GAME) {
			SceneManager::GetInstance()->SetActiveScene("GameState");

		}
		else if (SelectedOptions == Instructions)
			SceneManager::GetInstance()->SetActiveScene("InstructionsState");
		else if (SelectedOptions == Quit)
			exit(0);
		Delay = 0.0f;
	}


	switch (SelectedOptions)
	{
	case GAME:
		b_GAME = true;
		b_INSTRUCTIONS = false;
		b_quit = false;
		break;
	case Instructions:
		b_GAME = false;
		b_INSTRUCTIONS = true;
		b_quit = false;
		break;
	case Quit:
		b_GAME = false;
		b_INSTRUCTIONS = false;
		b_quit = true;
		break;
	}

	//Update the position of the arrow based on the boolens 
	if (b_GAME)
		Arrow->SetPosition(Vector3((float)Application::GetInstance().GetWindowWidth() / 3.2f,
		(float)Application::GetInstance().GetWindowHeight() / 1.875f, 2.f));
	if (b_INSTRUCTIONS)
		Arrow->SetPosition(Vector3((float)Application::GetInstance().GetWindowWidth() / 3.2f,
		(float)Application::GetInstance().GetWindowHeight() / 2.5f, 2.f));
	if (b_quit)
		Arrow->SetPosition(Vector3((float)Application::GetInstance().GetWindowWidth() / 3.2f,
		(float)Application::GetInstance().GetWindowHeight() / 4.f, 2.f));

}
void CMenuState::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//GraphicsManager::GetInstance()->UpdateLightUniforms();

	// Setup 3D pipeline then render 3D
	GraphicsManager::GetInstance()->SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Render the required entities
	EntityManager::GetInstance()->Render();

	// Setup 2D pipeline then render 2D
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, 
															  Application::GetInstance().GetWindowWidth(), 
															  0, 
															  Application::GetInstance().GetWindowHeight(), 
															  -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();

	// Render the required entities
	EntityManager::GetInstance()->RenderUI();
}
void CMenuState::Exit()
{
	// Remove the entity from EntityManager
	EntityManager::GetInstance()->RemoveEntity(MenuStateBackground);

	// Remove the meshes which are specific to CMenuState
	MeshBuilder::GetInstance()->RemoveMesh("MENUSTATE_BKGROUND");
	MeshBuilder::GetInstance()->RemoveMesh("Arrow");
	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}