[TOC]

### [203. 移除链表元素](https://leetcode-cn.com/problems/remove-linked-list-elements/)

#### 不设置 dummy 节点

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        // edge case
        if (!head) return head;

        while (head && head->val == val) {
            head = head->next;
        }
        if (!head) return head;

        ListNode* current = head;
        
        while (current) {
            if (current->next && current->next->val == val) {
                current->next = current->next->next;
            } else {
                current = current->next;
            }
        }

        return head;
    }
};
```

#### 设置 dummy 节点

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        // edge case
        if (!head) return head;

        auto dummy = new ListNode();
        dummy->next = head;

        ListNode* current = dummy;
        while (current) {
            if (current->next && current->next->val == val) {
                auto toDelete = current->next;
                current->next = current->next->next;
                delete toDelete;
            } else {
                current = current->next;
            }
        }

        return dummy->next;
    }
};
```

#### 递归

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        // edge case
        if (!head) return head;

        // recursion
        if (head->val == val) {
            return removeElements(head->next, val);
        } else {
            head->next = removeElements(head->next, val);
            return head;
        }
    }
};
```

### [707. 设计链表](https://leetcode-cn.com/problems/design-linked-list/)

#### 不设置 dummy 节点

```cpp
class MyLinkedList {
public:
    struct ListNode {
        int val;
        ListNode* next;
        ListNode(int _val) : val(_val), next(nullptr) {}
    };

    ListNode* head;
    int length;

    MyLinkedList() {
        head = nullptr;
        length = 0;
    }
    
    int get(int index) {
        // special case
        if (index < 0 || index > length - 1) return -1;

        ListNode* cur = head;
        while (index--) {
            cur = cur->next;
        }
        return cur->val;
    }
    
    void addAtHead(int val) {
        ListNode* newHead = new ListNode(val);
        if (!head) {
            head = newHead;
        } else {
            newHead->next = head;
            head = newHead;
        }
        ++length;
    }
    
    void addAtTail(int val) {
        ListNode* newTail = new ListNode(val);
        if (!head) {
            head = newTail;
        } else {
            ListNode* curTail = head;
            while (curTail->next) curTail = curTail->next;
            curTail->next = newTail;
        }
        ++length;
    }
    
    void addAtIndex(int index, int val) {
        // special case
        if (index > length) return;

        if (index <= 0) {
            addAtHead(val);
        } else if (index == length) {
            addAtTail(val);
        } else {
            ListNode* newNode = new ListNode(val);

            ListNode* dummy = new ListNode(0);
            dummy->next = head;
            ListNode* pre = dummy;
            ListNode* cur = head;
            while (index--) {
                pre = pre->next;
                cur = cur->next;
            }
            pre->next = newNode;
            newNode->next = cur;
            ++length;

            delete dummy;
        }
    }
    
