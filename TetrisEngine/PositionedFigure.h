#pragma once

#include "Figure.h"

namespace TetrisEngine {

	class PositionedFigure
	{
		protected:
			Figure* figure;
			int x;
			int y;
		public:
			PositionedFigure(int, int, Figure*);
			int getX() { return this->x; }
			int getY() { return this->y; }
			Figure* getFigure() { return this->figure; }
			PositionedFigure* setX(int x) { this->x = x; return this; }
			PositionedFigure* setY(int y) { this->y = y; return this; }
	};
}