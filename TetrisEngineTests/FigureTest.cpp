#include "StdAfx.h"
#include "FigureTest.h"
#include "TetrisEngine/Figure.h"
#include "TetrisEngine/Figure.cpp"
#include <vector>

using namespace std;
using namespace TetrisEngine;


void checkCoords(TestCase* test, Figure* figure, bool* coords, string actionMessage)
{
	int width = figure->getWidth();
	for (int y = 0; y < figure->getHeight(); y++) {
		for (int x = 0; x < width; x++) {
			bool hasPoint = (*(coords + x + y * width) == 1);
			char message[135];
			sprintf_s(
				message,
				"figure %s point at %d, %d%s",
				hasPoint ? "has" : "doesn't have",
				x,
				y,
				actionMessage.empty() ? "" : (" as " + actionMessage).c_str()
			);
			// cout << "Test: " << message << endl;
			test->assert(figure->hasPointAt(x, y) == hasPoint, message);
		}
	}
}

void checkCoords(TestCase* test, Figure* figure, bool* coords)
{
	checkCoords(test, figure, coords, "");
}

FigureTest::FigureTest(void)
{
}

void FigureTest::doRun()
{
	this->testConstructor();
	this->testFlips();
	this->testRotates();
	this->testInterceptions();
	this->testMerges();
	this->testDeleteLine();
}

void FigureTest::testConstructor()
{
	bool coords[6] = {
		1, 1, 1,
		1, 0, 0
	};
	/*bool coordsToCheck[6] = {
		1, 1, 1,
		0, 0, 1
	};*/
	bool *coordsToCheck = coords;
	
	Figure *f = new Figure(3, 2, coords);

	checkCoords(this, f, coordsToCheck);
}

void FigureTest::testFlips()
{
	bool origin[6] = {
			1, 1, 1,
			1, 0, 0
		},
		flippedV[6] = {
			1, 0, 0,
			1, 1, 1
		},
		flippedH[6] = {
			1, 1, 1,
			0, 0, 1
		},
		flippedHV[6] = {
			0, 0, 1,
			1, 1, 1
		}
	;
	Figure *f = new Figure(3, 2, origin);

	checkCoords(this, f, origin);
	checkCoords(this, f->flipHorizontally(), flippedH, "flip horizontally");
	checkCoords(this, f->flipVertically(), flippedV, "flip vertically");
	checkCoords(this, f->flipVertically()->flipHorizontally(), flippedHV, "flip vertically and then flip horizontally");
	checkCoords(this, f->flipHorizontally()->flipVertically(), flippedHV, "flip horizontally and then flip vertically");
	checkCoords(this, f->flipVertically()->flipVertically(), origin, "twice flip vertically");
	checkCoords(this, f->flipHorizontally()->flipHorizontally(), origin, "twice flip horizontally");
}

void FigureTest::testRotates()
{
	bool origin[6] = {
			1, 1, 1,
			1, 0, 0
		},
		rot90[6] = {
			1, 0,
			1, 0,
			1, 1
		},
		rot180[6] = {
			0, 0, 1,
			1, 1, 1
		},
		rot270[6] = {
			1, 1,
			0, 1,
			0, 1
		}
	;
	Figure *f = new Figure(3, 2, origin);

	checkCoords(this, f, origin);
	checkCoords(this, f->rotateLeft(), rot90, "rotate left");
	checkCoords(this, f->rotateLeft()->rotateLeft(), rot180, "rotate left twice");
	checkCoords(this, f->rotateLeft()->rotateLeft()->rotateLeft(), rot270, "rotate left thrice");
	checkCoords(this, f->rotateLeft()->rotateLeft()->rotateLeft()->rotateLeft(), origin, "rotate left fourfold");

	checkCoords(this, f->rotateRight(), rot270, "rotate right");
	checkCoords(this, f->rotateRight()->rotateRight(), rot180, "rotate right twice");
	checkCoords(this, f->rotateRight()->rotateRight()->rotateRight(), rot90, "rotate right thrice");
	checkCoords(this, f->rotateRight()->rotateRight()->rotateRight()->rotateRight(), origin, "rotate right fourfold");

	checkCoords(this, f->rotateLeft()->rotateRight(), origin, "rotate left and then right");
	checkCoords(this, f->rotateRight()->rotateLeft(), origin, "rotate right and then left");
}

