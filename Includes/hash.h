#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <vector>
#include <string>
#include "avlHash.h"

using namespace std;

class HashTable {
private:
    int tableSize;
    int elementCount;

    vector<AVLHashTree> tableBST;  // Only using BST for chaining

    int hash1(const string& key) const;
    void resizeIfNeeded();
    void rehash();

public:
    HashTable(int size);
    ~HashTable();

    void insert(const string& key, const string& value);
    bool search(const string& key, string& value);
    bool remove(const string& key);
    void printTable();  // Optional but useful for debugging
};

#endif