    void deleteAtIndex(int index) {
        if (index >= 0 && index <= length - 1) {
            if (index == 0) {
                ListNode* tmp = head;
                head = head->next;
                delete tmp;
            } else {
                ListNode* dummy = new ListNode(0);
                dummy->next = head;
                ListNode* pre = dummy;

                while (index--) {
                    pre = pre->next;
                }

                ListNode* deleteNode = pre->next;
                pre->next = pre->next->next;

                delete deleteNode;
                delete dummy;
            }
            --length;
        }
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
```

#### 设置 dummy 节点
```cpp
class MyLinkedList {
public:
    struct LinkedNode {
        int val = 0;
        LinkedNode* next = nullptr;
        LinkedNode() {}
        LinkedNode(int _val) : val(_val), next(nullptr) {}
    };

    LinkedNode* dummy = nullptr;
    int size = 0;

    MyLinkedList() {
        dummy = new LinkedNode();
        size = 0;
    }
    
    int get(int index) {
        // edge case
        if (index < 0 || index >= size) return -1;

        auto current = dummy;
        for (int i = 0; i <= index; ++i) {
            current = current->next;
        }

        return current->val;
    }
    
    void addAtHead(int val) {
        auto newNode = new LinkedNode(val);
        newNode->next = dummy->next;
        dummy->next = newNode;
        ++size;
    }
    
    void addAtTail(int val) {
        auto newNode = new LinkedNode(val);
        auto current = dummy;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
        ++size;
    }
    
    void addAtIndex(int index, int val) {
        // edge case
        if (index < 0 || index > size) return;

        auto newNode = new LinkedNode(val);

        if (index == size) {
            addAtTail(val);
            return;
        }

        auto current = dummy;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
        ++size;
    }
    
    void deleteAtIndex(int index) {
        // edge case
        if (index < 0 || index >= size) return;

        auto current = dummy;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }

        auto toDelete = current->next;
        current->next = current->next->next;
        delete toDelete;
        --size;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
```

### [206. 反转链表](https://leetcode-cn.com/problems/reverse-linked-list/)

#### 递归（base case 很重要，否则要加 else return head; 的判断语句）

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // base case
        if (!head || !head->next) return head;

        // recursion
        auto newHead = reverseList(head->next);
        
        head->next->next = head;
        head->next = nullptr;

        return newHead;
    }
};
```

#### 迭代

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // edge case
        if (!head || !head->next) return head;

        auto cur = head->next;
        head->next = nullptr;
        auto pre = head;
        while (cur) {
            auto nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }

        return pre;
    }
};
```

### [24. 两两交换链表中的节点](https://leetcode-cn.com/problems/swap-nodes-in-pairs/)

#### 递归

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        // recursion solution

        // base case
        if (!head || !head->next) return head;
        
        auto pre = head;
        auto cur = head->next;
        auto nxt = head->next->next;
        head = cur;
        head->next = pre;
        head->next->next = swapPairs(nxt);
        return head;
    }
};
```

#### 迭代 + dummy -> 掌握的不好，need to retry

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        // edge case
        if (!head || !head->next) return head;

        auto dummy = new ListNode();
        dummy->next = head;
        auto pre = dummy;

        while (pre->next && pre->next->next) {
            auto first = pre->next;
            auto second = pre->next->next;

            pre->next = second;
            first->next = second->next;
            second->next = first;

            pre = first;
        }

        auto newHead = dummy->next;
        delete dummy;
        return newHead;
    }
};
```

### [19. 删除链表的倒数第 N 个结点](https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/)

#### dummy

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // edge case
        if (n < 1 || !head) return nullptr;

        auto dummy = new ListNode();
        dummy->next = head;

        int size = 0;
        auto cur = head;
        while (cur) {
            ++size;
            cur = cur->next;
        }

        int length = size - n;
        cur = dummy;
        while (length--) {
            cur = cur->next;
        }

        auto toDelete = cur->next;
        cur->next = cur->next->next;
        delete toDelete;

        return dummy->next;
    }
};
```

### [面试题 02.07. 链表相交](https://leetcode-cn.com/problems/intersection-of-two-linked-lists-lcci/)

#### 递归（wrong solution）会导致两条腿乱走，导致先找到最后一个 intersection 的点再返回

具体例子分析
假设：

链表A: 1 → 2 → 3 → 4

链表B: 9 → 3 → 4

相交节点：从节点3开始相交（节点3和4是公共节点）

我们要找的是第一个相交节点3。

递归调用栈的详细展开

