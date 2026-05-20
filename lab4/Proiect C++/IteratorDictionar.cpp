#include "IteratorDictionar.h"
#include "Dictionar.h"
#include <exception>

using namespace std;

IteratorDictionar::IteratorDictionar(const Dictionar &d) : dict(d) {
    current = dict.first;
}

void IteratorDictionar::prim() { current = dict.first; }

void IteratorDictionar::urmator() {
    if (!valid()) {
        throw exception();
    }
    current = current->nextList;
}

TElem IteratorDictionar::element() const {
    if (!valid()) {
        throw exception();
    }
    return current->element;
}

bool IteratorDictionar::valid() const { return current != nullptr; }
