#include "final.h"

int main() {
    vector<string> files = {"BeaverChefs.txt", "DogWizards.txt", "EvilCats.txt", "EvilFox.txt", "ForestOwl.txt", "FutureRabbit.txt", "GnomeNecromancy.txt", "LionRoar.txt", "MarsUprising.txt", "MonkeyBusiness.txt", "StormTurtle.txt", "TortoiseandHare.txt"};
    HashTable myTable(653); 

    Final a; 

    a.loadWordsIntoHashTable(files, myTable);

    myTable.printTable();

    set<string> inputWords = a.readWordsFromFile("testfile.txt");

    vector<string> existingDocs = files;

    cout << "\nSimilarity Scores (lower = more similar):\n";
    for (const string& doc : existingDocs) {
        set<string> docWords = a.readWordsFromFile(doc);
        int score = a.calculateScore(inputWords, docWords);
        cout << doc << ": " << score << endl;
    }
}