```txt
初始调用: getIntersectionNode(1, 9)
├── 情况1: getIntersectionNode(2, 9)  [A.next, B]
│   ├── 情况1: getIntersectionNode(3, 9)  [A.next.next, B]
│   │   ├── 情况1: getIntersectionNode(4, 9)  [A.next.next.next, B]
│   │   │   ├── 情况1: getIntersectionNode(null, 9) → return null
│   │   │   ├── 情况2: getIntersectionNode(4, 3)  [A, B.next]
│   │   │   │   ├── 情况1: getIntersectionNode(null, 3) → return null
│   │   │   │   ├── 情况2: getIntersectionNode(4, 4)  [A, B.next.next] ✓ 找到节点4!
│   │   │   │   │   └── 立即返回节点4
│   │   │   │   └── 情况3: getIntersectionNode(null, 4) → return null
│   │   │   └── 情况3: getIntersectionNode(null, 3) → return null
│   │   ├── 情况2: getIntersectionNode(3, 3)  [A, B.next] ✓ 找到节点3!
│   │   │   └── 但此时调用栈还在处理情况1，不会立即检查这个分支
│   │   └── 情况3: getIntersectionNode(4, 3)  [A.next, B.next]
│   │       └── (这个分支会在情况2之前执行吗？不一定，取决于具体实现)
│   └── 情况2: getIntersectionNode(2, 3)  [A, B.next]
│   └── 情况3: getIntersectionNode(3, 3)  [A.next, B.next] ✓ 找到节点3!
├── 情况2: getIntersectionNode(1, 3)  [A, B.next]
└── 情况3: getIntersectionNode(2, 3)  [A.next, B.next]
```

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // recursion solution

        // base case
        if (!headA || !headB) return nullptr;
        if (headA == headB) return headA;
        if (auto intersectionNode = getIntersectionNode(headA->next, headB)) return intersectionNode;
        if (auto intersectionNode = getIntersectionNode(headA, headB->next)) return intersectionNode;
        if (auto intersectionNode = getIntersectionNode(headA->next, headB->next)) return intersectionNode;
        return nullptr;
    }
};
```

#### 递归（right solution, but I don't understand at this moment）

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
private:
    ListNode* findIntersection(ListNode* a, ListNode* b, ListNode* originalB) {
        // 基准情况1：链表A遍历完毕
        if (!a) return nullptr;
        
        // 基准情况2：链表B遍历完毕，重置B指针并移动到A的下一个节点
        if (!b) return findIntersection(a->next, originalB, originalB);
        
        // 找到相交节点
        if (a == b) return a;
        
        // 继续在链表B中搜索当前A节点
        return findIntersection(a, b->next, originalB);
    }
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        return findIntersection(headA, headB, headB);
    }
};
```

#### 双指针(做得不好，need to retry)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        auto node1 = headA;
        auto node2 = headB;

        while (node1 != node2) {
            node1 = node1 ? node1->next : headB;
            node2 = node2 ? node2->next : headA;
        }

        return node1;
    }
};
```

#### 迭代（copy from 代码随想录）

```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* curA = headA;
        ListNode* curB = headB;
        int lenA = 0, lenB = 0;
        while (curA != NULL) { // 求链表A的长度
            lenA++;
            curA = curA->next;
        }
        while (curB != NULL) { // 求链表B的长度
            lenB++;
            curB = curB->next;
        }
        curA = headA;
        curB = headB;
        // 让curA为最长链表的头，lenA为其长度
        if (lenB > lenA) {
            swap (lenA, lenB);
            swap (curA, curB);
        }
        // 求长度差
        int gap = lenA - lenB;
        // 让curA和curB在同一起点上（末尾位置对齐）
        while (gap--) {
            curA = curA->next;
        }
        // 遍历curA 和 curB，遇到相同则直接返回
        while (curA != NULL) {
            if (curA == curB) {
                return curA;
            }
            curA = curA->next;
            curB = curB->next;
        }
        return NULL;
    }
};
```

#### 基于集合的做法

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        std::unordered_set<ListNode*> nodeSet;
        while (headA) {
            nodeSet.insert(headA);
            headA = headA->next;
        }

        while (headB) {
            if (nodeSet.count(headB)) return headB;
            headB = headB->next;
        }
        return nullptr;
    }
};
```

### [142. 环形链表 II](https://leetcode-cn.com/problems/linked-list-cycle-ii/)

#### 基于集合的做法

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        std::unordered_set<ListNode*> nodeSet;

        while (head) {
            if (nodeSet.count(head)) return head;
            nodeSet.insert(head);
            head = head->next;
        }

        return nullptr;
    }
};
```

#### 双指针（数学题，需证明，先不看了）

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        // special case
        if (!head) return nullptr;

        ListNode* fastPtr = head;
        ListNode* slowPtr = head;

        while (fastPtr && fastPtr->next) {
            // 不能写在前面，因为一开始 fastPtr == slowPtr
            // if (fastPtr == slowPtr) break;
            fastPtr = fastPtr->next->next;
            slowPtr = slowPtr->next;
            if (fastPtr == slowPtr) break;
        }

        if (!fastPtr || !fastPtr->next) return nullptr;

        // fastPtr 在相遇点，令 slowPtr 回到出发点，以同样的速度出发
        // 再次相遇点既是起始点
        slowPtr = head;
        while (slowPtr != fastPtr) {
            slowPtr = slowPtr->next;
            fastPtr = fastPtr->next;
        }

        return slowPtr;
    }
};
```

