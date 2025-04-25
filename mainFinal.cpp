#include "final.h"

int main() {
    vector<string> files = {"BeaverChefs.txt", "DogWizards.txt", "EvilCats.txt", "EvilFox.txt", "ForestOwl.txt", "FutureRabbit.txt", "GnomeNecromancy.txt", "LionRoar.txt", "MarsUprising.txt", "MonkeyBusiness.txt", "StormTurtle.txt", "TortoiseandHare.txt"};
    HashTable myTable(653); 

    Final a; 

    a.loadWordsIntoHashTable(files, myTable);

    myTable.printTable();

    vector<set<string>> documents = {"BeaverChefs.txt", "DogWizards.txt", "EvilCats.txt", "EvilFox.txt", "ForestOwl.txt", "FutureRabbit.txt", "GnomeNecromancy.txt", "LionRoar.txt", "MarsUprising.txt", "MonkeyBusiness.txt", "StormTurtle.txt", "TortoiseandHare.txt"};

    // Compare all documents and calculate the scores
    vector<int> scores = compareDocuments(documents);

    // Print the scores for each document
    for (int i = 0; i < scores.size(); i++) {
        cout << "Document " << i + 1 << " score: " << scores[i] << endl;
    }
}