#include "final.h"

Final:: Final()
{

}

string Final::cleanWord(const string& word) {    // so fresh and so clean
    string cleaned;
    for (char c : word) {
        if (isalnum(c)) cleaned += tolower(c);
    }
    return cleaned;
}

void Final::loadWordsIntoHashTable(const vector<string>& filenames, HashTable& table) {
    for (const string& filename : filenames) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file: " << filename << endl;
            continue;
        }

        string line, word;
        while (getline(file, line)) {
            stringstream ss(line);
            while (ss >> word) {
                word = cleanWord(word); // Clean and normalize
                if (!word.empty()) {
                    int count = 0;
                    if (table.search(word, count)) {
                        table.insert(word, count + 1); // Update frequency
                    } else {
                        table.insert(word, 1); // First occurrence
                    }
                }
            }
        }

        file.close();
    }
}


