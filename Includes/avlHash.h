#ifndef AVLHASHTREE_H
#define AVLHASHTREE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    pair<string, string> data;
    Node* left;
    Node* right;
    int height;

    Node(const pair<string, string>& val) {
        data = val;
        left = nullptr;
        right = nullptr;
        height = 0;
    }
};

class AVLHashTree {
public:
    AVLHashTree();
    ~AVLHashTree();

    void insert(const string& key, const string& value);
    bool remove(const string& key);
    bool search(const string& key, string& value);
    void print();

    void inOrderTraversal(Node* node, vector<pair<string, string>>& result) const;
    vector<pair<string, string>> inOrderTraversal() const;

private:
    Node* root;

    Node* insert(Node* node, const pair<string, string>& data);
    Node* remove(Node* node, const string& key);
    Node* minValueNode(Node* node);

    int height(Node* node);
    int getBalanceFactor(Node* node);

    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);

    Node* search(Node* node, const string& key, string& value);
    void printTree(Node* root, int space);
    void destroyTree(Node* node);
};

#endif