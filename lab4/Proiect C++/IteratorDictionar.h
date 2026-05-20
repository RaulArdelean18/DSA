#pragma once
#include "Dictionar.h"

class IteratorDictionar {
    friend class Dictionar;

  private:
    /*
     * Creates an iterator for a dictionary and positions it at the first
     * element pre: The referenced dictionary exists post: The iterator
     * references the first element, or is invalid if the dictionary is empty
     * Time complexity: O(1)
     */
    IteratorDictionar(const Dictionar &d);

    // Stores a reference to the dictionary being iterated
    const Dictionar &dict;
    NodDictionar *current;

  public:
    /*
     * Resets the iterator to the first element of the dictionary
     * pre: The iterator is associated with a valid dictionary
     * post: The iterator references the first element, or is invalid if the
     * dictionary is empty Time complexity: O(1)
     */
    void prim();

    /*
     * Moves the iterator to the next element
     * pre: The iterator is valid
     * post: The iterator references the next element, or becomes invalid after
     * the last element Time complexity: O(1)
     */
    void urmator();

    /*
     * Checks whether the iterator currently references an element
     * pre: The iterator is associated with a valid dictionary
     * post: The iterator is not modified
     * Time complexity: O(1)
     */
    bool valid() const;

    /*
     * Returns the element currently referenced by the iterator
     * pre: The iterator is valid
     * post: The iterator is not modified
     * Time complexity: O(1)
     */
    TElem element() const;
};
