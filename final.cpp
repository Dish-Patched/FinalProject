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
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            continue;
        }

        string line, word;
        set<string> uniqueWordsInFile;

        while (getline(file, line)) {
            stringstream ss(line);
            while (ss >> word) {
                word = cleanWord(word);
                if (!word.empty() && uniqueWordsInFile.find(word) == uniqueWordsInFile.end()) {
                    uniqueWordsInFile.insert(word);

                    string currentValue;
                    if (table.search(word, currentValue)) {
                        // Avoid duplicating filename
                        if (currentValue.find(filename) == string::npos) {
                            currentValue += "," + filename;
                            table.insert(word, currentValue);
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
