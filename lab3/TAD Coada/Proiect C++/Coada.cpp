#include "Coada.h"

Coada::Coada()
{
    capacitate = 10;
    noduri = new Nod[capacitate];

    prim = -1;
    ultim = -1;

    for (int i = 0; i < capacitate - 1; i++) {
        noduri[i].urmator = i + 1;
        noduri[i].anterior = -1;
    }

    noduri[capacitate - 1].urmator = -1;
    noduri[capacitate - 1].anterior = -1;

    primLiber = 0;
}

int Coada::aloca()
{
    if (primLiber == -1) {
        resize();
    }

    int poz = primLiber;
    primLiber = noduri[primLiber].urmator;

    return poz;
}

void Coada::dealoca(int poz)
{
    noduri[poz].urmator = primLiber;
    noduri[poz].anterior = -1;
    primLiber = poz;
}

void Coada::resize()
{
    int capacitateVeche = capacitate;
    capacitate *= 2;

    Nod* noduriNoi = new Nod[capacitate];

    for (int i = 0; i < capacitateVeche; i++) {
        noduriNoi[i] = noduri[i];
    }

    delete[] noduri;
    noduri = noduriNoi;

    for (int i = capacitateVeche; i < capacitate - 1; i++) {
        noduri[i].urmator = i + 1;
        noduri[i].anterior = -1;
    }

    noduri[capacitate - 1].urmator = -1;
    noduri[capacitate - 1].anterior = -1;

    primLiber = capacitateVeche;
}

void Coada::adauga(TElem elem)
{
    int poz = aloca();

    noduri[poz].element = elem;
    noduri[poz].anterior = ultim;
    noduri[poz].urmator = -1;

    if (vida()) {
        prim = poz;
        ultim = poz;
        return;
    }

    noduri[ultim].urmator = poz;
    ultim = poz;
}

TElem Coada::element() const
{
    if (vida()) {
        throw std::exception();
    }

    return noduri[prim].element;
}

TElem Coada::sterge()
{
    if (vida()) {
        throw std::exception();
    }

    int pozSters = prim;
    TElem valoare = noduri[pozSters].element;

    prim = noduri[prim].urmator;

    if (prim != -1) {
        noduri[prim].anterior = -1;
    } else {
        ultim = -1;
    }

    dealoca(pozSters);

    return valoare;
}

bool Coada::vida() const
{
    return prim == -1;
}

Coada::~Coada()
{
    delete[] noduri;
}