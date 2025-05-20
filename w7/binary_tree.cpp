#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};

NODE* createNode(int data) {
    NODE* p = new NODE;
    p->key = data;
    p->p_left = nullptr;
    p->p_right = nullptr;
    return p;
}

vector<int> NLR(NODE* pRoot) {
    vector<int> result;
    if (pRoot == nullptr) {
        return result;
    }
    result.push_back(pRoot->key);
    vector<int> left_nodes = NLR(pRoot->p_left);
    result.insert(result.end(), left_nodes.begin(), left_nodes.end());
    vector<int> right_nodes = NLR(pRoot->p_right);
    result.insert(result.end(), right_nodes.begin(), right_nodes.end());
    return result;
}

vector<int> LNR(NODE* pRoot) {
    vector<int> result;
    if (pRoot == nullptr) {
        return result;
    }
    vector<int> left_nodes = LNR(pRoot->p_left);
    result.insert(result.end(), left_nodes.begin(), left_nodes.end());
    result.push_back(pRoot->key);
    vector<int> right_nodes = LNR(pRoot->p_right);
    result.insert(result.end(), right_nodes.begin(), right_nodes.end());
    return result;
}

vector<int> LRN(NODE* pRoot) {
    vector<int> result;
    if (pRoot == nullptr) {
        return result;
    }
    vector<int> left_nodes = LRN(pRoot->p_left);
    result.insert(result.end(), left_nodes.begin(), left_nodes.end());
    vector<int> right_nodes = LRN(pRoot->p_right);
    result.insert(result.end(), right_nodes.begin(), right_nodes.end());
    result.push_back(pRoot->key);
    return result;
}

vector<vector<int>> LevelOrder(NODE* pRoot) {
    vector<vector<int>> result;
    if (pRoot == nullptr) {
        return result;
    }

    queue<NODE*> q;
    q.push(pRoot);

    while (!q.empty()) {
        int level_size = q.size();
        vector<int> current_level_nodes;
        for (int i = 0; i < level_size; ++i) {
            NODE* current = q.front();
            q.pop();
            current_level_nodes.push_back(current->key);
            if (current->p_left) {
                q.push(current->p_left);
            }
            if (current->p_right) {
                q.push(current->p_right);
            }
        }
        result.push_back(current_level_nodes);
    }
    return result;
}

int countNode(NODE* pRoot) {
    if (pRoot == nullptr) {
        return 0;
    }
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

int sumNode(NODE* pRoot) {
    if (pRoot == nullptr) {
        return 0;
    }
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

int calculateHeightOfThisNode(NODE* pNode) {
    if (pNode == nullptr) {
        return -1; 
    }
    return 1 + max(calculateHeightOfThisNode(pNode->p_left), calculateHeightOfThisNode(pNode->p_right));
}

int heightNode(NODE* pRoot, int value) {
    if (pRoot == nullptr) {
        return -1; 
    }
    if (pRoot->key == value) {
        return calculateHeightOfThisNode(pRoot);
    }
    
    int left_height = heightNode(pRoot->p_left, value);
    if (left_height != -1) { 
        return left_height;
    }
    
    return heightNode(pRoot->p_right, value);
}

int Level(NODE* pRoot, NODE* p) {
    if (pRoot == nullptr || p == nullptr) {
        return -1;
    }

    queue<pair<NODE*, int>> q;
    q.push({pRoot, 0});

    while(!q.empty()) {
        NODE* current_node = q.front().first;
        int current_level = q.front().second;
        q.pop();

        if (current_node == p) {
            return current_level;
        }

        if (current_node->p_left) {
            q.push({current_node->p_left, current_level + 1});
        }
        if (current_node->p_right) {
            q.push({current_node->p_right, current_level + 1});
        }
    }
    return -1;
}

int countLeaf(NODE* pRoot) {
    if (pRoot == nullptr) {
        return 0;
    }
    if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) {
        return 1;
    }
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}

// int main() {
//     NODE* root = createNode(1);
//     root->p_left = createNode(2);
//     root->p_right = createNode(3);
//     root->p_left->p_left = createNode(4);
//     root->p_left->p_right = createNode(5);
//     root->p_right->p_left = createNode(6);

//     cout << "NLR: ";
//     vector<int> nlr_nodes = NLR(root);
//     for (int val : nlr_nodes) cout << val << " ";
//     cout << "\n";

//     cout << "LNR: ";
//     vector<int> lnr_nodes = LNR(root);
//     for (int val : lnr_nodes) cout << val << " ";
//     cout << "\n";

//     cout << "LRN: ";
//     vector<int> lrn_nodes = LRN(root);
//     for (int val : lrn_nodes) cout << val << " ";
//     cout << "\n";

//     cout << "Level Order: " << "\n";
//     vector<vector<int>> levels = LevelOrder(root);
//     for (const auto& level : levels) {
//         for (int val : level) {
//             cout << val << " ";
//         }
//         cout << "\n";
//     }

//     cout << "Node count: " << countNode(root) << "\n";
//     cout << "Sum of nodes: " << sumNode(root) << "\n";
//     cout << "Height of node with value 2: " << heightNode(root, 2) << "\n"; // Node 2 is root of subtree 2-4-5, height is 1
//     cout << "Height of node with value 3: " << heightNode(root, 3) << "\n"; // Node 3 is root of subtree 3-6, height is 1
//     cout << "Height of node with value 1: " << heightNode(root, 1) << "\n"; // Node 1 is root, height is 2
//     cout << "Height of node with value 5: " << heightNode(root, 5) << "\n"; // Node 5 is leaf, height is 0
//     cout << "Height of node with value 7 (not found): " << heightNode(root, 7) << "\n";


//     cout << "Level of node 5 (p_left->p_right): " << Level(root, root->p_left->p_right) << "\n"; // Expected 2
//     cout << "Level of node 3 (p_right): " << Level(root, root->p_right) << "\n"; // Expected 1
//     cout << "Level of root: " << Level(root, root) << "\n"; // Expected 0
//     NODE* temp_node = createNode(100); // A node not in the tree
//     cout << "Level of node 100 (not in tree): " << Level(root, temp_node) << "\n"; // Expected -1


//     cout << "Leaf count: " << countLeaf(root) << "\n"; // 4, 5, 6 are leaves

//     delete root->p_left->p_left;
//     delete root->p_left->p_right;
//     delete root->p_right->p_left;
//     delete root->p_left;
//     delete root->p_right;
//     delete root;
//     delete temp_node;

//     return 0;
// }