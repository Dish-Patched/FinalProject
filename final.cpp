#include "final.h"

Final::Final() 
{ 
    
}

string Final::cleanWord(const string& word) {
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
        set<string> wordsInFile;

        while (getline(file, line)) {
            stringstream ss(line);
            while (ss >> word) {
                word = cleanWord(word);

                if (!word.empty() && wordsInFile.find(word) == wordsInFile.end()) {
                    wordsInFile.insert(word);

                    string filesContainingWord;
                    if (table.search(word, filesContainingWord)) {
                        // Only add filename if not already present
                        if (filesContainingWord.find(filename) == string::npos) {
                            filesContainingWord += "," + filename;
                            table.insert(word, filesContainingWord);
                        }
                    } else {
                        table.insert(word, filename);
                    }
                }
            }
        }

        file.close();
    }
}
