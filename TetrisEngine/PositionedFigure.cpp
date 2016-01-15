#include "StdAfx.h"
#include "PositionedFigure.h"


namespace TetrisEngine {

	PositionedFigure::PositionedFigure(int x, int y, Figure* figure)
	{
		this->x = x;
		this->y = y;
		this->figure = figure;
	}
}