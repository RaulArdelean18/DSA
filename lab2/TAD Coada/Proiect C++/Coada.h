#pragma once
using namespace std;

typedef int TElem;

class Coada
{
private:
	struct Nod
	{
		TElem element;
		Nod *anterior;
		Nod *urmator;
	};

	Nod *prim;
	Nod *ultim;

public:
	/*
	Construieste o coada vida
	pre: true
	post: coada este vida
	complexitate: Theta(1)
	*/
	Coada();

	/*
	Adauga un element la sfarsitul cozii
	pre: true
	post: elementul e este adaugat la sfarsitul cozii
	complexitate: Theta(1)
	*/
	void adauga(TElem e);

	/*
	Returneaza primul element din coada
	pre: coada nu este vida
	post: returneaza primul element din coada
	complexitate: Theta(1)
	*/
	TElem element() const;

	/*
	Elimina si returneaza primul element din coada
	pre: coada nu este vida
	post: elimina si returneaza primul element din coada
	complexitate: Theta(1)
	*/
	TElem sterge();

	/*
	Verifica daca coada este vida
	pre: true
	post: returneaza true iff coada este vida
	complexitate: Theta(1)
	*/
	bool vida() const;

	/*
	Elibereaza memoria ocupata de coada
	pre: true
	post: memoria ocupata de coada este eliberata
	complexitate: Theta(n)
	*/
	~Coada();
};
