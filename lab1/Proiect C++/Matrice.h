#pragma once

typedef int TElem;

#define NULL_TELEMENT 0

class Matrice
{

private:
	int rows, cols, n, capacity; /// rows - nr de linii, cols - nr de coloane, n - nr de elemente din val_elem, capacity - size ul lui val_elem
	int *v;						 /// capacity ul pe linii, v[i+1]-v[i] = nr de elemente de pe linia i, unde i ap 0..n
	int *col_elem;				 /// coloanele unde am elemente
	TElem *val_elem;			 /// retin valorile

	void inside(int i, int j) const;
	void resize();
	int binary_search(int row, int col, bool &yeet) const;

public:
	// constructor
	// se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);

	// destructor
	~Matrice();

	// returnare element de pe o linie si o coloana
	// se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	// indicii se considera incepand de la 0
	TElem element(int i, int j) const;

	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;

	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem);
};