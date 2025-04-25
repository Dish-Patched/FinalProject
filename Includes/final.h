#ifndef FINAL_H
#define FINAL_H

#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>
#include <set>
#include "hash.h"
#include "dsw.h"

using namespace std;

class Final
{
    public:
    Final();
    string cleanWord(const string& word);
    void loadWordsIntoHashTable(const vector<string>& filenames, HashTable& table); 
    set<string> readWordsFromFile(const string& filename);
    int calculateScore(const set<string>& inputWords, const set<string>& docWords);

    private:

};

#endif