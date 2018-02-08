
#include <iostream>
using namespace std;
#include "InstructionsState.h"
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

#include "InstructionsState.h"


//Hey Hey he didn't say its not possible right ? :3
CInstructionState::CInstructionState()
{
}

CInstructionState::~CInstructionState()
{
}

void CInstructionState::Init()
{
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("INSTRUCTIONSTATE_BKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("INSTRUCTIONSTATE_BKGROUND")->textureID = LoadTGA("Image//InstructionsState.tga");

	MeshBuilder::GetInstance()->GenerateQuad("ARROW", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("ARROW")->textureID = LoadTGA("Image//Arrow.tga");

	float halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;
	InstructionStateBackground = Create::Sprite2DObject("INSTRUCTIONSTATE_BKGROUND",
		Vector3(halfWindowWidth, halfWindowHeight, 0.0f),
		Vector3(800.0f, 600.0f, 0.0f));
	Arrow = Create::Sprite2DObject("ARROW",
		Vector3(halfWindowWidth, halfWindowHeight, 2.f),
		Vector3(25.0f, 25.0f, 25.0f));

	cout << "CInstructionState loaded\n" << endl;
}

void CInstructionState::Update(double dt)
{
	EntityManager::GetInstance()->Update(dt);

	float halfWindowWidth = (float)Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = (float)Application::GetInstance().GetWindowHeight() / 2.0f;

	InstructionStateBackground->SetPosition(Vector3(halfWindowWidth, halfWindowHeight, 0.f));
	InstructionStateBackground->SetScale(Vector3((float)Application::GetInstance().GetWindowWidth(),
		(float)Application::GetInstance().GetWindowHeight(), 0.f));

	Arrow->SetPosition((Vector3(halfWindowWidth, halfWindowHeight, 2.f)));
	Arrow->SetScale(Vector3((float)Application::GetInstance().GetWindowWidth() / 32,
		(float)Application::GetInstance().GetWindowHeight() / 24, 0.f));



	//Delay timer to prevent spamming button
	delay += (float)dt;
	if (delay > 0.5f)
	{
		delay = 0.5f;
	}
		

	////Selection of Type
	//if (KeyboardController::GetInstance()->IsKeyDown(VK_UP) && delay >= ButtonCooldown
	//	|| KeyboardController::GetInstance()->IsKeyDown('W') && delay >= ButtonCooldown)
	//{
	//	/*if (SelectedOptions == Game) 
	//	{
	//		SelectedOptions = Return;
	//		

	//	}
	//	else if (SelectedOptions == Return)
	//	{
	//		SelectedOptions = Game;
	//		
	//	}*/

	//	//if (SelectedOptions == Exit)
	//	//{
	//	//	SelectedOptions = Exit;
	//	//}

	//	delay = 0.0f;
	//}
	

	//Confirm Selection

	if (KeyboardController::GetInstance()->IsKeyDown(VK_RETURN) && delay >= ButtonCooldown)
	{
		exit(0);
		delay = 0.0f;
	}


	switch (SelectedOptions)
	{
	case Game:
		b_GAME = true;
		b_RETURN = false;
		break;
	case Return:
		b_GAME = false;
		b_RETURN = true;
		break;



	}


	if (b_GAME)
		Arrow->SetPosition(Vector3((float)Application::GetInstance().GetWindowWidth() / 3.2f,
		(float)Application::GetInstance().GetWindowHeight() / 8.875f, 2.f));
	if (b_RETURN)
		Arrow->SetPosition(Vector3((float)Application::GetInstance().GetWindowWidth() / 3.2f,
		(float)Application::GetInstance().GetWindowHeight() / 10.5f, 2.f));


}


void CInstructionState::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

void CInstructionState::Exit()
{
	// Remove the entity from EntityManager
	//EntityManager::GetInstance()->RemoveEntity(InstructionStateBackground);
	MeshBuilder::GetInstance()->RemoveMesh("INSTRUCTIONSTATE_BKGROUND");
	MeshBuilder::GetInstance()->RemoveMesh("ARROW");
	GraphicsManager::GetInstance()->DetachCamera();
	InstructionStateBackground->SetIsDone(true);

}
