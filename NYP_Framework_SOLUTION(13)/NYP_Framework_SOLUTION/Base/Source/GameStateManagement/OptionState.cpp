#include <iostream>
using namespace std;

#include "OptionState.h"
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

COptionState::COptionState()
{
}

COptionState::~COptionState()
{
}

void COptionState::Init()
{
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("OPTIONS_BKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("OPTIONS_BKGROUND")->textureID = LoadTGA("Image//MenuState.tga");
}

void COptionState::Update(double dt)
{

}

void COptionState::Render()
{
}

void COptionState::Exit()
{
}
