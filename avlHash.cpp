#include "avlHash.h"

AVLHashTree::AVLHashTree() {
    root = nullptr;
}

AVLHashTree::~AVLHashTree() {
    destroyTree(root);
}

void AVLHashTree::destroyTree(Node* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

int AVLHashTree::height(Node* node) {
    if (node)
        return node->height;
    else
        return -1;
}

int AVLHashTree::getBalanceFactor(Node* node) {
    if (node)
        return height(node->left) - height(node->right);
    else
        return 0;
}

Node* AVLHashTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* AVLHashTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* AVLHashTree::insert(Node* node, const pair<string, string>& data) {
    if (!node) return new Node(data);

    if (data.first < node->data.first)
        node->left = insert(node->left, data);
    else if (data.first > node->data.first)
        node->right = insert(node->right, data);
    else {
        node->data.second = data.second; // Update value if key already exists
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalanceFactor(node);

    if (balance > 1 && data.first < node->left->data.first)
        return rotateRight(node);

    if (balance > 1 && data.first > node->left->data.first) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && data.first > node->right->data.first)
        return rotateLeft(node);

    if (balance < -1 && data.first < node->right->data.first) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLHashTree::insert(const string& key, const string& value) {
    root = insert(root, {key, value});
}

Node* AVLHashTree::minValueNode(Node* node) {
    Node* current = node;
    while (current->left)
        current = current->left;
    return current;
}

Node* AVLHashTree::remove(Node* node, const string& key) {
    if (!node) return node;

    if (key < node->data.first)
        node->left = remove(node->left, key);
    else if (key > node->data.first)
        node->right = remove(node->right, key);
    else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        Node* temp = minValueNode(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data.first);
    }

    if (!node) return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalanceFactor(node);

    if (balance > 1 && getBalanceFactor(node->left) >= 0)
        return rotateRight(node);

    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && getBalanceFactor(node->right) <= 0)
        return rotateLeft(node);

    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

bool AVLHashTree::remove(const string& key) {
    string dummyValue; // Temporary variable to check if the key exists
    if (search(key, dummyValue)) {
        root = remove(root, key);
        return true;
    }
    return false;
}

Node* AVLHashTree::search(Node* node, const string& key, string& value) {
    if (!node) return nullptr;

    if (key == node->data.first) {
        value = node->data.second;
        return node;
    } else if (key < node->data.first) {
        return search(node->left, key, value);
    } else {
        return search(node->right, key, value);
    }
}

bool AVLHashTree::search(const string& key, string& value) {
    return search(root, key, value) != nullptr;
}

void AVLHashTree::printTree(Node* root, int space) {
    const int COUNT = 10;

    if (!root) return;

    space += COUNT;

    printTree(root->right, space);

    for (int i = COUNT; i < space; i++) {
        cout << " ";
    }
    cout << root->data.first << ": " << root->data.second << endl;

    printTree(root->left, space);
}

void AVLHashTree::print() {
    printTree(root, 0);
    cout << endl;
}

void AVLHashTree::inOrderTraversal(Node* node, vector<pair<string, string>>& result) const {
    if (!node) return;
    inOrderTraversal(node->left, result);
    result.push_back(node->data);
    inOrderTraversal(node->right, result);
}

vector<pair<string, string>> AVLHashTree::inOrderTraversal() const {
    vector<pair<string, string>> result;
    inOrderTraversal(root, result);
    return result;
}