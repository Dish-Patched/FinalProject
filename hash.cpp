#include "hash.h"

HashTable::HashTable(int size) {
    tableSize = size;
    elementCount = 0;
    tableBST.resize(size);
}

HashTable::~HashTable() {}

int HashTable::hash1(const string& key) const {
    unsigned long hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c);
    }
    return hash % tableSize;
}

void HashTable::insert(const string& key, const string& value) {
    resizeIfNeeded();
    int index = hash1(key);
    tableBST[index].insert(key, value);
    elementCount++;        
}

bool HashTable::search(const string& key, string& value) {
    int index = hash1(key);
    return tableBST[index].search(key, value);
}

bool HashTable::remove(const string& key) {
    int index = hash1(key);
    if (tableBST[index].remove(key)) {
        elementCount--;
        return true;
    }
    return false;
}

void HashTable::printTable() {
    for (int i = 0; i < tableSize; ++i) {
        vector<pair<string, string>> elements = tableBST[i].inOrderTraversal();
        if (!elements.empty()) {
            cout << "Bucket [" << i << "]: ";
            for (const auto& pair : elements) {
                cout << "(" << pair.first << ", " << pair.second << ") ";
            }
            cout << endl;
        }
    }
}

// Resize if load factor exceeds threshold
void HashTable::resizeIfNeeded() {
    double loadFactor = elementCount/tableSize;
    if (loadFactor > 0.75) {
        rehash();
    }
}

// Double table size and rehash all elements
void HashTable::rehash() {
    cout << "HERE" << endl;
    int newSize = tableSize * 2;
    vector<pair<string, string>> oldElements;

    for (const auto& tree : tableBST) {
        vector<pair<string, string>> elements = tree.inOrderTraversal();
        oldElements.insert(oldElements.end(), elements.begin(), elements.end());
    }

    tableSize = newSize;
    tableBST.clear();
    tableBST.resize(newSize);
    //elementCount = 0;

    for (const auto& pair : oldElements) {
        insert(pair.first, pair.second);
    }

    cout << "Table resized to " << tableSize << " slots." << endl;
}
