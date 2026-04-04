
#include "Coada.h"
#include <exception>
#include <iostream>

using namespace std;

Coada::Coada()
{
	prim = nullptr;
	ultim = nullptr;
}

void Coada::adauga(TElem elem)
{
	Nod *nodNou = new Nod{elem, ultim, nullptr};

	if (vida())
	{
		prim = nodNou;
		ultim = nodNou;
		return;
	}

	ultim->urmator = nodNou;
	ultim = nodNou;
}

// arunca exceptie daca coada e vida
TElem Coada::element() const
{
	if (vida())
	{
		throw exception();
	}

	return prim->element;
}

TElem Coada::sterge()
{
	if (vida())
	{
		throw exception();
	}

	Nod *nodSters = prim;
	TElem valoare = nodSters->element;

	prim = prim->urmator;
	if (prim != nullptr)
	{
		prim->anterior = nullptr;
	}
	else
	{
		ultim = nullptr;
	}

	delete nodSters;
	return valoare;
}

bool Coada::vida() const
{
	return prim == nullptr;
}

Coada::~Coada()
{
	while (!vida())
	{
		sterge();
	}
}
