#include "StdAfx.h"
#include "TestCase.h"

using namespace std;

#define STOP_ON_FAILURE false

TestCase::TestCase(void)
{
}

void TestCase::showResults()
{
	cout << "Asserts: " << this->testCount << endl
		<< "Failures: " << this->failureCount << endl;
}

void TestCase::assert(bool condition, string str) {
	this->testCount++;

	if ( ! condition) {
		this->failureCount++;
		cout << "Failed asserting that: " << str << endl;

		if (STOP_ON_FAILURE) {
			this->showResults();
			throw exception("Tests failed!");
		}
	}
}

void TestCase::assert(bool condition)
{
	this->assert(condition, "some condition is true");
}

bool TestCase::run()
{
	this->testCount = 0;
	this->failureCount = 0;

	try {
		
		this->doRun();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	cout << endl << "Total results:" << endl;
	this->showResults();

	return this->failureCount == 0;
}