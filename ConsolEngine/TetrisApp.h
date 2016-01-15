#pragma once
#include "BaseApp.h"
#include "TetrisEngine/Field.h"
#include <string.h>

using namespace TetrisEngine;

class TetrisApp :
	public BaseApp
{
	protected:
		float timer;
		float stepTime;
		bool started;
		Field* field;
		void drawField();
		void drawFigure(int, int, Figure*);
		void drawFigure(int, int, Figure*, bool);
		void drawText(int, int, char*);
		void startGame();
	public:
		TetrisApp();
		~TetrisApp();
		virtual void KeyPressed(int btnCode);
		virtual void UpdateF(float deltaTime);
};
