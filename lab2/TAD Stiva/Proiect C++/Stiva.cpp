
#include "Stiva.h"
#include <exception>
#include <iostream>

using namespace std;


Stiva::Stiva() {
	varf = nullptr;
}


void Stiva::adauga(TElem elem) {
	Nod* nodNou = new Nod{ elem, varf };
	varf = nodNou;
}

//arunca exceptie daca coada e vida
TElem Stiva::element() const {
	if (vida()) {
		throw exception();
	}

	return varf->element;
}

TElem Stiva::sterge() {
	if (vida()) {
		throw exception();
	}

	Nod* nodSters = varf;
	TElem valoare = nodSters->element;
	varf = varf->urmator;

	delete nodSters;
	return valoare;
}

bool Stiva::vida() const {
	return varf == nullptr;
}


Stiva::~Stiva() {
	while (!vida()) {
		sterge();
	}
}