void FigureTest::testInterceptions()
{
	bool coords1[6] = {
			1, 1, 1,
			1, 0, 0
		},
		coords2[10] = {
			0, 0,
			0, 0,
			0, 0,
			1, 0,
			1, 1
		};
	Figure *f1 = new Figure(3, 2, coords1),
		*f2 = new Figure(2, 5, coords2);

	this->assert(! f2->isIntercept(0, 0, f1), "testInterceptions assert 1 is true");
	this->assert(! f2->isIntercept(1, 0, f1), "testInterceptions assert 2 is true");
	this->assert(! f2->isIntercept(1, 2, f1), "testInterceptions assert 3 is true");
	this->assert(f2->isIntercept(0, 2, f1), "testInterceptions assert 4 is true");
	this->assert(f2->isIntercept(1, 3, f1), "testInterceptions assert 5 is true");
}

void FigureTest::testMerges()
{
	bool coords[6] = {
			1, 1, 1,
			1, 0, 0
		},
		main[25] = {
			0, 0, 0, 1, 0,
			0, 1, 1, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 1, 1, 1,
			1, 1, 1, 1, 1
		},
		merged1[25] = {
			//
			1, 1, 1, 1, 0, //
			1, 1, 1, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 1, 1, 1,
			1, 1, 1, 1, 1
		},
		merged2[25] = {
			     //
			0, 0, 0, 1, 0,
			0, 1, 1, 1, 1, //
			1, 0, 1, 0, 1,
			1, 0, 1, 1, 1,
			1, 1, 1, 1, 1
		},
		merged3[25] = {
			  //
			0, 0, 0, 1, 0,
			0, 1, 1, 0, 1,
			1, 1, 1, 1, 1, //
			1, 1, 1, 1, 1,
			1, 1, 1, 1, 1
		},
		merged4[25] = {
			            //
			0, 0, 0, 1, 1, //
			0, 1, 1, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 1, 1, 1,
			1, 1, 1, 1, 1
		};
	Figure* f = new Figure(3, 2, coords),
		* mainF = new Figure(5, 5, main);

	checkCoords(this, mainF->merge(0, 0, f), merged1, "merge1");
	checkCoords(this, mainF->merge(2, 1, f), merged2, "merge2");
	checkCoords(this, mainF->merge(1, 2, f), merged3, "merge3");
	checkCoords(this, mainF->merge(4, 0, f), merged4, "merge4");
}

void FigureTest::testDeleteLine()
{
	bool main1[25] = {
			0, 0, 0, 1, 0,
			0, 1, 1, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 1, 1, 1,
			1, 1, 1, 1, 1
		},
		removed1[25] = {
			0, 0, 0, 0, 0,
			0, 0, 0, 1, 0,
			0, 1, 1, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 1, 1, 1
		},
		main2[25] = {
			0, 0, 0, 1, 0,
			1, 1, 1, 1, 1,
			1, 0, 1, 0, 1,
			1, 0, 1, 1, 1,
			1, 1, 1, 1, 1
		},
		removed2[25] = {
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 1, 0,
			1, 0, 1, 0, 1,
			1, 0, 1, 1, 1
		},
		main3[25] = {
			0, 0, 0, 1, 1,
			0, 1, 1, 0, 1,
			1, 0, 0, 0, 1,
			1, 0, 1, 1, 1,
			0, 1, 1, 1, 1
		};
	Figure* mainF1 = new Figure(5, 5, main1),
		* mainF2 = new Figure(5, 5, main2),
		* mainF3 = new Figure(5, 5, main3);

	checkCoords(this, mainF1->deleteFullLines(), removed1, "removed1");
	checkCoords(this, mainF2->deleteFullLines(), removed2, "removed2");
	checkCoords(this, mainF3->deleteFullLines(), main3, "removed3");
}
