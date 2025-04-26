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


    int user = 1;
    while(user != 0)
    {
        cout << "Actions menu: " << endl;
        cout << "1. View highest and lowest scores." <<endl;
        cout << "2. See tree of all scores." <<endl;
        cout << "3. See scores higher than..." <<endl;
        cout << "4. See scores lower than..." <<endl;
        cout << "0. To exit." << endl;
        cout << endl << "What would you like to do? ";

        cin >> user;

        int userin;

        if(user == 1){

        }
        else if(user == 2){
            cout << "\nFinal Balanced Tree (Score : Filename):" << endl;
            plagiarismTree.display();
        }
        else if(user == 3){
            cout << "Please enter a score to search: ";
            cin >> userin;
            plagiarismTree.findHigher(userin);
        }
        else if(user == 4){
            cout << "Please enter a score to search: ";
            cin >> userin;
            plagiarismTree.findLower(userin);
        }
        else if(user == 0){
            cout << "Exitting..." << endl;
            break;
        }
        else
            cout <<"Invalid input, please try again" << endl << endl;
    }

    return 0;
}
