#pragma once

#include <vector>

namespace TetrisEngine {

	class Figure
	{
		private:
			std::vector<bool> *coords;
			int width;
			int height;
		protected:
			void init(int, int, std::vector<bool>*);
		public:
			Figure(int width, int height, std::vector<bool> *coords);
			Figure(int width, int height, bool* coords);
			Figure(int width, int height);
			int getWidth() { return this->width; }
			int getHeight() { return this->height; }
			bool hasPointAt(int, int);
			Figure* rotateLeft();
			Figure* rotateRight();
			Figure* flipHorizontally();
			Figure* flipVertically();
			bool isIntercept(int x, int y, Figure* figure);
			Figure* merge(int x, int y, Figure* figure);
			Figure* deleteFullLines();
	};
}
