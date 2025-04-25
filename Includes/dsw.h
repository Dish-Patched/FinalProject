#ifndef DSW_H
#define DSW_H

#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

struct Node2
{
    int key; // Numerical score
    string value; // Filename
    Node2* left;
    Node2* right;

    Node2(int k, const string& val)
    {
        key = k;
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST
{
private:
    Node2* root;

    void rotateRight(Node2*& node);
    void rotateLeft(Node2*& node);
    void createVine();   
    void rebuildTree(int size);   
    void performRotations(int count);   
    void printTree(Node2* root, int space);
    void insert(Node2*& node, int key, const string& value);

public:
    BST();
    ~BST();
    void deleteTree(Node2*& root);

    void insert(int key, const string& value);
    void dswBalance();
    void display();
};

#endif
