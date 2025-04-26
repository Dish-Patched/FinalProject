#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

#include <iostream>
#include <iomanip>
#include <climits>

using namespace std;

struct binomialNode
{
    int key;
    string value;
    int degree;
    binomialNode* sibling;
    binomialNode* child;
    binomialNode* parent;

    binomialNode(int k, string v);
};

class BinomialHeap
{
    private:
        binomialNode* head;

        binomialNode* unionHeap(binomialNode* heap1, binomialNode* heap2);
        binomialNode* mergeTrees(binomialNode* tree1, binomialNode* tree2);
        void linkTrees(binomialNode*& prev, binomialNode*& cur, binomialNode*& next);

    public:
        BinomialHeap();

        void insert(int key, string value);
        void merge(BinomialHeap& other);
        int findMin();
        binomialNode* findMin(binomialNode*& minPrevOut);

        void deleteMin();
        void deleteKey(int key);
        void decreaseKey(int oldKey, int newKey);
        binomialNode* findNode(binomialNode* node, int key);

        void printHeap();
        void printTree(binomialNode* node, int space);
};

#endif