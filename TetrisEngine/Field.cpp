#include "StdAfx.h"
#include "Field.h"
#include "Figure.h"
#include "PositionedFigure.h"
#include <cstdlib>

namespace TetrisEngine {
	Figure* Field::generateRandomFigure()
	{
		Figure* figure;

		switch (rand() % 5) {
			case 0: {
				bool coords[6] = {
					1, 1, 1,
					0, 1, 0
				};
				figure = new Figure(3, 2, coords);
				break;
			}
			case 1: {
				bool coords[6] = {
					1, 1, 1,
					0, 0, 1
				};
				figure = new Figure(3, 2, coords);
				break;
			}
			case 2: {
				bool coords[6] = {
					1, 1, 0,
					0, 1, 1
				};
				figure = new Figure(3, 2, coords);
				break;
			}
			case 3: {
				bool coords[4] = {
					1, 1,
					1, 1
				};
				figure = new Figure(2, 2, coords);
				break;
			}
			case 4: {
				bool coords[4] = {
					1, 1, 1, 1
				};
				figure = new Figure(4, 1, coords);
				break;
			}
		}

		for (int i = 0; i < (rand() % 5); i++) {
			switch (rand() % 4) {
				case 0: {
					figure = figure->flipHorizontally();
					break;
				}
				case 1: {
					figure = figure->flipVertically();
					break;
				}
				case 2: {
					figure = figure->rotateLeft();
					break;
				}
				case 3: {
					figure = figure->rotateRight();
					break;
				}
			}
		}

		return figure;
	}
			
	void Field::init()
	{
		this->nextFigure = this->generateRandomFigure();
		this->currentFigure = NULL;

		this->mainFigure = new Figure(this->width, this->height);
		this->finished = false;
	}

	Field::Field(int w, int h)
	{
		this->width = w;
		this->height = h;
		this->init();
	};

	Field::Field()
	{
		this->width = 5;
		this->height = 5;
		this->init();
	};

	void Field::nextStep()
	{
		if (this->currentFigure == NULL) {
			this->takeNextFigure();
			return;
		}
		// todo: check collision

		this->moveFigureDown();
		this->mainFigure = this->mainFigure->deleteFullLines();
	}

	void Field::takeNextFigure()
	{
		this->currentFigure = new PositionedFigure((int) (this->width / 2), 0, this->nextFigure);
		this->nextFigure = this->generateRandomFigure();
		
		this->mainFigure = this->mainFigure->deleteFullLines();

		if (this->outOfBounds(this->currentFigure->getX(), this->currentFigure->getY(), this->currentFigure->getFigure())) {
			this->finished = true;
		}
	}

	void Field::moveFigureLeft()
	{
		int newX = this->currentFigure->getX() - 1;
		if (this->outOfBounds(newX, this->currentFigure->getY(), this->currentFigure->getFigure())) {
			return;
		}
		this->currentFigure->setX(newX);
	}

	void Field::moveFigureRight()
	{
		int newX = this->currentFigure->getX() + 1;
		if (this->outOfBounds(newX, this->currentFigure->getY(), this->currentFigure->getFigure())) {
			return;
		}
		this->currentFigure->setX(newX);
	}

	void Field::moveFigureDown()
	{
		int newY = this->currentFigure->getY() + 1;
		if (this->outOfBounds(this->currentFigure->getX(), newY, this->currentFigure->getFigure())) {
			this->mainFigure = this->mainFigure->merge(
				this->currentFigure->getX(),
				this->currentFigure->getY(),
				this->currentFigure->getFigure()
			);
			this->takeNextFigure();

			return;
		}
		this->currentFigure->setY(newY);
	}

	void Field::rotateFigure()
	{
		Figure* newFigure = this->currentFigure->getFigure()->rotateLeft();

		// todo: check collisions
		if (this->outOfBounds(this->currentFigure->getX(), this->currentFigure->getY(), newFigure)) {
			return;
		}

		this->currentFigure	= new PositionedFigure( // dull rotate...
			this->currentFigure->getX(),
			this->currentFigure->getY(),
			newFigure
		);
	}

	bool Field::outOfBounds(int x, int y, Figure* figure)
	{
		return x + figure->getWidth() > this->width
			|| x < 0
			|| y < 0
			|| y + figure->getHeight() > this->height
			|| this->mainFigure->isIntercept(x, y, figure)
		;
	}
}
