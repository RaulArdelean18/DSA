#include "Dictionar.h"
#include "IteratorDictionar.h"

NodDictionar::NodDictionar(TCheie c, TValoare v) {
    element = TElem(c, v);
    nextBucket = nullptr;
    prevList = nullptr;
    nextList = nullptr;
}

Dictionar::Dictionar() {
    capacity = 17;
    nr_elements = 0;
    first = nullptr;
    last = nullptr;
    tabel = new NodDictionar *[capacity];
    for (int i = 0; i < capacity; i++) {
        tabel[i] = nullptr;
    }
}

Dictionar::~Dictionar() {
    NodDictionar *current = first;
    while (current != nullptr) {
        NodDictionar *aux = current;
        current = current->nextList;
        delete aux;
    }
    delete[] tabel;
}

TValoare Dictionar::adauga(TCheie c, TValoare v) {
    int position = dispersie(c);
    NodDictionar *current = tabel[position];
    while (current != nullptr) {
        if (current->element.first == c) {
            TValoare valoareVeche = current->element.second;
            current->element.second = v;
            return valoareVeche;
        }
        current = current->nextBucket;
    }

    if ((nr_elements + 1) * 4 > capacity * 3) {
        redimensioneaza();
        position = dispersie(c);
    }

    NodDictionar *newNode = new NodDictionar(c, v);
    newNode->nextBucket = tabel[position];
    tabel[position] = newNode;

    if (first == nullptr) {
        first = newNode;
        last = newNode;
    } else {
        last->nextList = newNode;
        newNode->prevList = last;
        last = newNode;
    }

    nr_elements++;
    return NULL_TVALOARE;
}

TValoare Dictionar::cauta(TCheie c) const {
    int position = dispersie(c);
    NodDictionar *current = tabel[position];
    while (current != nullptr) {
        if (current->element.first == c) {
            return current->element.second;
        }
        current = current->nextBucket;
    }
    return NULL_TVALOARE;
}

TValoare Dictionar::sterge(TCheie c) {
    int position = dispersie(c);
    NodDictionar *current = tabel[position];
    NodDictionar *prevBucket = nullptr;

    while (current != nullptr && current->element.first != c) {
        prevBucket = current;
        current = current->nextBucket;
    }

    if (current == nullptr) {
        return NULL_TVALOARE;
    }

    if (prevBucket == nullptr) {
        tabel[position] = current->nextBucket;
    } else {
        prevBucket->nextBucket = current->nextBucket;
    }

    if (current->prevList == nullptr) {
        first = current->nextList;
    } else {
        current->prevList->nextList = current->nextList;
    }

    if (current->nextList == nullptr) {
        last = current->prevList;
    } else {
        current->nextList->prevList = current->prevList;
    }

    TValoare erasedValue = current->element.second;
    delete current;
    nr_elements--;
    return erasedValue;
}

int Dictionar::dispersie(TCheie c) const {
    int rest = c % capacity;
    if (rest < 0) {
        rest += capacity;
    }
    return rest;
}

void Dictionar::redimensioneaza() {
    int newCapacity = capacity * 2 + 1;
    NodDictionar **newTabel = new NodDictionar *[newCapacity];
    for (int i = 0; i < newCapacity; i++) {
        newTabel[i] = nullptr;
    }

    NodDictionar *current = first;
    while (current != nullptr) {
        int rest = current->element.first % newCapacity;
        if (rest < 0) {
            rest += newCapacity;
        }
        current->nextBucket = newTabel[rest];
        newTabel[rest] = current;
        current = current->nextList;
    }

    delete[] tabel;
    tabel = newTabel;
    capacity = newCapacity;
}

int Dictionar::dim() const { return nr_elements; }

bool Dictionar::vid() const { return nr_elements == 0; }

IteratorDictionar Dictionar::iterator() const {
    return IteratorDictionar(*this);
}
