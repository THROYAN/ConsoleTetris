#include "StdAfx.h"
#include "Figure.h"
#include <vector>

using namespace std;

namespace TetrisEngine {

	Figure::Figure(int width, int height, vector<bool> *coords)
	{
		this->init(width, height, coords);
	}

	Figure::Figure(int width, int height, bool* coords)
	{
		this->init(
			width,
			height,
			new vector<bool>(coords, coords + (width * height)/* / sizeof coords[0]*/)
		);
	}

	Figure::Figure(int width, int height)
	{
		this->init(
			width,
			height,
			new vector<bool>(width * height, false)
		);
	}

	void Figure::init(int width, int height, vector<bool> *coords)
	{
		this->width = width;
		this->height = height;
		this->coords = new vector<bool>(width * height);

		// copy full vector
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				(*this->coords)[i + j * width] = coords->at(i + j * width);
			}
		}
	}

	bool Figure::hasPointAt(int x, int y) {
		return this->coords->at(x + y * this->width);
	}

	Figure* Figure::flipVertically() {
		vector<bool> flippedV(this->width * this->height);

		for (int i = 0; i < this->width; i++) {
			for (int j = 0; j < this->height; j++) {
				flippedV[i + j * this->width] = this->coords->at(i + (this->height - j - 1) * this->width);
			}
		}

		return new Figure(this->width, this->height, &flippedV);
	}

	Figure* Figure::flipHorizontally() {
		vector<bool> flippedH(this->width * this->height);

		for (int i = 0; i < this->width; i++) {
			for (int j = 0; j < this->height; j++) {
				flippedH[i + j * this->width] = this->coords->at((this->width - i - 1) + j * this->width);
			}
		}

		return new Figure(this->width, this->height, &flippedH);
	}

	Figure* Figure::rotateLeft() {
		// height and width are switched
		int width = this->height;
		int height = this->width;

		vector<bool> rotated(width * height);

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				rotated[i + j * width] = this->coords->at(
					(this->width - j - 1) + i * this->width
				);
			}
		}

		return new Figure(width, height, &rotated);
	}

	Figure* Figure::rotateRight() {
		// height and width are switched
		int width = this->height;
		int height = this->width;

		vector<bool> rotated(width * height);

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				rotated[i + j * width] = this->coords->at(
					(this->height - i - 1) * this->width + j
				);
			}
		}

		return new Figure(width, height, &rotated);
	}

	bool Figure::isIntercept(int x, int y, Figure* figure)
	{
		int width = min(this->getWidth(), x + figure->getWidth());
		int height = min(this->getHeight(), y + figure->getHeight());
		for (int i = x; i < width; i++) {
			for (int j = y; j < height; j++) {
				if (this->hasPointAt(i, j) && figure->hasPointAt(i - x, j - y)) {
					return true;
				}
			}
		}

		return false;
	}

	Figure* Figure::merge(int x, int y, Figure* figure)
	{
		int width = this->getWidth();
		int height = this->getHeight();
		int fWidth = figure->getWidth();
		int fHeight = figure->getHeight();
		vector<bool> newCoords(width * height, false);

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				newCoords[i + j * width] =
					(i >= x && j >= y && (i - x) < fWidth && (j - y) < fHeight && figure->hasPointAt(i - x, j - y))
					|| (i < width && j < height && this->hasPointAt(i, j))
				;
			}
		}

		return new Figure(width, height, &newCoords);
	}

	Figure* Figure::deleteFullLines()
	{
		vector<bool> newCoords;
		for (int j = 0; j < this->getHeight(); j++) {
			bool f = true;
			vector<bool> line;
			for (int i = 0; i < this->getWidth(); i++) {
				if (! this->hasPointAt(i, j)) {
					f = false;
				}
				line.push_back(this->hasPointAt(i, j));
			}
			if (f) {
				newCoords.insert(newCoords.begin(), this->getWidth(), false); // insert empty line
				continue;
			}
			newCoords.insert(newCoords.end(), line.begin(), line.end()); // copy line
		}

		return new Figure(this->getWidth(), newCoords.size() / this->getWidth(), &newCoords);
	}
}
