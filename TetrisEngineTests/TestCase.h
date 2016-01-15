#pragma once

#include <string>

using namespace std;

class TestCase abstract
{
	private:	
		int testCount;
		int failureCount;
	protected:
		virtual void doRun()=0;

	public:
		TestCase();
		void assert(bool condition);
		void assert(bool condition, string errorMessage);
		void showResults();
		bool run();
};
