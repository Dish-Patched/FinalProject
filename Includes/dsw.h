#ifndef DSW_H
#define DSW_H

#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

struct Node2
{
    pair<string, string> data;
    Node2* left;
    Node2* right;

    Node2(const string& key, const string& value)
    {
        data = make_pair(key, value);
        left = nullptr;
        right = nullptr;
    }
};

class BST
{
private:
    Node2* root;

    // helper functions
    void rotateRight(Node2*& node);
    void rotateLeft(Node2*& node);
    void createVine();   
    void rebuildTree(int size);   
    void performRotations(int count);   
    void printTree(Node2* root, int space);
    void insert(Node2*& node, const string& key, const string& value);

public:
    BST();
    ~BST();
    void deleteTree(Node2*& root);

    void insert(const string& key, const string& value);
    void dswBalance();
    void display();
};

#endif
