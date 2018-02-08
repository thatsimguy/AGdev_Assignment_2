#pragma once
#include "Scene.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "../FPSCamera.h"
#include "../SpriteEntity.h"
//#include "ShaderProgram.h"


class SceneManager;

class CInstructionState : public Scene
{
public:
	CInstructionState();
	~CInstructionState();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	enum InstructionState
	{
		Game,
		Return,
	};


private:
	FPSCamera camera;
	SpriteEntity* InstructionStateBackground;

	CInstructionState(SceneManager* _sceneMgr);
	//ShaderProgram* currProg;


	std::string fps;
	float delay = 0.0f;
	const float ButtonCooldown = 0.20f;
	static InstructionState* sInstance;
	InstructionState SelectedOptions = Game;
	SpriteEntity* Arrow;

	bool b_GAME;
	bool b_RETURN;

};