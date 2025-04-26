#include "final.h"

int main() {
    vector<string> files = {
        "BeaverChefs.txt", "DogWizards.txt", "EvilCats.txt",
        "EvilFox.txt", "ForestOwl.txt", "FutureRabbit.txt",
        "GnomeNecromancy.txt", "LionRoar.txt", "MarsUprising.txt",
        "MonkeyBusiness.txt", "StormTurtle.txt", "TortoiseandHare.txt"
    };

    string folder = "Documents/";

    HashTable myTable(653);
    Final a;
    BST plagiarismTree;
    BinomialHeap heap;

    vector<string> fullPaths;
    for (const string& f : files) {
        fullPaths.push_back(folder + f);
    }
    a.loadWordsIntoHashTable(fullPaths, myTable);

    set<string> inputWords = a.readWordsFromFile(folder + "testfile.txt");

    for (const string& doc : files) {
        set<string> docWords = a.readWordsFromFile(folder + doc);
        int score = a.calculateScore(inputWords, docWords);
        plagiarismTree.insert(score, doc);
        heap.insert(score, doc);
    }

    plagiarismTree.dswBalance();

    int user = 1;
    while (user != 0) {
        cout << "Actions menu: " << endl;
        cout << "Lower scores = More similar. Higher scores = Less similar" << endl;
        cout << "1. View highest and lowest scores." << endl;
        cout << "2. See tree of all scores." << endl;
        cout << "3. See scores higher than..." << endl;
        cout << "4. See scores lower than..." << endl;
        cout << "0. To exit." << endl;
        cout << endl << "What would you like to do? ";

        cin >> user;

        int userin;

        if (user == 1) {
            plagiarismTree.printMax();
            
            binomialNode* dummyPrev = nullptr;
            binomialNode* minNode = heap.findMin(dummyPrev);

            if (minNode) {
                cout << "Lowest score : " << minNode->key << " "
                    << minNode->value << endl << endl;
            } else {
                cout << "Heap is empty!" << endl << endl;
            }
        }
        else if (user == 2) {
            cout << "\nFinal Balanced Tree (Score : Filename):" << endl;
            plagiarismTree.display();
        }
        else if (user == 3) {
            cout << "Please enter a score to search: ";
            cin >> userin;
            plagiarismTree.findHigher(userin);
        }
        else if (user == 4) {
            cout << "Please enter a score to search: ";
            cin >> userin;
            plagiarismTree.findLower(userin);
        }
        else if (user == 0) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid input, please try again" << endl << endl;
        }
    }

    return 0;
}
