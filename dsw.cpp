#include "dsw.h"

// -------------------------------PRIVATE-------------------------------------

void BST::rotateRight(Node2*& node)
{
    if (node == nullptr || node->left == nullptr)
        return;

    Node2* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;

    node = leftChild;
}

void BST::rotateLeft(Node2*& node)
{
    if (node == nullptr || node->right == nullptr)
        return;

    Node2* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;

    node = rightChild;
}

void BST::createVine()
{
    if (root == nullptr)
        return;

    Node2* grandparent = nullptr;
    Node2* parent = root;
    Node2* child = root->left;

    while (parent != nullptr)
    {
        if (child != nullptr)
        {
            rotateRight(parent);
            if (grandparent == nullptr)
                root = parent;
            else
                grandparent->right = parent;
            child = parent->left;
        }
        else
        {
            grandparent = parent;
            parent = parent->right;
            if (parent != nullptr)
                child = parent->left;
        }
    }
}

void BST::rebuildTree(int size)
{
    int highestPowerof2 = (int)pow(2, floor(log2(size + 1)));
    int m = (size + 1) - highestPowerof2;

    performRotations(m);

    for (size = (size - m) / 2; size > 0; size /= 2)
        performRotations(size);
}

void BST::performRotations(int count)
{
    Node2* grandparent = nullptr;
    Node2* parent = root;
    Node2* child = (parent != nullptr) ? parent->right : nullptr;

    for (int i = 0; i < count; i++)
    {
        if (child == nullptr)
            break;

        rotateLeft(parent);

        if (grandparent == nullptr)
            root = parent;
        else
            grandparent->right = parent;

        // After rotation, parent is now what child was.
        grandparent = parent;
        parent = parent->right;
        if (parent != nullptr)
            child = parent->right;
        else
            child = nullptr;
    }
}


void BST::printTree(Node2* root, int space)
{
    if (root == nullptr)
        return;

    space += 5;

    printTree(root->right, space);

    for (int i = 5; i < space; i++)
        cout << " ";
    cout << root->key << " : " << root->value << endl;

    printTree(root->left, space);
}

void BST::findHigher(Node2* node, int score, vector<Node2*>& result)
{
    if (node == nullptr)
        return;

    if (node->key > score)
    {
        result.push_back(node);
        findHigher(node->left, score, result); 
        findHigher(node->right, score, result);
    }
    else
    {
        findHigher(node->right, score, result);
    }
}

void BST::findLower(Node2* node, int score, vector<Node2*>& result)
{
    if (node == nullptr)
        return;

    if (node->key < score)
    {
        result.push_back(node);
        findLower(node->left, score, result);
        findLower(node->right, score, result);
    }
    else
    {
        findLower(node->left, score, result);  
    }
}

// -------------------------- PUBLIC ----------------------------------

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    deleteTree(root);
}

void BST::deleteTree(Node2*& node)
{
    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void BST::insert(int key, const string& value)
{
    insert(root, key, value);
}

void BST::insert(Node2*& node, int key, const string& value)
{
    if (node == nullptr)
    {
        node = new Node2(key, value);
        return;
    }

    if (key < node->key)
        insert(node->left, key, value);
    else
        insert(node->right, key, value);
}

void BST::dswBalance()
{
    if (root == nullptr)
        return;

    createVine();
    //display(); // You can comment this if you don't want intermediate output

    int size = 0;
    Node2* temp = root;
    while (temp != nullptr)
    {
        size++;
        temp = temp->right;
    }

    rebuildTree(size);
}

void BST::display()
{
    cout << endl;
    printTree(root, 0);
    cout << endl;
}

void BST::findHigher(int score)
{
    vector<Node2*> result;
    findHigher(root, score, result);
    
    if (result.empty())
    {
        cout << "No files with scores higher than " << score << "." << endl << endl;
    }
    else
    {
        cout << "Files with scores higher than " << score << ":\n";
        for (auto node : result)
            cout << node->key << " : " << node->value << endl;
    }
    cout << endl;
}

void BST::findLower(int score)
{
    vector<Node2*> result;
    findLower(root, score, result);
    if (result.empty())
    {
        cout << "No files with scores lower than " << score << "." << endl << endl;
    }
    else
    {
        cout << "Files with scores lower than " << score << ":\n";
        for (auto node : result)
            cout << node->key << " : " << node->value << endl;
    }
    cout << endl;
}