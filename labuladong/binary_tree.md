[TOC]

* an array or a linked list traversal framework

```cpp
// iterative traversal of the array
void traverse(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {

    }
}

// recursive traversal of the array
void traverse(vector<int>& arr, int i) {
    if (i == arr.size()) {
        return;
    }
    // pre-order position
    traverse(arr, i + 1);
    // post-order position
}

// iterative traversal of the singly linked list
void traverse(ListNode* head) {
    for (ListNode* p = head; p != nullptr; p = p->next) {

    }
}

// recursive traversal of the singly linked list
void traverse(ListNode* head) {
    if (head == nullptr) {
        return;
    }
    // pre-order position
    traverse(head->next);
    // post-order position
}
```

* binary tree traversal framework

```cpp
// binary tree traversal framework
void traverse(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    // pre-order position
    traverse(root->left);
    // in-order position
    traverse(root->right);
    // post-order position
}
```