#pragma once

#include "Scene.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "../FPSCamera.h"
#include "../SpriteEntity.h"

class SceneManager;
class CMenuState : public Scene
{
public:
	CMenuState();
	~CMenuState();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	enum MenuState
	{
		GAME,
		Instructions,
		Credits,
		Quit,
	};

private:
	FPSCamera camera;
	SpriteEntity* MenuStateBackground;
	//	TextEntity* textObj[3];

	CMenuState(SceneManager* _sceneMgr); // This is used to register to SceneManager
	ShaderProgram* currProg;

	std::string fps;
	float Delay = 0.0f;
	const float ButtonCooldown = 0.20f;

	static MenuState* sInstance;

	MenuState SelectedOptions = GAME;
	//SpriteEntity* MainMenu;
	SpriteEntity* Arrow;

	bool b_GAME;
	bool b_INSTRUCTIONS;
	bool b_quit;

};
