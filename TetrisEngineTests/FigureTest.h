#pragma once

#include <string>
#include "TestCase.h"

using namespace std;

class FigureTest: public TestCase
{
	protected:
		virtual void doRun() override;
		void testConstructor();
		void testFlips();
		void testRotates();
		void testInterceptions();
		void testMerges();
		void testDeleteLine();
	public:
		FigureTest(void);
};
