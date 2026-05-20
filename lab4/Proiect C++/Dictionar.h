#pragma once

#define NULL_TVALOARE -1
typedef int TCheie;
typedef int TValoare;

class IteratorDictionar;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

struct NodDictionar {
    TElem element;
    NodDictionar *nextBucket; /// next node in table[i] linked list
    /// global list iterators
    NodDictionar *prevList;
    NodDictionar *nextList;

    /**
     * Creates a dictionary node with the given key and value
     * pre: The key and value are valid TCheie and TValoare values
     * post: The node stores the pair (c, v), and all links are null
     * Time complexity: Theta(1)
     */
    NodDictionar(TCheie c, TValoare v);
};

class Dictionar {
    friend class IteratorDictionar;

  private:
    /// hash table
    NodDictionar **tabel;
    int capacity;
    int nr_elements;
    NodDictionar *first;
    NodDictionar *last;

    /*
     * Computes the hash table position for a key
     * pre: The dictionary capacity is positive
     * post: Returns a valid index from the hash table
     * Time complexity: Theta(1)
     */
    int dispersie(TCheie c) const;

    /*
     * Increases the hash table capacity and redistributes all nodes
     * pre: The dictionary is correctly initialized
     * post: All elements remain in the dictionary, and the capacity is
     * increased Time complexity: O(n), where n is the number of elements
     */
    void redimensioneaza();

  public:
    /*
     * Creates an empty dictionary
     * pre: None
     * post: The dictionary is empty and ready to store pairs
     * Time complexity: O(1)
     */
    Dictionar();

    /*
     * Adds a key-value pair or updates the value of an existing
     * pre: The dictionary is correctly initialized
     * post: The key is associated with value v; returns the old value if the
     * key existed, otherwise NULL_TVALOARE
     * Time complexity: Best/Average O(1),Worst O(n)
     */
    TValoare adauga(TCheie c, TValoare v);

    /*
     * Searches for the value associated with a key
     * pre: The dictionary is correctly initialized
     * post: Returns the associated value if the key exists, otherwise
     * NULL_TVALOARE Time complexity: Best/Average O(1), Worst O(n)
     */
    TValoare cauta(TCheie c) const;

    /*
     * Removes the pair with the given key from the dictionary
     * pre: The dictionary is correctly initialized
     * post: The key is no longer stored; returns its old value if it existed,
     * otherwise NULL_TVALOARE Time complexity: Best/Average O(1), Worst O(n)
     */
    TValoare sterge(TCheie c);

    /*
     * Returns the number of key-value pairs in the dictionary
     * pre: The dictionary is correctly initialized
     * post: The dictionary is not modified
     * Time complexity: O(1)
     */
    int dim() const;

    /*
     * Checks whether the dictionary is empty
     * pre: The dictionary is correctly initialized
     * post: The dictionary is not modified
     * Time complexity: O(1)
     */
    bool vid() const;

    /*
     * Creates an iterator positioned at the first element of the dictionary
     * pre: The dictionary is correctly initialized
     * post: Returns an iterator for this dictionary; the dictionary is not
     * modified Time complexity: O(1)
     */
    IteratorDictionar iterator() const;

    /*
     * Destroys the dictionary and releases its allocated memory
     * pre: The dictionary was correctly initialized
     * post: All nodes and the hash table are deallocated
     * Time complexity: O(n), where n is the number of elements
     */
    ~Dictionar();
};
