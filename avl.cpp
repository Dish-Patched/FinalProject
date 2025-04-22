//================ PRIVATE ================//

void AVLTree::destroyTree(Node* node)
{
    if(node)    //if node exists
    {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

int AVLTree::height(Node* node)
{
    if(node)
        return node->height;
    else
        return -1;  //maintaining balance factor
}

int AVLTree::balanceFactor(Node* node) //change here if need
{
    if(node)
        return height(node->left) - height(node->right);
    else
        return 0;
}

Node* AVLTree::rotateRight(Node* y)
{
    if (y == nullptr || y->left == nullptr)
        return y;

    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* AVLTree::rotateLeft(Node* y)
{
    if (y == nullptr || y->right == nullptr)
        return y;

    Node* x = y->right;
    Node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

void AVLTree::printTree(Node* root, int space) {
    const int COUNT = 10;

    if (root == nullptr) {
        return;
    }

    space += COUNT;

    // Print the right child first
    printTree(root->right, space);

    // Print current node
    for (int i = COUNT; i < space; i++) {
        cout << " ";
    }
    cout << root->key << endl;

    // Print left child
    printTree(root->left, space);
}

Node* AVLTree::insert(Node* node, int key)
{
    // Perform the normal BST insertion
    if (node == nullptr) 
        return new Node(key); 

    if (key < node->key) 
        node->left = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
    else
        return 1;
        //throw MyException("Duplicate value found");

    //Perform rotations
    node->height = 1 + max(height(node->left), height(node->right)); 
   
    int balance = balanceFactor(node); 

    // Left Left Case 
    if (balance > 1 && key < node->left->key) 
        return rotateRight(node); 

    // Right Right Case 
    if (balance < -1 && key > node->right->key) 
        return rotateLeft(node); 

    // Left Right Case 
    if (balance > 1 && key > node->left->key) { 
        node->left = rotateLeft(node->left); 
        return rotateRight(node); 
    } 

    // Right Left Case 
    if (balance < -1 && key < node->right->key) { 
        node->right = rotateRight(node->right); 
        return rotateLeft(node); 
    } 

    // Return the (unchanged) node pointer 
    return node; 
}

Node* AVLTree::minValueNode(Node* node)
{
    Node* current = node;
    //Find smallest node
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* AVLTree::remove(Node* node, int key)
{
    if (node == nullptr)
        return 1;
    //throw MyException("Error, key not found");

    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    else
    {
        // Node found
        if ((node->left == nullptr) || (node->right == nullptr))
        {
            Node *temp = node->left ? node->left : node->right;

            if (temp == nullptr) // No child case
            {
                temp = node;
                node = nullptr;
            }
            else // One child case
                *node = *temp;  
            delete temp;
        }
        else // Two children case
        {
            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
    }

    // If the tree had only one node, return
    if (node == nullptr)
        return node;

    // Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Balance the tree
    int balance = balanceFactor(node);

    // Left Left Case
    if (balance > 1 && balanceFactor(node->left) >= 0)
        return rotateRight(node);

    // Left Right Case
    if (balance > 1 && balanceFactor(node->left) < 0)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && balanceFactor(node->right) <= 0)
        return rotateLeft(node);

    // Right Left Case
    if (balance < -1 && balanceFactor(node->right) > 0)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

//============== PUBIC ==================//
AVLTree::AVLTree()
{
    root = nullptr;
}

AVLTree::~AVLTree()
{
    destroyTree(root);
    root = nullptr;
}

void AVLTree::display()
{
    cout << endl;
    printTree(root, 0);
    cout << endl;
}

void AVLTree::insert(int key)
{
    root = insert(root, key);
}

void AVLTree::remove(int key)
{
    root = remove(root, key);
}
