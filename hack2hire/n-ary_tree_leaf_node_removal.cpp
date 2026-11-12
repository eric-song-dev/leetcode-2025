#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Definition for N-ary tree node
struct Node {
    int val;
    vector<Node*> children;

    Node(int val) {
        this->val = val;
    }
};

class Solution {
private:
    int height(Node* root, std::vector<std::vector<int>>& res) {
        // base case
        if (!root) {
            return -1;
        }

        int h = 0;
        for (const auto& child : root->children) {
            h = std::max(h, height(child, res) + 1);
        }

        if (h == res.size()) {
            res.push_back({});
        }

        res[h].push_back(root->val);

        return h;
    }

public:
    vector<vector<int>> removeLeafNodes(Node* root) {
        // edge case
        if (!root) {
            return {};
        }

        std::vector<std::vector<int>> res;
        height(root, res);
        return res;
    }
};

/*
Time Complexity: O(n), where n is the size of nodes
Space Complexity: O(h), where h is the height of tree, in worst case, h = n
*/

int main() {
    // Test Case 1:
    //
    //   1
    // / | \
    // 2 3 4
    // |
    // 5
    //
    Node* root1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);
    Node* node5 = new Node(5);

    root1->children.push_back(node2);
    root1->children.push_back(node3);
    root1->children.push_back(node4);
    node2->children.push_back(node5);

    vector<vector<int>> res1 = (new Solution())->removeLeafNodes(root1);
    cout << "[";
    for (int i = 0; i < res1.size(); i++) {
        cout << "[";
        for (int j = 0; j < res1[i].size(); j++) {
            cout << res1[i][j];
            if (j < res1[i].size() - 1) cout << ", ";
        }
        cout << "]";
        if (i < res1.size() - 1) cout << ", ";
    }
    cout << "]" << endl; // Expected: [[5, 3, 4], [2], [1]]

    // Test Case 2:
    // 1
    // |
    // 2
    // |
    // 3
    // |
    // 4
    //
    Node* root2 = new Node(1);
    Node* node2_2 = new Node(2);
    Node* node3_2 = new Node(3);
    Node* node4_2 = new Node(4);

    root2->children.push_back(node2_2);
    node2_2->children.push_back(node3_2);
    node3_2->children.push_back(node4_2);

    vector<vector<int>> res2 = (new Solution())->removeLeafNodes(root2);
    cout << "[";
    for (int i = 0; i < res2.size(); i++) {
        cout << "[";
        for (int j = 0; j < res2[i].size(); j++) {
            cout << res2[i][j];
            if (j < res2[i].size() - 1) cout << ", ";
        }
        cout << "]";
        if (i < res2.size() - 1) cout << ", ";
    }
    cout << "]" << endl; // Expected: [[4], [3], [2], [1]]

    // Test Case 3:
    //
    //       1
    //     / | \ 
    //    2  3  4 
    //  / |     |\ 
    // 5  6    7  8 
    //   /|\    \
    // 9 10 11  12
    //
    Node* root3 = new Node(1);
    Node* n2 = new Node(2), *n3 = new Node(3), *n4 = new Node(4);
    Node* n5 = new Node(5), *n6 = new Node(6), *n7 = new Node(7), *n8 = new Node(8);
    Node* n9 = new Node(9), *n10 = new Node(10), *n11 = new Node(11), *n12 = new Node(12);

    root3->children.insert(root3->children.end(), {n2, n3, n4});
    n2->children.insert(n2->children.end(), {n5, n6});
    n4->children.insert(n4->children.end(), {n7, n8});
    n6->children.insert(n6->children.end(), {n9, n10, n11});
    n7->children.push_back(n12);

    vector<vector<int>> res3 = (new Solution())->removeLeafNodes(root3);
    cout << "[";
    for (int i = 0; i < res3.size(); i++) {
        cout << "[";
        for (int j = 0; j < res3[i].size(); j++) {
            cout << res3[i][j];
            if (j < res3[i].size() - 1) cout << ", ";
        }
        cout << "]";
        if (i < res3.size() - 1) cout << ", ";
    }
    cout << "]" << endl; // Expected: [[5, 9, 10, 11, 3, 12, 8], [6, 7], [2, 4], [1]]

    // Test Case 4:
    Node* root4 = new Node(42);
    vector<vector<int>> res4 = (new Solution())->removeLeafNodes(root4);
    cout << "[";
    for (int i = 0; i < res4.size(); i++) {
        cout << "[";
        for (int j = 0; j < res4[i].size(); j++) {
            cout << res4[i][j];
            if (j < res4[i].size() - 1) cout << ", ";
        }
        cout << "]";
        if (i < res4.size() - 1) cout << ", ";
    }
    cout << "]" << endl; // Expected: [[42]]

    // Test Case 5:
    //
    //      1 
    //  /  |  \  \ 
    // 2   3  4   5
    //
    Node* root5 = new Node(1);
    Node* c2 = new Node(2), *c3 = new Node(3), *c4 = new Node(4), *c5 = new Node(5);
    root5->children.insert(root5->children.end(), {c2, c3, c4, c5});

    vector<vector<int>> res5 = (new Solution())->removeLeafNodes(root5);
    cout << "[";
    for (int i = 0; i < res5.size(); i++) {
        cout << "[";
        for (int j = 0; j < res5[i].size(); j++) {
            cout << res5[i][j];
            if (j < res5[i].size() - 1) cout << ", ";
        }
        cout << "]";
        if (i < res5.size() - 1) cout << ", ";
    }
    cout << "]" << endl; // Expected: [[2, 3, 4, 5], [1]]

    return 0;
}
