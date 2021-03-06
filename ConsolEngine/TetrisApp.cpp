#pragma once

#include "TetrisApp.h"
#include "BaseApp.h"
#include "TetrisEngine/Field.cpp"
#include "TetrisEngine/PositionedFigure.cpp"
#include "TetrisEngine/Figure.cpp"

#include <strsafe.h>
#include <string>
#include <sstream>

using namespace TetrisEngine;
using namespace std;

TetrisApp::TetrisApp() : BaseApp(60, 80)
{
	this->started = false;
	this->startGame();
}

TetrisApp::~TetrisApp(void)
{
	delete this->field;
}

void TetrisApp::startGame()
{
	this->field = new Field(10, 30);
	this->timer = 0.0;
	this->stepTime = 0.5; // seconds to next step
}

void TetrisApp::KeyPressed(int btnCode)
{
	if (! this->started) {
		this->field->nextStep();
		this->started = true;
		// remove "Press any key" message
		this->drawText(1, 1, "                            ");
	}
	if (this->field->isFinished()) {
		if (btnCode == 113) {
			exit(0);
		} else if (btnCode == 114) {
			this->startGame();
		}
		return;
	}
	switch (btnCode) {
		case 75: { // left
			this->field->moveFigureLeft();
			break;
		}
		case 77: { // right
			this->field->moveFigureRight();
			break;
		}
		case 80: { // d
			this->field->moveFigureDown();
			this->timer = 0; // it's hopping...
			break;
		}
		case 113: { // q
			exit(0);
			break;
		}
		case 72: // up
		case 32: { // space
			this->field->rotateFigure();
			break;
		}
		case 0: { // specials
			break;
		}
		default: {
			char message[135];
			sprintf_s(message, "Button code: %d   ", btnCode);
			this->drawText(40, 1, message);
		}
	}
}

void TetrisApp::UpdateF(float deltaTime)
{
	if (! this->started) {
		this->drawField();
		this->drawText(1, 1, "Press any key to start game!");

		return;
	}

	if (this->field->isFinished()) {
		this->drawText(1, 1, "GAME OVER");

		return;
	}

	this->timer += deltaTime;
	while (this->timer > this->stepTime) {
		this->field->nextStep();
		this->timer -= this->stepTime;
	}
	this->drawField();
	char message[135];
	sprintf_s(message, "Delta time: %f", deltaTime);
	this->drawText(40, 0, message);
}

void TetrisApp::drawText(int x, int y, char* ch)
{
	int len = strlen(ch);
	for (int i = 0; i < len; i++) {
		SetChar(x + i, y, *(ch + i));
	}
}

void TetrisApp::drawField()
{
	SetChar(0, 0, L'╔');
	SetChar(this->field->getWidth() + 1, 0, L'╗');
	SetChar(0, this->field->getHeight() + 1, L'╚');
	SetChar(this->field->getWidth() + 1, this->field->getHeight() + 1, L'╝');
	for (int y = 0; y < this->field->getHeight(); y++) {
		SetChar(0, y + 1, L'║');
		SetChar(this->field->getWidth() + 1, y + 1, L'║');
	}
	for (int x = 0; x < this->field->getWidth(); x++) {
		SetChar(x + 1, 0, L'═');
		SetChar(x + 1, this->field->getHeight() + 1, L'═');
		for (int y = 0; y < this->field->getHeight(); y++) {
			SetChar(x + 1, y + 1, L' ');
		}
	}
	
	this->drawFigure(this->field->getWidth() + 5, 2, new Figure(5, 5), false);
	this->drawFigure(this->field->getWidth() + 5, 2, this->field->getNextFigure());
	this->drawFigure(1, 1, this->field->getMainFigure());

	PositionedFigure* figure = this->field->getCurrentFigure();

	if (figure == NULL) {
		return;
	}

	// plus borders
	this->drawFigure(figure->getX() + 1, figure->getY() + 1, figure->getFigure());
}

void TetrisApp::drawFigure(int x, int y, Figure* figure) {
	this->drawFigure(x, y, figure, true);
}

void TetrisApp::drawFigure(int x, int y, Figure* figure, bool transparent)
{
	for (int i = 0; i < figure->getWidth(); i++) {
		for (int j = 0; j < figure->getHeight(); j++) {
			wchar_t symbol = L'█';
			if (! figure->hasPointAt(i, j)) {
				if (transparent) {
					continue;
				}
				symbol = L' ';
			}
			SetChar(x + i, y + j, symbol);
		}
	}
}
