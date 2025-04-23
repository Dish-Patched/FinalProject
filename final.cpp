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
        set<string> wordsInFile;  // To avoid inserting the same word multiple times for the same file

        while (getline(file, line)) {
            stringstream ss(line);
            while (ss >> word) {
                word = cleanWord(word);  // Clean and normalize the word
                if (!word.empty() && wordsInFile.find(word) == wordsInFile.end()) {
                    // If the word is not already processed for this file
                    wordsInFile.insert(word);

                    // Check if the word is already in the table
                    vector<string> filesContainingWord;
                    if (table.search(word, filesContainingWord)) {
                        // Word is found, just add the current file to its list
                        filesContainingWord.push_back(filename);
                        table.insert(word, filesContainingWord);  // Update the value (which is the list of files)
                    } else {
                        // Word not found, create a new entry with the filename
                        filesContainingWord.push_back(filename);
                        table.insert(word, filesContainingWord);
                    }
                }
            }
        }

        file.close();
    }
}