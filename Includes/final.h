#ifndef FINAL_H
#define FINAL_H

#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>
#include "hash.h"

using namespace std;

class Final
{
    public:
    string cleanWord(const string& word);
    void loadWordsIntoHashTable(const vector<string>& filenames, HashTable& table); 

    private:

};

#endif