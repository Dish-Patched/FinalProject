<<<<<<< HEAD
#ifndef FINAL_H
#define FINAL_H

#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>
#include <set>
#include "hash.h"
#include "uf.h"

using namespace std;

class Final
{
    public:
    Final();
    string cleanWord(const string& word);
    void loadWordsIntoHashTable(const vector<string>& filenames, HashTable& table); 

    private:

};

=======
#ifndef FINAL_H
#define FINAL_H

#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>
#include <set>
#include "hash.h"

using namespace std;

class Final
{
    public:
    Final();
    string cleanWord(const string& word);
    void loadWordsIntoHashTable(const vector<string>& filenames, HashTable& table); 

    private:

};

>>>>>>> 79e9dc17744bd243b20a71b22932f35ef3dd48b3
#endif