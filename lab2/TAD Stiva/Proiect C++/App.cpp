#include <iostream>
#include <assert.h>
#include <exception>
#include "Stiva.h"

using namespace std;

void testStiva() {
	Stiva s;
	assert(s.vida() == true);

	try {
		s.element();
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}

	try {
		s.sterge();
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}

	s.adauga(10);
	s.adauga(20);
	s.adauga(30);

	assert(s.vida() == false);
	assert(s.element() == 30);
	assert(s.sterge() == 30);
	assert(s.element() == 20);
	assert(s.sterge() == 20);
	assert(s.sterge() == 10);
	assert(s.vida() == true);
}


int main() {
	testStiva();
	cout << "Testele pentru stiva au trecut.\n";
	return 0;
}
