#include "dsw.h"

// -------------------------------PRIVATE-------------------------------------

void BST::rotateRight(Node2*& node)
{
    if(node == nullptr || node->left == nullptr)
        return;

    Node2* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;

    node = leftChild;
}

void BST::rotateLeft(Node2*& node)
{
    if(node == nullptr || node->right == nullptr)
        return;

    Node2* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;

    node = rightChild;
}

void BST::createVine()
{
    if(root == nullptr)
        return;

    Node2* grandparent = nullptr;
    Node2* parent = root;
    Node2* child = root->left;

    while(parent != nullptr)
    {
        if(child != nullptr)
        {
            rotateRight(parent);
            if(grandparent == nullptr)
                root = parent;
            else
                grandparent->right = parent;
            child = parent->left;
        }
        else
        {
            grandparent = parent;
            parent = parent->right;
            if(parent != nullptr)
                child = parent->left;
        }
    }
}

void BST::rebuildTree(int size)
{
    int highestPowerof2 = (int)pow(2, floor(log2(size + 1)));
    int m = (size + 1) - highestPowerof2;

    performRotations(m);

    for(size = (size - m) / 2; size > 0; size /= 2)
        performRotations(size);
}

void BST::performRotations(int count)
{
    Node2* grandparent = nullptr;
    Node2* parent = root;
    Node2* child = root->right;

    for(int i = 0; i < count; i++)
    {
        if(child == nullptr)
            break;

        rotateLeft(parent);
        if(grandparent == nullptr)
            root = parent;
        else
            grandparent->right = parent;

        grandparent = parent;
        parent = parent->right;
        if(parent != nullptr)
            child = parent->left;
    }
}

void BST::printTree(Node2* root, int space)
{
    if(root == nullptr)
        return;

    space += 5;

    printTree(root->right, space);

    for(int i = 5; i < space; i++)
        cout << " ";
    cout << root->data.first << " : " << root->data.second << endl;

    printTree(root->left, space);
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
    if(node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void BST::insert(const string& key, const string& value)
{
    insert(root, key, value);
}

void BST::insert(Node2*& node, const string& key, const string& value)
{
    if(node == nullptr)
    {
        node = new Node2(key, value);
        return;
    }

    if(key < node->data.first)
        insert(node->left, key, value);
    else
        insert(node->right, key, value);
}

void BST::dswBalance()
{
    if(root == nullptr)
        return;

    createVine();

    cout << "After Phase 1: ";
    display();

    int size = 0;
    Node2* temp = root;
    while(temp != nullptr)
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
