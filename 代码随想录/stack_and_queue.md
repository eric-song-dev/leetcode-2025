[TOC]

### [232. 用栈实现队列](https://leetcode-cn.com/problems/implement-queue-using-stacks/)

```cpp
class MyQueue {
private:
    std::stack<int> inputStack;
    std::stack<int> outputStack;

public:
    MyQueue() {
        
    }
    
    void push(int x) {
        inputStack.push(x);
    }
    
    int pop() {
        int top = peek();
        outputStack.pop();
        return top;
    }
    
    int peek() {
        if (outputStack.empty()) {
            while (!inputStack.empty()) {
                auto tmp = inputStack.top();
                outputStack.push(tmp);
                inputStack.pop();
            }
        }

        if (outputStack.empty()) return -1;

        return outputStack.top();
    }
    
    bool empty() {
        return inputStack.empty() && outputStack.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
```

### [225. 用队列实现栈](https://leetcode-cn.com/problems/implement-stack-using-queues/)

#### 两个队列

```cpp
class MyStack {
private:
    std::queue<int> mainQueue;
    std::queue<int> tmpQueue;

public:
    MyStack() {
        
    }
    
    void push(int x) {
        tmpQueue.push(x);
        while (!mainQueue.empty()) {
            tmpQueue.push(mainQueue.front());
            mainQueue.pop();
        }

        std::swap(tmpQueue, mainQueue);
    }
    
    int pop() {
        auto res = top();
        mainQueue.pop();
        return res;
    }
    
    int top() {
        return mainQueue.front();
    }
    
    bool empty() {
        return mainQueue.empty() && tmpQueue.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
```

#### 一个队列

```cpp
class MyStack {
public:
    MyStack() {

    }
    
    void push(int x) {
        int oldLenth = que.size();

        que.push(x);
        while (oldLenth--) {
            que.push(que.front());
            que.pop();
        }
    }
    
    int pop() {
        int res = top();
        que.pop();
        return res;
    }
    
    int top() {
        return que.front();
    }
    
    bool empty() {
        return que.empty();
    }

private:
    queue<int> que;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
```

### [20. 有效的括号](https://leetcode-cn.com/problems/valid-parentheses/)

```cpp
class Solution {
public:
    bool isValid(string s) {
        // edge case
        if (s.empty()) return false;
        if (s.size() % 2 == 1) return false;

        std::unordered_map<char, char> umap = {
            {')', '('},
            {'}', '{'},
            {']', '['},
        };

        std::stack<char> stk;

        for (const auto& ch : s) {
            if (!umap.count(ch)) {  // ({[
                stk.push(ch);
            } else {                // ]})
                if (stk.empty() || umap[ch] != stk.top()) return false;
                else stk.pop();
            }
        }

        return stk.empty();
    }
};
```

### [1047. 删除字符串中的所有相邻重复项](https://leetcode-cn.com/problems/remove-all-adjacent-duplicates-in-string/)

#### 使用 std::stack

```cpp
class Solution {
public:
    string removeDuplicates(string s) {
        // edge case
        if (s.empty()) return s;

        std::stack<char> stk;
        for (const auto& ch : s) {
            if (!stk.empty() && ch == stk.top()) {
                stk.pop();
            } else {
                stk.push(ch);
            }
        }

        std::string res;
        while (!stk.empty()) {
            res.push_back(stk.top());
            stk.pop();
        }

        std::reverse(res.begin(), res.end());

        return res;
    }
};
```

#### 直接使用字符串作为栈

```cpp
class Solution {
public:
    string removeDuplicates(string s) {
        // special case
        if (s.empty()) return "";

        string res;
        for (auto ch : s) {
            if (res.empty()) {
                res.push_back(ch);
            } else {
                if (res.back() == ch) res.pop_back();
                else res.push_back(ch);
            }
        }

        return res;
    }
};
```

### [150. 逆波兰表达式求值](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/)

```cpp
class Solution {
private:
    pair<int, int> getTwoNums(stack<int>& stk) {
        auto num1 = stk.top();
        stk.pop();
        auto num2 = stk.top();
        stk.pop();
        
        return {num1, num2};
    }

public:
    int evalRPN(vector<string>& tokens) {
        // edge case
        if (tokens.size() < 1) return 0;

        std::stack<int> stk;
        int res = 0;
        for (const auto& token : tokens) {
            if (token == "+") {
                auto nums = getTwoNums(stk);
                stk.push(nums.second + nums.first);
            } else if (token == "-") {
                auto nums = getTwoNums(stk);
                stk.push(nums.second - nums.first);
            } else if (token == "*") {
                auto nums = getTwoNums(stk);
                stk.push(nums.second * nums.first);
            } else if (token == "/") {
                auto nums = getTwoNums(stk);
                stk.push(nums.second / nums.first);
            } else {
                stk.push(stoi(token));
            }
        }

        return stk.top();
    }
};
```

### [239. 滑动窗口最大值](https://leetcode-cn.com/problems/sliding-window-maximum/)

#### 自己写的超时算法

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // special case
        if (k > nums.size()) return {};

        vector<int> res;

        queue<int> que;
        int x = k;
        while (x != 0) {
            que.push(nums[k - x]);
            --x;
        }
        int maxValue = getMaxValueOfQueue(que);
        res.push_back(maxValue);

        for (int i = k; i != nums.size(); ++i) {
            que.pop();
            que.push(nums[i]);

            maxValue = getMaxValueOfQueue(que);
            res.push_back(maxValue);
        }

        return res;
    }

    int getMaxValueOfQueue(queue<int>& que) {
        int maxValue = INT32_MIN;

        int queSize = que.size();
        for (int i = 0; i != queSize; ++i) {
            maxValue = max(maxValue, que.front());
            que.push(que.front());
            que.pop();
        }

        return maxValue;
    }
};
```

#### 单调队列

```cpp
```

### [347. 前 K 个高频元素](https://leetcode-cn.com/problems/top-k-frequent-elements/)

#### 对 map 的 value 进行排序

#### [C++ STL中Map的按Key排序和按Value排序](https://blog.csdn.net/iicy266/article/details/11906189)

#### [reference to non-static member function must be called](https://blog.csdn.net/qq_26849233/article/details/77930991)

```cpp
class Solution {
private:
    // 不定义 static 就会有 this 指针，传入 sort 库函数时就会有问题
    static bool cmp(const pair<int, int>& lhs, const pair<int, int>& rhs) {
        return lhs.second > rhs.second;
    }

public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // special case
        if (nums.empty() || k > nums.size()) return {};

        map<int, int, less<int>> map;
        for (auto num : nums) {
            ++map[num];
        }

        vector<pair<int, int>> vec(map.begin(), map.end());
        sort(vec.begin(), vec.end(), cmp);


        vector<int> res;
        for (const auto& iter : vec) {
            res.push_back(iter.first);
            --k;
            if (k == 0) break;
        }

        return res;
    }
};
```

#### 优先级队列

```cpp
```

