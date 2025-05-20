#include <iostream>
#include <vector>

using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};

NODE* Search(NODE* pRoot, int x);
void Insert(NODE* &pRoot, int x);
void Remove(NODE* &pRoot, int x);
NODE* createTree(int a[], int n);
void removeTree(NODE* &pRoot);
int Height(NODE* pRoot);
int countLess(NODE* pRoot, int x);
int countGreater(NODE* pRoot, int x);
bool isBST(NODE* pRoot);
bool isFullBST(NODE* pRoot);

NODE* createBSTNode(int data) {
    NODE* p = new NODE;
    p->key = data;
    p->p_left = nullptr;
    p->p_right = nullptr;
    return p;
}

NODE* Search(NODE* pRoot, int x) {
    if (pRoot == nullptr || pRoot->key == x) {
        return pRoot;
    }
    if (x < pRoot->key) {
        return Search(pRoot->p_left, x);
    } else {
        return Search(pRoot->p_right, x);
    }
}

void Insert(NODE* &pRoot, int x) {
    if (pRoot == nullptr) {
        pRoot = createBSTNode(x);
        return;
    }
    if (x < pRoot->key) {
        Insert(pRoot->p_left, x);
    } else if (x > pRoot->key) { 
        Insert(pRoot->p_right, x);
    }
}

NODE* findMin(NODE* pNode) {
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
        if (pRoot->p_left == nullptr) {
            NODE* temp = pRoot->p_right;
            delete pRoot;
            pRoot = temp;
        } else if (pRoot->p_right == nullptr) {
            NODE* temp = pRoot->p_left;
            delete pRoot;
            pRoot = temp;
        } else {
            NODE* temp = findMin(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }
}

NODE* createTree(int a[], int n) {
    NODE* root = nullptr;
    for (int i = 0; i < n; ++i) {
        Insert(root, a[i]);
    }
    return root;
}

void removeTree(NODE* &pRoot) { 
    if (pRoot == nullptr) {
        return;
    }
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}

int Height(NODE* pRoot) {
    if (pRoot == nullptr) {
        return -1; 
    }
    int left_height = Height(pRoot->p_left);
    int right_height = Height(pRoot->p_right);
    return 1 + max(left_height, right_height);
}

int countLess(NODE* pRoot, int x) {
    if (pRoot == nullptr) {
        return 0;
    }
    if (pRoot->key < x) {
        return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
    }

    if (pRoot->key >= x) {
        return countLess(pRoot->p_left, x);
    } else { 
        int count = 1; 
        count += countLess(pRoot->p_left, x); 
        count += countLess(pRoot->p_right, x); 
        return count;
    }
}

int countGreater(NODE* pRoot, int x) {
    if (pRoot == nullptr) {
        return 0;
    }
    if (pRoot->key <= x) {
        return countGreater(pRoot->p_right, x);
    } else { 
        int count = 1; 
        count += countGreater(pRoot->p_right, x); 
        count += countGreater(pRoot->p_left, x); 
        return count;
    }
}

bool isBSTUtil(NODE* pNode, int min_val, int max_val) {
    if (pNode == nullptr) {
        return true;
    }
    if (pNode->key <= min_val || pNode->key >= max_val) {
        return false;
    }
    return isBSTUtil(pNode->p_left, min_val, pNode->key) &&
           isBSTUtil(pNode->p_right, pNode->key, max_val);
}

bool isBST(NODE* pRoot) {
    return isBSTUtil(pRoot, INT_MIN, INT_MAX);
}

bool isFull(NODE* pRoot) { 
    if (pRoot == nullptr) {
        return true; 
    }
    if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) {
        return true;
    }
    if (pRoot->p_left && pRoot->p_right) {
        return isFull(pRoot->p_left) && isFull(pRoot->p_right);
    }
    return false;
}

bool isFullBST(NODE* pRoot) {
    if (!isBST(pRoot)) {
        return false;
    }
    return isFull(pRoot);
}

// int main() {
//     NODE* bst_root = nullptr;
//     Insert(bst_root, 50);
//     Insert(bst_root, 30);
//     Insert(bst_root, 70);
//     Insert(bst_root, 20);
//     Insert(bst_root, 40);
//     Insert(bst_root, 60);
//     Insert(bst_root, 80);

//     cout << "BST In-order (should be sorted): ";

//     cout << "Search for 40: " << (Search(bst_root, 40) ? "Found" : "Not Found") << endl;
//     cout << "Search for 90: " << (Search(bst_root, 90) ? "Found" : "Not Found") << endl;

//     cout << "Height of BST: " << Height(bst_root) << endl; // Expected 2

//     cout << "Nodes less than 65: " << countLess(bst_root, 65) << endl; // 20,30,40,50,60 -> 5 nodes
//     cout << "Nodes less than 20: " << countLess(bst_root, 20) << endl; // 0 nodes
//     cout << "Nodes less than 50: " << countLess(bst_root, 50) << endl; // 20,30,40 -> 3 nodes
    
//     cout << "Nodes greater than 35: " << countGreater(bst_root, 35) << endl; // 40,50,60,70,80 -> 5 nodes
//     cout << "Nodes greater than 80: " << countGreater(bst_root, 80) << endl; // 0 nodes
//     cout << "Nodes greater than 50: " << countGreater(bst_root, 50) << endl; // 60,70,80 -> 3 nodes

//     cout << "Is BST? " << (isBST(bst_root) ? "Yes" : "No") << endl; // Yes

//     cout << "Is Full BST? " << (isFullBST(bst_root) ? "Yes" : "No") << endl; // Yes

//     Remove(bst_root, 20); // Remove a leaf

//     cout << "After removing 20, Is Full BST? " << (isFullBST(bst_root) ? "Yes" : "No") << endl; // No

//     Remove(bst_root, 30);

//     Insert(bst_root, 20); // 20 becomes left child of 40

//     cout << "After removing 30, then adding 20, Is Full BST? " << (isFullBST(bst_root) ? "Yes" : "No") << endl; // No

//     removeTree(bst_root);
//     cout << "Tree removed, root is: " << (bst_root ? "Not Null" : "Null") << endl; // Null

//     return 0;
// }