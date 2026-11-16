// tag - 思路很巧妙，得背一下
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
private:
    int maxRootToLeafSum(TreeNode* root, int& maxLeafToLeafSum) {
        // base case
        if (!root) {
            return 0;
        }

        int left = maxRootToLeafSum(root->left, maxLeafToLeafSum);
        int right = maxRootToLeafSum(root->right, maxLeafToLeafSum);

        if (root->left && root->right) {
            maxLeafToLeafSum = std::max(maxLeafToLeafSum, left + right + root->val);

            return root->val + std::max(left, right);
        }

        return root->val + (root->left ? left : right);
    }

public:
    int findMaxLeafToLeafSum(TreeNode* root) {
        // edge case
        if (!root) {
            return 0;
        }

        int maxLeafToLeafSum = INT_MIN;

        maxRootToLeafSum(root, maxLeafToLeafSum);

        return maxLeafToLeafSum;
    }
};

/*
Time Complexity: O(n)
Space Complexity: O(h), where h is the height of the tree, in average case, h = log(n), in worst case, h = n
*/