#include "final.h"

int main() {
    vector<string> files = {"BeaverChefs.txt", "DogWizards.txt", "EvilCats.txt", "EvilFox.txt", "ForestOwl.txt", "FutureRabbit.txt", "GnomeNecromancy.txt", "LionRoar.txt", "MarsUprising.txt", "MonkeyBusiness.txt", "StormTurtle.txt", "TortoiseandHare.txt"};
<<<<<<< HEAD
    HashTable myTable(100); // or any other variant
=======
    HashTable myTable(653); 
>>>>>>> 7d46806ef6bcc370d068007f83912e0e6c081e36

    Final a; 

    a.loadWordsIntoHashTable(files, myTable);

    myTable.printTable();
}