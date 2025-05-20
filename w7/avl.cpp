#include <iostream>
#include <cmath>

using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
    int height; 
};

NODE* createNode(int data);
void Insert(NODE* &pRoot, int x);
void Remove(NODE* &pRoot, int x);
bool isAVL(NODE* pRoot);

int getHeight(NODE* p) {
    if (p == nullptr) {
        return -1; 
    }
    return p->height;
}

void updateHeight(NODE* p) {
    if (p) { // Only update if node exists
        p->height = 1 + max(getHeight(p->p_left), getHeight(p->p_right));
    }
}

int getBalance(NODE* p) {
    if (p == nullptr) {
        return 0;
    }
    return getHeight(p->p_left) - getHeight(p->p_right);
}

NODE* rotateRight(NODE* y) {
    NODE* x = y->p_left;
    NODE* T2 = x->p_right;

    x->p_right = y;
    y->p_left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

NODE* rotateLeft(NODE* x) {
    NODE* y = x->p_right;
    NODE* T2 = y->p_left;

    y->p_left = x;
    x->p_right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

NODE* balance(NODE* p) {
    if (!p) return p;

    updateHeight(p);
    int balanceFactor = getBalance(p);

    if (balanceFactor > 1) {
        if (getBalance(p->p_left) < 0) {
            p->p_left = rotateLeft(p->p_left);
        }
        return rotateRight(p);
    }

    if (balanceFactor < -1) {
        if (getBalance(p->p_right) > 0) {
            p->p_right = rotateRight(p->p_right);
        }
        return rotateLeft(p);
    }

    return p;
}


NODE* createNode(int data) {
    NODE* p = new NODE;
    p->key = data;
    p->p_left = nullptr;
    p->p_right = nullptr;
    p->height = 0;
    return p;
}

void Insert(NODE* &pRoot, int x) { 
    if (pRoot == nullptr) {
        pRoot = createNode(x);
        return;
    }

    if (x < pRoot->key) {
        Insert(pRoot->p_left, x);
    } else if (x > pRoot->key) {
        Insert(pRoot->p_right, x);
    } else {
        return;
    }

    pRoot = balance(pRoot); 
}

NODE* findMinAVL(NODE* pNode) {
    while (pNode && pNode->p_left != nullptr) {
        pNode = pNode->p_left;
    }
    return pNode;
}


void Remove(NODE* &pRoot, int x) { 
    if (pRoot == nullptr) {
        return; 
    }

    if (x < pRoot->key) {
        Remove(pRoot->p_left, x);
    } else if (x > pRoot->key) {
        Remove(pRoot->p_right, x);
    } else {
        if (pRoot->p_left == nullptr || pRoot->p_right == nullptr) {
            NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            if (temp == nullptr) {
                delete pRoot;
                pRoot = nullptr;
            } else { 
                NODE* nodeToDel = pRoot;
                pRoot = temp;
                delete nodeToDel;
            }
        } else {
            // Case 2: Node with two children
            NODE* temp = findMinAVL(pRoot->p_right); 
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key); 
        }
    }

    if (pRoot == nullptr) {
        return;
    }
    
    pRoot = balance(pRoot);
}

bool isBSTProperty(NODE* pNode, int min_val, int max_val) {
    if (pNode == nullptr) {
        return true;
    }
    if (pNode->key <= min_val || pNode->key >= max_val) {
        return false;
    }
    return isBSTProperty(pNode->p_left, min_val, pNode->key) &&
           isBSTProperty(pNode->p_right, pNode->key, max_val);
}

bool isAVL(NODE* pRoot) {
    if (pRoot == nullptr) {
        return true;
    }

    int balanceFactor = getBalance(pRoot);
    if (abs(balanceFactor) > 1) {
        return false;
    }

    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}