#include "final.h"

int main() {
    vector<string> files = {
        "BeaverChefs.txt", "DogWizards.txt", "EvilCats.txt", "EvilFox.txt",
        "ForestOwl.txt", "FutureRabbit.txt", "GnomeNecromancy.txt", "LionRoar.txt",
        "MarsUprising.txt", "MonkeyBusiness.txt", "StormTurtle.txt", "TortoiseandHare.txt"
    };

    HashTable myTable(653);
    Final a;
    BST plagiarismTree;

    a.loadWordsIntoHashTable(files, myTable);

    set<string> inputWords = a.readWordsFromFile("testfile.txt");

    //cout << "\nSimilarity Scores (lower = more similar):\n";
    for (const string& doc : files) {
        set<string> docWords = a.readWordsFromFile(doc);
        int score = a.calculateScore(inputWords, docWords);
        //cout << doc << ": " << score << endl;
        plagiarismTree.insert(score, doc);
    }

    // Balance the tree after all insertions
    plagiarismTree.dswBalance();

    // Display the balanced tree
    cout << "\nFinal Balanced Tree (Score : Filename):" << endl;
    plagiarismTree.display();

    return 0;
}
