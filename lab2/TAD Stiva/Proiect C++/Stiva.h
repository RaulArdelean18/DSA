#pragma once

using namespace std;

typedef int TElem;

class Stiva
{
	private:
		struct Nod {
			TElem element;
			Nod* urmator;
		};

		Nod* varf;

	public:
		/*
		Construieste o stiva vida
		pre: true
		post: stiva este vida
		complexitate: Theta(1)
		*/
		Stiva();

		/*
		Adauga un element in varful stivei
		pre: true
		post: elementul e este adaugat in varful stivei
		complexitate: Theta(1)
		*/
		void adauga(TElem e);

		/*
		Returneaza elementul din varful stive
		pre: stiva nu este vida
		post: returneaza elementul din varful stivei
		complexitate: Theta(1)
		*/
		TElem element() const;

		/*
		Elimina si returneaza elementul din varful stivei
		pre: stiva nu este vida
		post: elimina si returneaza elementul din varful stivei
		complexitate: Theta(1)
		*/
		TElem sterge();

		/*
		Verifica daca stiva este vida
		pre: true
		post: returneaza true iff stiva este vida
		complexitate: Theta(1)
		*/
		bool vida() const;
		
		/*
		Elibereaza memoria ocupata de stiva
		pre: true
		post: memoria ocupata de stiva este eliberata
		complexitate: Theta(n)
		*/
		~Stiva();
};
