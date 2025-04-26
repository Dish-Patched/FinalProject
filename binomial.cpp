#include "binomial.h"

binomialNode::binomialNode(int k, string v)
{
    key = k;
    value = v;
    degree = 0;
    parent = nullptr;
    sibling = nullptr;
    child = nullptr;
}

// ---------------------- PRIVATE FUNCTIONS ------------------------------
binomialNode* BinomialHeap::unionHeap(binomialNode* heap1, binomialNode* heap2)
{
    if(!heap1)
        return heap2;
    if(!heap2)
        return heap1;

    binomialNode* newHead = nullptr;
    binomialNode** pos = &newHead;

    while(heap1 && heap2)
    {
        if(heap1->degree <= heap2->degree)
        {
            *pos = heap1;
            heap1 = heap1->sibling;
        } else {
            *pos = heap2;
            heap2 = heap2->sibling;
        }
        pos = &((*pos)->sibling);
    }

    // add remaining elements
    *pos = (heap1) ? heap1 : heap2;

    return newHead;
}

binomialNode* BinomialHeap::mergeTrees(binomialNode* tree1, binomialNode* tree2)
{
    if(tree1->key > tree2->key)
        swap(tree1, tree2);

    tree2->parent = tree1;
    tree2->sibling = tree1->child;
    tree1->child = tree2;
    tree1->degree++;

    return tree1;
}

void BinomialHeap::linkTrees(binomialNode*& prev, binomialNode*& cur, binomialNode*& next)
{
    if(cur->degree != next->degree || (next->sibling && next->sibling->degree == cur->degree))
    {
        prev = cur;
        cur = next;
    } else {
        if(cur->key <= next->key) {
            cur->sibling = next->sibling;
            mergeTrees(cur, next);
        } else {
            if(!prev)
                head = next;
            else
                prev->sibling = next;
            mergeTrees(next, cur);
            cur = next;
        }
    }
}

// ---------------- PUBLIC FUNCTIONS ------------------------------
BinomialHeap::BinomialHeap()
{
    head = nullptr;
    minNode = nullptr;
}

void BinomialHeap::insert(int key, string value)
{
    BinomialHeap tempHeap;
    tempHeap.head = new binomialNode(key, value);

    head = unionHeap(head, tempHeap.head);

    if (!minNode || key < minNode->key)
        minNode = tempHeap.head;

    if(!head || !head->sibling)
        return;
    
    binomialNode* prev = nullptr;
    binomialNode* cur = head;
    binomialNode* next = cur->sibling;

    while(next)
    {
        linkTrees(prev, cur, next);
        next = cur->sibling;
    }
}

void BinomialHeap::merge(BinomialHeap& other)
{
    head = unionHeap(head, other.head);
    other.head = nullptr;

    if(!head || !head->sibling)
        return;

    binomialNode* prev = nullptr;
    binomialNode* cur = head;
    binomialNode* next = cur->sibling;

    while(next)
    {
        linkTrees(prev, cur, next);
        next = cur->sibling;
    }

}

binomialNode* BinomialHeap::findMin(binomialNode*& minPrevOut)
{
    if (!minNode)
        return nullptr;
    return minNode;
}

int BinomialHeap::findMin()
{
    if (!minNode)
        return -1;
    return minNode->key;
}


void BinomialHeap::deleteMin() {
    if (!head)
        return; 

    binomialNode* minPrev = nullptr;
    binomialNode* delNode = findMin(minPrev);  

    if (minPrev) {
        minPrev->sibling = delNode->sibling;
    } else {
        head = delNode->sibling;
    }

    binomialNode* child = delNode->child;
    binomialNode* reversed = nullptr;

    while (child) {
        binomialNode* next = child->sibling;
        child->sibling = reversed;
        child->parent = nullptr;
        reversed = child;
        child = next;
    }

    BinomialHeap tempHeap;
    tempHeap.head = reversed;
    merge(tempHeap);

    delete delNode;

    if (!head) {
        minNode = nullptr;
    } else {
        minNode = head;
        binomialNode* temp = head->sibling;
        while (temp) {
            if (temp->key < minNode->key)
                minNode = temp;
            temp = temp->sibling;
        }
    }
}


void BinomialHeap::deleteKey(int key) {
        decreaseKey(key, INT_MIN);
        deleteMin();
}


binomialNode* BinomialHeap::findNode(binomialNode* node, int key) {
    if (!node) return nullptr;
    if (node->key == key) return node;

    binomialNode* found = findNode(node->child, key);
    if (found) return found;

    return findNode(node->sibling, key);
}


void BinomialHeap::decreaseKey(int oldKey, int newKey)
{
    if (newKey >= oldKey)
        return;

    binomialNode* target = findNode(head, oldKey);
    if (!target)
        return;

    target->key = newKey;
    while (target->parent && target->key < target->parent->key) {
        swap(target->key, target->parent->key);
        target = target->parent;
    }
}


void BinomialHeap::printHeap() {
    cout << "Binomial Heap:\n";
    binomialNode* current = head;


    while (current != nullptr) {
        cout << endl << "Tree of degree " << current->degree << endl;
        printTree(current, 0);
        current = current->sibling;
    }
}

void BinomialHeap::printTree(binomialNode* node, int space) 
{
    if (node == nullptr) 
        return;

    cout << setw(space * 2) << node->key << endl;

    binomialNode* child = node->child;
    while (child) {
        printTree(child, space + 3);
        child = child->sibling;
    }
}