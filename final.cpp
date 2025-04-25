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

int calculateScore(const set<string>& doc1Words, const set<string>& doc2Words) {
    // Intersection: Common words
    set<string> commonWords;
    for (const string& word : doc1Words) {
        if (doc2Words.find(word) != doc2Words.end()) {
            commonWords.insert(word);
        }
    }

    // Union: Unique words
    set<string> uniqueWords = doc1Words;
    for (const string& word : doc2Words) {
        uniqueWords.insert(word);
    }

    // Score is calculated as: number of unique words - number of common words
    int score = uniqueWords.size() - commonWords.size();
    return score;
}

// Function to compare all documents and calculate the accumulated score
vector<int> compareDocuments(const vector<set<string>>& documents) {
    int n = documents.size();
    vector<int> scores(n, 0);

    // Compare each document with every other document
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Calculate score between document i and document j
            int score = calculateScore(documents[i], documents[j]);

            // Add score to both documents (since it's a pairwise comparison)
            scores[i] += score;
            scores[j] += score;
        }
    }

    return scores;
}
