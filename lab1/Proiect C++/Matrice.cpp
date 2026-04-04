#include "Matrice.h"

#include <exception>

using namespace std;

/**
 * O(1) time complexity
 * Verific daca pozitia (i,j) se afla in matrice
 * param i: int, linia pe care se afla pozitia in matrice
 * param j: int, coloana pe care se afla pozitia in matrice
 * return: throw exception, daca nu se afla, nothing altfel
 */
void Matrice::inside(int i, int j) const
{
	if (i < 0 or i >= rows or j < 0 or j >= cols)
		throw exception();
}

/**
 * O(n) time complexity, worst case = best case
 * Daca matricea ii prea mica, o maresc de 2 ori nr de elemente
 * no params
 * return nothing, only change the capacity of the col_elem and val_elem
 */
void Matrice::resize()
{
	capacity *= 2;

	int *new_col_elem = new int[capacity];
	TElem *new_val_elem = new TElem[capacity];

	for (int i = 0; i < n; i++)
	{
		new_col_elem[i] = col_elem[i];
		new_val_elem[i] = val_elem[i];
	}

	delete[] col_elem;
	delete[] val_elem;

	col_elem = new_col_elem;
	val_elem = new_val_elem;
}

/**
 * O(log(N)) time complexity, best case if in first op we find the value, worst case if we reach all op (log(N))
 * Cauta in linia row daca exista un element nenul pe coloana col.
 * 
 * param row: int, linia pe care cautam
 * param col: int, verificam daca avem un element nenul in col
 * 
 * Daca exista, return pozitia lui in vectorii interni;
 * Daca nu exista, return pozitia unde ar trebui inserat.
 */
int Matrice::binary_search(int row, int col, bool &yeet) const
{
	int l = v[row], r = v[row + 1] - 1;

	while (l <= r)
	{
		int mid = l + r >> 1;

		if (col_elem[mid] == col)
		{
			yeet = true;
			return mid;
		}

		if (col_elem[mid] < col)
			l = mid + 1;
		else
			r = mid - 1;
	}

	yeet = false;
	return l;
}
/**
 * O(n) time complexity, worst case = best case
 * Initializam valorile, respectiv vectorii
 * param NrLinii: nr de linii
 * param col: nr de coloane
 * return nothing
 */
Matrice::Matrice(int NrLinii, int col)
{
	if (NrLinii <= 0 or col <= 0)
		throw exception();

	rows = NrLinii;
	cols = col;
	this->n = 0;
	capacity = 1;

	v = new int[rows + 1];
	for (int i = 0; i <= rows; i++)
		v[i] = 0;

	col_elem = new int[capacity];
	val_elem = new TElem[capacity];
}

Matrice::~Matrice()
{
	delete[] v;
	delete[] col_elem;
	delete[] val_elem;
}

int Matrice::nrLinii() const
{
	return rows;
}

int Matrice::nrColoane() const
{
	return cols;
}

/**
 * O(1) time complexity, worst case = best case
 * Returneaza elementul aflat pe pozitia (i, j) din matrice.
 * param i: int, linia pe care se afla elementul target
 * param j: int, coloana pe care se afla elementul target
 * Daca pe acea pozitie nu exista un element nenul memorat, return NULL_TELEMENT, otherwise valoarea de pe pozitie
 */
TElem Matrice::element(int i, int j) const
{
	inside(i, j);

	bool yeet = false;
	int pos = binary_search(i, j, yeet);

	if (yeet)
		return val_elem[pos];

	return NULL_TELEMENT;
}

/** 
 * O(n) time complexity, worst case = best case
 * Modifica elementul de pe pozitia (i, j) cu valoarea e si returneaza valoarea veche.
 * Daca e este diferit de NULL_TELEMENT, elementul este inserat sau actualizat.
 * Dacă e == NULL_TELEMENT, elementul este sters din reprezentarea rara.
 */
TElem Matrice::modifica(int i, int j, TElem e)
{
	inside(i, j);

	bool gasit = false;
	int pos = binary_search(i, j, gasit);

	if (gasit)
	{
		TElem last_val = val_elem[pos];

		if (e == NULL_TELEMENT) /// stergem elementul
		{
			for (int k = pos; k < n - 1; k++)
			{
				col_elem[k] = col_elem[k + 1];
				val_elem[k] = val_elem[k + 1];
			}

			n--;
			for (int k = i + 1; k <= rows; k++)
				v[k]--;
		}
		else /// adaugam noul element
			val_elem[pos] = e;

		return last_val;
	}

	if (e == NULL_TELEMENT)
		return NULL_TELEMENT;

	if (n == capacity) /// dau resize, ca sa pot adauga noul elem
		resize();

	for (int k = n; k > pos; k--)
	{
		col_elem[k] = col_elem[k - 1];
		val_elem[k] = val_elem[k - 1];
	}

	col_elem[pos] = j;
	val_elem[pos] = e;
	n++;

	for (int k = i + 1; k <= rows; k++)
		v[k]++;

	return NULL_TELEMENT;
}
