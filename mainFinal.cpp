#include "final.h"

int main() {
    vector<string> files = {"BeaverChefs.txt", "DogWizards.txt", "EvilCats.txt", "EvilFox.txt", "ForestOwl.txt", "FutureRabbit.txt", "GnomeNecromancy.txt", "LionRoar.txt", "MarsUprising.txt", "MonkeyBusiness.txt", "StormTurtle.txt", "TortoiseandHare.txt"};
    HashTable myTable(1000, CHAINING_BST); // or any other variant

    Final a; 

    a.loadWordsIntoHashTable(files, myTable);

    myTable.printTable();
}