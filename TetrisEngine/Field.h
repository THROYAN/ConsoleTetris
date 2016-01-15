#pragma once

#include "Figure.h"
#include "PositionedFigure.h"


namespace TetrisEngine {

	class Field
	{
		private:
			PositionedFigure* currentFigure;
			Figure* nextFigure;
			Figure* mainFigure;
			int width;
			int height;
			bool finished;
		public:
			Field(int w, int h);// : width(w), height(h) { this->init(); };
			Field();// : width(10), height(40) { this->init(); };
			void nextStep();
			PositionedFigure* getCurrentFigure() { return this->currentFigure; }
			Figure* getNextFigure() { return this->nextFigure; }
			Figure* getMainFigure() { return this->mainFigure; }
			void moveFigureLeft();
			void moveFigureRight();
			void moveFigureDown();
			void rotateFigure();
			int getWidth() { return this->width; }
			int getHeight() { return this->height; }
			bool outOfBounds(int, int, Figure*);
			bool isFinished() { return this->finished; }
		protected:
			Figure* generateRandomFigure();
			void init();
			void takeNextFigure();
	};
}