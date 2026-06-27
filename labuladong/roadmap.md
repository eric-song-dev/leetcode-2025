[TOC]

### [303. Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/)

```cpp
class NumArray {
public:
    std::vector<int> preSum;

    NumArray(vector<int>& nums) {
        // edge case
        if (nums.empty()) return;

        preSum.resize(nums.size());
        preSum[0] = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            preSum[i] = preSum[i - 1] + nums[i];
        }
    }
    
    int sumRange(int left, int right) {
        // edge case
        if (left < 0 || right < 0 || left > right) return 0;

        if (left == 0) return preSum[right];
        else return preSum[right] - preSum[left - 1];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
```

### [304. Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/)

```cpp
class NumMatrix {
public:
    std::vector<std::vector<int>> preSum;

    NumMatrix(vector<vector<int>>& matrix) {
        /*
        // edge case
        if (matrix.empty() || matrix[0].empty()) {
            preSum.clear();
            return;
        }

        preSum.resize(matrix.size());
        preSum[0].resize(matrix[0].size());
        preSum[0][0] = matrix[0][0];

        for (int i = 1; i != matrix.size(); ++i) {
            preSum[i][0] = matrix[i][0] + preSum[i - 1][0];
        }

        for (int j = 1; j != matrix[0].size(); ++j) {
            preSum[0][j] = matrix[0][j] + preSum[0][j - 1];
        }

        for (int i = 1; i != matrix.size(); ++i) {
            for (int j = 1; j != matrix[0].size(); ++j) {
                preSum[i][j] = matrix[i][j] + preSum[i - 1][j] + preSum[i][j - 1] - preSum[i - 1][j - 1];
            }
        }
        */

        // edge size
        int m = matrix.size(), n = matrix[0].size();
        if (m == 0 || n == 0) return;
        preSum.resize(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                preSum[i][j] = preSum[i-1][j] + preSum[i][j-1] + matrix[i - 1][j - 1] - preSum[i-1][j-1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        // edge case
        if (row1 < 0 || row1 >= preSum.size()
            || col1 < 0 || col1 >= preSum[0].size()
            || row2 < 0 || row2 >= preSum.size()
            || col2 < 0 || col2 >= preSum[0].size()) {
            return 0;
        }

        return preSum[row2 + 1][col2 + 1] - preSum[row1][col2 + 1] - preSum[row2 + 1][col1] + preSum[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
```

### [724. Find Pivot Index](https://leetcode.com/problems/find-pivot-index/)

```cpp
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        // edge case
        if (nums.empty()) return -1;

        std::vector<int> preSumFromLeft;
        std::vector<int> preSumFromRight;
        preSumFromLeft.resize(nums.size(), 0);
        preSumFromRight.resize(nums.size(), 0);

        preSumFromLeft[0] = nums[0];
        for (int i = 1; i != nums.size(); ++i) {
            preSumFromLeft[i] = nums[i] + preSumFromLeft[i - 1];
        }

        preSumFromRight[nums.size() - 1] = nums[nums.size() - 1];
        if (nums.size() >= 2) {
            for (int i = nums.size() - 2; i != -1; --i) {
                preSumFromRight[i] = nums[i] + preSumFromRight[i + 1];
            }
        }

        for (int i = 0; i != nums.size(); ++i) {
            if (preSumFromLeft[i] == preSumFromRight[i]) return i;
        }

        return -1;
    }
};
```

### [238. Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/)

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        // edge case
        if (nums.empty()) return {};

        int productOfAll = 1;

        int countOf0 = 0;
        for (const auto& num : nums) {
            if (num == 0) ++countOf0;
            else productOfAll *= num;
        }

        std::vector<int> res;

        for (const auto& num : nums) {
            if (countOf0 > 1) { 
                res.push_back(0);
            } else if (countOf0 == 1) {
                if (num == 0) {
                    res.push_back(productOfAll);
                } else {
                    res.push_back(0);
                }
            } else {
                res.push_back(productOfAll / num);
            }
        }

        return res;
    }
};
```

### [525. Contiguous Array](https://leetcode.com/problems/contiguous-array)

```cpp
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        // edge case
        if (nums.empty()) return 0;

        int res = 0;
        std::vector<int> preSum;
        preSum.resize(nums.size());
        std::unordered_map<int, int> umap; // key: sum, value: index
        umap[0] = -1;

        for (int i = 0; i != nums.size(); ++i) {
            if (nums[i] == 0) nums[i] = -1;

            if (i == 0) {
                preSum[i] = nums[i];
            } else {
                preSum[i] = preSum[i - 1] + nums[i];
            }

            if (umap.count(preSum[i])) {
                int distance = i - umap[preSum[i]];
                res = std::max(distance, res);
            } else {
                umap[preSum[i]] = i;
            }
        }

        return res;
    }
};
```

### [370. Range Addition](https://leetcode.com/problems/range-addition/)

#### tag - 差分数组没咋看，需要再次复习

```cpp
class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        // edge case
        if (length <= 0) return {};

        std::vector<int> diff;
        diff.resize(length, 0);

        for (const auto& update : updates) {
            int startIdx = update[0];
            int endIdx = update[1];
            int inc = update[2];

            diff[startIdx] += inc;
            if (endIdx + 1 < diff.size()) diff[endIdx + 1] -= inc;
        }

        std::vector<int> res;
        res.resize(diff.size(), 0);
        res[0] = diff[0];
        for (int i = 1; i != diff.size(); ++i) {
            res[i] = res[i - 1] + diff[i];
        }

        return res;
    }
};

/*
array: [2, 0, 1, 3, 1]
diff: [2, -2, 1, 2, -2]

update: [1, 3, 2]
array: [2, 2, 3, 5, 1]
diff: [2, 0, 1, 2, -4]

diff[startIdx] += inc;
diff[endIdx + 1] -= inc;

array[0] = diff[0];
array[1] = diff[0] + diff[1] = array[0] + diff[1];
array[2] = diff[0] + diff[1] + diff[2] = array[1] + diff[2];
array[i] = array[i - 1] + diff[i];
*/
```

### [1109. Corporate Flight Bookings](https://leetcode.com/problems/corporate-flight-bookings)

```cpp
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        // edge case
        if (n <= 0) return {};

        std::vector<int> diff;
        diff.resize(n, 0);

        for (const auto& booking : bookings) {
            int startIdx = booking[0];
            int endIdx = booking[1];
            int inc = booking[2];

            if (startIdx - 1 >= 0 && startIdx - 1 < diff.size()) diff[startIdx - 1] += inc;
            if (endIdx >= 0 && endIdx < diff.size()) diff[endIdx] -= inc;
        }

        std::vector<int> res;
        res.resize(diff.size(), 0);
        res[0] = diff[0];
        for (int i = 1; i != diff.size(); ++i) {
            res[i] = res[i - 1] + diff[i];
        }

        return res;
    }
};
```

### [1094. Car Pooling](https://leetcode.com/problems/car-pooling/)

```cpp
class Solution {
public:
    const static int MAX_DISTANCE = 1001;

    bool carPooling(vector<vector<int>>& trips, int capacity) {
        // edge case
        if (capacity <= 0) return false;

        std::vector<int> diff;
        diff.resize(MAX_DISTANCE, 0);

        for (const auto& trip : trips) {
            int numPassengers = trip[0];
            int startIdx = trip[1];
            int endIdx = trip[2];

            if (startIdx >= 0 && startIdx < diff.size()) diff[startIdx] += numPassengers;
            if (endIdx >= 0 && endIdx < diff.size()) diff[endIdx] -= numPassengers;
        }

        std::vector<int> road;
        road.resize(diff.size(), 0);
        road[0] = diff[0];
        int maxNumPassengers = road[0];
        for (int i = 1; i != diff.size(); ++i) {
            road[i] = road[i - 1] + diff[i];
            maxNumPassengers = std::max(maxNumPassengers, road[i]);
        }

        return capacity >= maxNumPassengers;
    }
};

/*
trips = [[2,1,5],[3,3,7]]

tripo road: [0, 0, 0, 0, 0, 0, 0, 0]
trip0 road: [0, 2, 2, 2, 2, 0, 0, 0]
trip1 road: [0, 2, 2, 5, 5, 3, 3, 0]

trips = [[9,0,1],[3,3,7]]

tripo road: [0, 0, 0, 0, 0, 0, 0, 0]
trip0 road: [9, 0, 0, 0, 0, 0, 0, 0]
trip1 road: [9, 0, 0, 3, 3, 3, 3, 0]

check if capacity >= max value of tripn road
*/
```

### [48. Rotate Image](https://leetcode.com/problems/rotate-image/)

```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        // edge case
        if (matrix.empty() 
            || matrix[0].empty() 
            || matrix.size() != matrix[0].size()) return;

        // 1. update by diagonal
        for (int i = 0; i != matrix.size() - 1; ++i) {
            for (int j = i + 1; j != matrix.size(); ++j) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }

        // 2. reverse every row
        for (auto& row : matrix) {
            std::reverse(row.begin(), row.end());
        }
    }
};

/*
origin:
[1, 2, 3]
[4, 5, 6]
[7, 8, 9]

update by diagonal:
[1, 4, 7]
[2, 5, 8]
[3, 6, 9]

reverse every row:
[7, 4, 1]
[8, 5, 2]
[9, 6, 3]
*/
```

### [54. Spiral Matrix](https://leetcode.com/problems/spiral-matrix/)

```cpp
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return {};

        int m = matrix.size(), n = matrix[0].size();
        int upperBound = 0, lowerBound = m - 1;
        int leftBound = 0, rightBound = n - 1;
        vector<int> res;

        while (res.size() < m * n) {
            if (upperBound <= lowerBound) {
                for (int j = leftBound; j <= rightBound; ++j) {
                    res.push_back(matrix[upperBound][j]);
                }
                ++upperBound;
            }

            if (leftBound <= rightBound) {
                for (int i = upperBound; i <= lowerBound; ++i) {
                    res.push_back(matrix[i][rightBound]);
                }
                rightBound--;
            }
            
            if (upperBound <= lowerBound) {
                for (int j = rightBound; j >= leftBound; --j) {
                    res.push_back(matrix[lowerBound][j]);
                }
                lowerBound--;
            }
            
            if (leftBound <= rightBound) {
                for (int i = lowerBound; i >= upperBound; --i) {
                    res.push_back(matrix[i][leftBound]);
                }
                leftBound++;
            }
        }

        return res;
    }
};
```

### [622. Design Circular Queue](https://leetcode.com/problems/design-circular-queue/)

```cpp
class MyCircularQueue {
public:
    // [start, end)
    int start = 0;
    int end = 0;
    int count = 0;
    std::vector<int> buffer;

    MyCircularQueue(int k) {
        buffer.resize(k, 0);
    }
    
    bool enQueue(int value) {
        if (isFull()) return false;

        buffer[end] = value;
        end = (end + 1) % buffer.size();
        ++count;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) return false;

        start = (start + 1) % buffer.size();
        --count;
        return true;
    }
    
    int Front() {
        if (isEmpty()) return -1;

        return buffer[start];
    }
    
    int Rear() {
        if (isEmpty()) return -1;

        return buffer[(end - 1 + buffer.size()) % buffer.size()];
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == buffer.size();
    }
};

/*
normal array: [2, 3, 0, 0, 0, 1]
start: 5
end: 2
count: 3

empty array: [0, 0, 0, 0, 0, 0]
start: 5
end: 5
count: 0

full array: [2, 3, 4, 5, 6, 1]
start: 5
end: 5
count: 6
*/

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
```

### [641. Design Circular Deque](https://leetcode.com/problems/design-circular-deque/)

```cpp
class MyCircularDeque {
public:
    // [start, end)
    int start = 0;
    int end = 0;
    int count = 0;
    std::vector<int> buffer;

    MyCircularDeque(int k) {
        buffer.resize(k, 0);
    }
    
    bool insertFront(int value) {
        if (isFull()) return false;

        start = (start - 1 + buffer.size()) % buffer.size();
        buffer[start] = value;
        ++count;
        return true;
    }
    
    bool insertLast(int value) {
        if (isFull()) return false;

        buffer[end] = value;
        end = (end + 1) % buffer.size();
        ++count;
        return true;
    }
    
    bool deleteFront() {
        if (isEmpty()) return false;

        start = (start + 1) % buffer.size();
        --count;
        return true;
    }
    
    bool deleteLast() {
        if (isEmpty()) return false;

        end = (end - 1 + buffer.size()) % buffer.size();
        --count;
        return true;
    }
    
    int getFront() {
        if (isEmpty()) return -1;

        return buffer[start];
    }
    
    int getRear() {
        if (isEmpty()) return -1;

        return buffer[(end - 1 + buffer.size()) % buffer.size()];
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == buffer.size();
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
```

### [71. Simplify Path](https://leetcode.com/problems/simplify-path/)

```cpp
class Solution {
public:
    string simplifyPath(string path) {
        // edge case
        if (path.empty()) return "";

        std::vector<std::string> stk;
        std::istringstream iss(path);
        std::string token;

        while (std::getline(iss, token, '/')) {
            if (token == "." || token == "") {
                continue;
            } else if (token == "..") {
                if (!stk.empty()) stk.pop_back();
            } else {
                stk.push_back(token);
            }
        }

        std::string res;
        for (const auto& dir : stk) {
            res.append("/").append(dir);
        }

        return res.empty() ? "/" : res;
    }
};
```

### [225. Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)

#### tag - 难，得多背背

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

/*
main queue: []
tmp queue: []

push 1
main queue: []
tmp queue: [1]
redirect
main queue: []
tmp queue: [1]
switch
main queue: [1]
tmp queue: []

push 2
main queue: [1]
tmp queue: [2]
redirect
main queue: []
tmp queue: [2, 1]
switch
main queue: [2, 1]
tmp queue: []

push 2
main queue: [2, 1]
tmp queue: [3]
redirect
main queue: []
tmp queue: [3, 2, 1]
switch
main queue: [3, 2, 1]
tmp queue: []
*/

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
```

### [496. Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/)

#### tag - 难，单调栈的模板还得多理解理解

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        // edge case
        if (nums1.empty() || nums2.empty()) return {};

        std::unordered_map<int, int> umap; // key: num, value: the greater num
        std::stack<int> stk;
        for (int i = nums2.size() - 1; i >= 0; --i) {
            while (!stk.empty() && stk.top() <= nums2[i]) {
                stk.pop();
            }

            umap[nums2[i]] = stk.empty() ? -1 : stk.top();
            stk.push(nums2[i]);
        }

        std::vector<int> res;
        for (const auto& num : nums1) {
            res.push_back(umap.count(num) ? umap[num] : -1);
        }

        return res;
    }
};

/*
nums1: [5, 3, 7]
nums2: [2, 4, 3, 6, 5, 7]
res: [7, 6, -1]

first step: calculate every next greater element in nums2 solely

stack: [7], umap: {{7, -1}}
stack: [7, 5], umap: {{7, -1}, {5, 7}}
stack: [7, 6], umap: {{7, -1}, {5, 7}, {6, 7}}
stack: [7, 6, 3], umap: {{7, -1}, {5, 7}, {6, 7}, {3, 6}}
stack: [7, 6, 4], umap: {{7, -1}, {5, 7}, {6, 7}, {3, 6}, {4, 6}}
stack: [7, 6, 4, 2], umap: {{7, -1}, {5, 7}, {6, 7}, {3, 6}, {4, 6}, {2, 4}}
*/
```

### [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)

#### tag - 难理解，正着遍历和倒着遍历都要理解

#### 倒着遍历

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        // edge case
        if (temperatures.empty()) return {};

        std::vector<int> res(temperatures.size(), 0);
        std::stack<int> stk; // index
        for (int i = temperatures.size() - 1; i >= 0; --i) {
            while (!stk.empty() && temperatures[stk.top()] <= temperatures[i]) {
                stk.pop();
            }

            res[i] = stk.empty() ? 0 : stk.top() - i;
            stk.push(i);
        }

        return res;
    }
};
```

#### 正着遍历

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        // edge case
        if (temperatures.empty()) return {};

        std::vector<int> res(temperatures.size(), 0);
        std::stack<int> stk; // index
        for (int i = 0; i != temperatures.size(); ++i) {
            while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
                auto colderTempIndex = stk.top();
                res[colderTempIndex] = i - colderTempIndex;
                stk.pop();
            }

            stk.push(i);
        }

        return res;
    }
};
```

### [503. Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii)

```cpp
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        // edge case
        if (nums.empty()) return {};

        std::vector<int> res(nums.size(), -1);
        std::stack<int> stk; // index
        for (int i = 0; i != nums.size() * 2; ++i) {
            auto index = i % nums.size();
            while (!stk.empty() && nums[index] > nums[stk.top()]) {
                res[stk.top()] = nums[index];
                stk.pop();
            }
            stk.push(index);
        }

        return res;
    }
};

/*
the key point is traverse this array twice
*/
```

### [49. Group Anagrams](https://leetcode.com/problems/group-anagrams/)

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // edge case
        if (strs.empty()) return {};

        std::vector<std::vector<std::string>> res;
        std::unordered_map<std::string, std::vector<std::string>> umap; // key: char frequency, value: anagrams

        for (const auto& str : strs) {
            int frequencyVec[26] = {0};
            for (const auto& ch : str) {
                ++frequencyVec[ch - 'a'];
            }
            std::string charFrequencyStr;
            charFrequencyStr.reserve(52);
            for (const auto& frequency : frequencyVec) {
                charFrequencyStr += std::to_string(frequency);
                charFrequencyStr += ";";
            }
            umap[charFrequencyStr].push_back(str);
        }

        for (auto& iter : umap) {
            res.push_back(std::move(iter.second));
        }

        return res;
    }
};

/*
option 1:
step 1: group the same length strs first
step 2: group the anagrams together

option 2:
step 1: group the anagrams together directly

option 3:
step 1: sort every str
step 2: group the anagrams together

let's do option 2 first
*/
```

### [128. Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/)

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // edge case
        if (nums.empty()) return 0;

        std::unordered_set<int> uset(nums.begin(), nums.end());

        int res = 0;
        for (const auto& num : uset) {
            // it means num is the start of the consecutive elements sequence
            if (!uset.count(num - 1)) {
                int currentLength = 1;
                while (uset.count(num + currentLength)) {
                    ++currentLength;
                }

                res = std::max(res, currentLength);
            }
        }

        return res;
    }
};
```

### [290. Word Pattern](https://leetcode.com/problems/word-pattern/)

#### tag - 双向映射

```cpp
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        // edge case
        if (pattern.empty() || s.empty()) return false;

        std::istringstream iss(s);
        std::string token;
        int i = 0;
        std::unordered_map<char, std::string> umap; // key: letter in pattern, value: unique word in s
        std::unordered_set<std::string> uset; // key: unique word in s
        while (std::getline(iss, token, ' ')) {
            if (i >= pattern.size()) return false;

            if (umap.count(pattern[i])) {
                if (umap[pattern[i]] != token) return false;
            } else {
                if (uset.count(token)) return false;
                umap[pattern[i]] = token;
                uset.insert(token);
            }

            ++i;
        }

        return i == pattern.size();
    }
};
```

### [138. Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/)

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        // edge case
        if (!head) return nullptr;

        std::unordered_map<Node*, Node*> umap; // key: old node, value: new node

        auto cur = head;
        while (cur) {
            umap[cur] = new Node(cur->val);
            cur = cur->next;
        }

        for (const auto& [oldNode, newNode] : umap) {
            if (oldNode->next) newNode->next = umap[oldNode->next];
            if (oldNode->random) newNode->random = umap[oldNode->random];
        }

        return umap[head];
    }
};

/*
1. map the new nodes and old nodes first
2. make every pointer point to the right node
*/
```

### [169. Majority Element](https://leetcode.com/problems/majority-element/)

#### tag - Boyer-Moore 投票算法

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // edge case
        if (nums.empty()) return 0;

        int candidate = 0;
        int count = 0;

        for (const auto& num : nums) {
            if (count == 0) {
                candidate = num;
            }

            count += (num == candidate ? 1 : -1);
        }

        return candidate;
    }
};

/*
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // edge case
        if (nums.empty()) return 0;

        std::unordered_map<int, int> umap; // key: num, value: frequency

        for (const auto& num : nums) {
            ++umap[num];
            if (umap[num] > (nums.size() / 2)) return num;
        }

        return 0;
    }
};
*/
```

### [155. Min Stack](https://leetcode.com/problems/min-stack/)

```cpp
class MinStack {
private:
    std::stack<int> stk;
    std::stack<int> minStk;

public:
    MinStack() {
        
    }
    
    void push(int val) {
        stk.push(val);
        
        if (minStk.empty() || val <= minStk.top()) {
            minStk.push(val);
        }
    }
    
    void pop() {
        if (stk.top() == minStk.top()) {
            minStk.pop();
        }
        stk.pop();
    }
    
    int top() {
        if (stk.empty()) return -1;
        return stk.top();
    }
    
    int getMin() {
        if (minStk.empty()) return -1;
        return minStk.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
```

### [729. My Calendar I](https://leetcode.com/problems/my-calendar-i/)

```cpp
class MyCalendar {
private:
    std::vector<std::pair<int, int>> events;

public:
    MyCalendar() {
        
    }
    
    bool book(int startTime, int endTime) {
        for (const auto& event : events) {
            if (!(endTime <= event.first || startTime >= event.second)) return false;
        }

        events.push_back({startTime, endTime});
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(startTime,endTime);
 */

 /*
 option 1: make a fixed array, initial it with all 0; if book a event, change the relative elements to 1, but the range of start and end are too wide, so it's not a good solution

 option 2: just use std::pair, check if every start and end is in the pair
 */
```

### [950. Reveal Cards In Increasing Order](https://leetcode.com/problems/reveal-cards-in-increasing-order/)

```cpp
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        // edge case
        if (deck.empty()) return {};

        std::sort(deck.rbegin(), deck.rend());

        std::deque<int> dq;

        for (const auto& num : deck) {
            if (!dq.empty()) {
                auto tmp = dq.back();
                dq.pop_back();
                dq.push_front(tmp);
            }
            dq.push_front(num);
        }

        return std::vector(dq.begin(), dq.end());
    }
};

/*
reverse simulation
*/
```

### [1700. Number of Students Unable to Eat Lunch](https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/)

```cpp
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        // edge case
        if (students.empty() || sandwiches.empty()) return -1;

        int count0 = 0;
        int count1 = 0;

        for (const auto& s : students) {
            if (s == 0) ++count0;
            else ++count1;
        }

        for (const auto& sandwich : sandwiches) {
            if (sandwich == 0) {
                if (count0 == 0) break;
                --count0;
            } else {
                if (count1 == 0) break;
                --count1;
            }
        }

        return count0 + count1;
    }
};

/*
Instead of simulating the queue rotation, we can count how many students prefer each type.
Once we encounter a sandwich that no one prefers, the process must stop.
*/
```

### [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)

#### tag - 好题，适合练滑动窗口模板

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        // edge case
        if (s.empty() || t.empty()) return "";

        std::unordered_map<char, int> need; // key: char, value: frequency of a char
        std::unordered_map<char, int> window;
        for (const auto ch : t) {
            ++need[ch];
        }

        // [left, right)
        int left = 0;
        int right = 0;
        int valid = 0;
        std::pair<int, int> res = {0, INT_MAX}; // first: left, second: right
        while (right < s.size()) {
            auto rch = s[right];
            ++right;

            if (need.count(rch)) {
                ++window[rch];
                if (window[rch] == need[rch]) {
                    ++valid;
                }
            }

            while (valid == need.size()) {
                if (right - left < res.second - res.first) res = {left, right};

                auto lch = s[left];
                ++left;

                if (need.count(lch)) {
                    if (window[lch] == need[lch]) {
                        --valid;
                    }
                    --window[lch];
                }
            }
        }

        return res.second == INT_MAX ? "" : s.substr(res.first, res.second - res.first);
    }
};

/*
Step 1: expand the window by moving right pointer, keep expanding until the window satisfies the condition
Step 2: shrink the window by moving left pointer, once the window is valid, try to minimize it, keep shrinking until it becomes invalid again
*/
```

### [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/)

#### tag - 好题，注意由于是定长字符串，所以收缩滑动窗口的条件 if (right - left == s1.size())

```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        // edge case
        if (s1.empty() || s2.empty() || s1.size() > s2.size()) return false;

        std::unordered_map<char, int> need; // key: char, value: frequency of a char
        std::unordered_map<char, int> window;

        for (const auto ch : s1) {
            ++need[ch];
        }

        // [left, right)
        int left = 0;
        int right = 0;
        int valid = 0;

        while (right < s2.size()) {
            auto rch = s2[right];
            ++right;

            if (need.count(rch)) {
                ++window[rch];
                if (window[rch] == need[rch]) {
                    ++valid;
                }
            }

            if (right - left == s1.size()) {
                if (valid == need.size()) return true;

                auto lch = s2[left];
                ++left;

                if (need.count(lch)) {
                    if (window[lch] == need[lch]) {
                        --valid;
                    }
                    --window[lch];
                }
            }
        }

        return false;
    }
};

/*
Step 1: expand the window by moving right pointer, keep expanding until the window satisfies the condition
Step 2: shrink the window by moving left pointer, once the window is valid, try to minimize it, keep shrinking until it becomes invalid again
*/
```

### [438. Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string)

```cpp
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        // edge case
        if (s.empty() || p.empty() || s.size() < p.size()) return {};

        std::unordered_map<char, int> need; // key: char, value: frequency of a char
        std::unordered_map<char, int> window;

        for (const auto ch : p) {
            ++need[ch];
        }

        // [left, right)
        int left = 0;
        int right = 0;
        int valid = 0;
        std::vector<int> res;

        while (right < s.size()) {
            auto rch = s[right];
            ++right;

            if (need.count(rch)) {
                ++window[rch];
                if (window[rch] == need[rch]) {
                    ++valid;
                }
            }

            if (right - left == p.size()) {
                if (valid == need.size()) {
                    res.push_back(left);
                }

                auto lch = s[left];
                ++left;

                if (need.count(lch)) {
                    if (window[lch] == need[lch]) {
                        --valid;
                    }
                    --window[lch];
                }
            }
        }

        return res;
    }
};
```

### [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // edge case
        if (s.empty()) return 0;

        std::unordered_map<char, int> window; // key: char, value: frequency of a char

        // [left, right)
        int left = 0;
        int right = 0;
        int res = 0;

        while (right < s.size()) {
            auto rch = s[right++];
            ++window[rch];
            
            while (window[rch] > 1) {
                auto lch = s[left++];
                --window[lch];
            }

            res = std::max(res, right - left);
        }

        return res;
    }
};

/*
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // edge case
        if (s.empty()) return 0;

        std::unordered_map<char, int> window; // key: char, value: frequency of a char

        // [left, right)
        int left = 0;
        int right = 0;
        int valid = 0;
        int res = 0;

        while (right < s.size()) {
            auto rch = s[right++];

            ++window[rch];
            if (window[rch] == 1) {
                ++valid;
                res = std::max(res, valid);
            } 
            
            while (window[rch] > 1) {
                auto lch = s[left++];

                if (window[lch] == 1) {
                    --valid;
                }
                --window[lch];
            }
        }

        return res;
    }
};
*/

/*
s = "pwwkew"

left = 0, right = 1, valid = 1, res = 1
string = "p"
window = {{"p", 1}}

left = 0, right = 2, valid = 2, res = 2
string = "pw"
window = {{"p", 1}, {"w", 1}}

left = 0, right = 3, valid = 2, res = 2
string = "pww"
window = {{"p", 1}, {"w", 2}}

// start shrink
left = 1, right = 3, valid = 1, res = 2
string = "ww"
window = {{"p", 0}, {"w", 2}}

left = 2, right = 3, valid = 1, res = 2
string = "w"
window = {{"p", 0}, {"w", 1}}

// start extend
left = 2, right = 4, valid = 2, res = 2
string = "wk"
window = {{"p", 0}, {"w", 1}, {"k", 1}}

left = 2, right = 5, valid = 3, res = 3
string = "wke"
window = {{"p", 0}, {"w", 1}, {"k", 1}, {"e", 1}}

left = 2, right = 6, valid = 3, res = 3
string = "wkew"
window = {{"p", 0}, {"w", 2}, {"k", 1}, {"e", 1}}

// start shrink
left = 3, right = 6, valid = 3, res = 3
string = "kew"
window = {{"p", 0}, {"w", 1}, {"k", 1}, {"e", 1}}
*/
```

### [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        // edge case
        if (height.empty() || height.size() == 1) return 0;

        int n = height.size();

        std::vector<int> maxLeftBarOfEveryBar(n, 0);
        std::vector<int> maxRightBarOfEveryBar(n, 0);

        for (int i = 1; i < n; ++i) {
            maxLeftBarOfEveryBar[i] = std::max(maxLeftBarOfEveryBar[i - 1], height[i - 1]);
        }

        for (int i = n - 2; i >= 0; --i) {
            maxRightBarOfEveryBar[i] = std::max(maxRightBarOfEveryBar[i + 1], height[i + 1]);
        }

        int res = 0;
        for (int i = 1; i < n - 1; ++i) {
            res += std::max(0, std::min(maxLeftBarOfEveryBar[i], maxRightBarOfEveryBar[i]) - height[i]);
        }

        return res;
    }
};

/*
create a memo first to avoid double loop O(n square) time complexity
*/
```

### [11. Container With Most Water](https://leetcode.com/problems/container-with-most-water/)

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        // edge case
        if (height.empty() || height.size() == 1) return 0;

        int res = 0;
        int left = 0;
        int right = height.size() - 1;

        while (left < right) {
            res = std::max(res, (right - left) * std::min(height[left], height[right]));

            if (height[left] < height[right]) {
                ++left;
            } else if (height[left] > height[right]) {
                --right;
            } else /*if (height[left] == height[right])*/ {
                ++left;
                --right;
            }
        }

        return res;
    }
};

/*
two pointers
*/
```

### [80. Remove Duplicates from Sorted Array II](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/)

#### tag - if (nums[fast] != nums[slow - 1] || nums[fast] != nums[slow - 2]) 此 if 条件需注意

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // edge case
        if (nums.size() <= 2) return nums.size();

        int slow = 2;

        for (int fast = 2; fast < nums.size(); ++fast) {
            /*
            Incorrect approach: Comparing against nums[fast - n] fails because the elements behind fast might have already been overwritten by the slow pointer.
            [1,1,1,2,2,3], slow = 2, fast = 2
            [1,1,2,2,2,3], slow = 2, fast = 3
            [1,1,2,3,2,3], slow = 3, fast = 5
            if (nums[fast] != nums[fast - 1] || nums[fast] != nums[fast - 2]) {
                nums[slow++] = nums[fast];
            }
            */

            /*
            Correct approach: Compare the current element with the element at `slow - 2` in our newly formed valid array. If they are different, it means adding this element won't violate the "at most twice" rule.

            [1,1,1,2,2,3], slow = 2, fast = 2
            [1,1,2,2,2,3], slow = 3, fast = 3
            [1,1,2,2,2,3], slow = 4, fast = 4
            [1,1,2,2,3,3], slow = 5, fast = 5
            */
            if (nums[fast] != nums[slow - 1] || nums[fast] != nums[slow - 2]) {
                nums[slow++] = nums[fast];
            }
        }

        return slow;
    }
};

/*
slow, fast pointers
*/
```

### [125. Valid Palindrome](https://leetcode.com/problems/valid-palindrome/)

#### tag - 下一次可以用不修改字符串 s 的方法做

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        // edge case
        if (s.empty()) return true;

        // convert and prune
        int slow = 0;
        for (int fast = 0; fast < s.size(); ++fast) {
            if (std::isalnum(s[fast])) {
                if (std::isupper(s[fast])) {
                    s[slow] = std::tolower(s[fast]);
                } else {
                    s[slow] = s[fast];
                }
                ++slow;
            }
        }

        int left = 0;
        int right = slow - 1;

        while (left <= right) {
            if (s[left] != s[right]) return false;
            ++left;
            --right;
        }

        return true;
    }
};
```

### [1658. Minimum Operations to Reduce X to Zero](https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/)

#### tag - 思路很精妙，可以看下如何转换成一道 sliding window 题目

```cpp
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        // edge case
        if (nums.empty()) return -1;

        int sum = 0;
        for (const auto num : nums) {
            sum += num;
        }

        const int target = sum - x;

        // [left, right)
        int left = 0;
        int right = 0;
        int res = INT_MAX;

        int currentSum = 0;

        while (right < nums.size()) {
            auto rightNum = nums[right];
            ++right;
            
            currentSum += rightNum;

            while (currentSum > target && left < right) {
                auto leftNum = nums[left];
                ++left;

                currentSum -= leftNum;
            }

            if (currentSum == target) {
                res = std::min(res, (int)nums.size() - (right - left));
            }
        }

        return res == INT_MAX ? -1 : res;
    }
};

/*
expand: when the sum is less than x
shrink: when the sum is greater than x
collect data: when the sum equals x (minimum)

the key operation is to calculate the sum of the whole array first, and the target (sum - x) is a classic sliding window question
*/
```

### [713. Subarray Product Less Than K](https://leetcode.com/problems/subarray-product-less-than-k/)

#### tag - 经典的“求连续子数组数量”的滑动窗口题目，如何收集结果的思路很巧妙

```cpp
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        // edge case
        if (nums.empty()) return 0;
        if (k <= 1) return 0;

        // [left, right)
        int left = 0;
        int right = 0;
        int res = 0;
        int product = 1;

        while (right < nums.size()) {
            // expand the window
            auto rightNum = nums[right];
            ++right;

            product *= rightNum;

            while (product >= k && left < right) {
                // shrink the window
                auto leftNum = nums[left];
                ++left;

                product /= leftNum;
            }

            // collect the results
            if (product < k) {
                res += right - left;
            }
        }

        return res;
    }
};

/*
expand: when the product of all the elements in the subarray is strictly less than k
shrink: when the product of all the elements in the subarray is strictly greater than k
collect results: when the product of all the elements in the subarray is strictly less than k
*/
```

### [412. Fizz Buzz](https://leetcode.com/problems/fizz-buzz/)

```cpp
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        // edge case
        if (n <= 0) return {};

        std::vector<string> res;
        res.reserve(n);

        for (int i = 1; i <= n; ++i) {
            if (i % 15 == 0) {
                res.push_back("FizzBuzz");
            } else if (i % 3 == 0) {
                res.push_back("Fizz");
            } else if (i % 5 == 0) {
                res.push_back("Buzz");
            } else {
                res.push_back(std::to_string(i));
            }
        }

        return res;
    }
};
```

```cpp
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        // edge case
        if (n <= 0) return {};

        std::vector<std::string> res;
        res.reserve(n);

        for (int i = 1; i <= n; ++i) {
            std::string str;
            if (i % 3 == 0) str += "Fizz";
            if (i % 5 == 0) str += "Buzz";

            if (!str.empty()) {
                res.push_back(std::move(str));
            } else {
                res.push_back(std::to_string(i));
            }
        }

        return res;
    }
};
```

### [12. Integer to Roman](https://leetcode.com/problems/integer-to-roman/)

#### tag - 思路好难，用找零钱的思路和贪心算法

```cpp
class Solution {
public:
    string intToRoman(int num) {
        // edge case
        if (num <= 0) return "";

        // a lookup table sorted in descending order
        std::vector<std::pair<int, std::string>> valueSymbols = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
            {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
            {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"},
            {1, "I"}
        };

        std::string res;

        for (const auto& [value, symbol] : valueSymbols) {
            if (num == 0) break;

            while (num >= value) {
                std::cout << num << " " << value << " " << symbol << std::endl;
                res += symbol;
                num -= value;
            }
        }

        return res;
    }
};
```

### [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/)

#### tag - 好题

```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // edge case
        if (intervals.size() <= 1) return intervals;

        std::sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a.front() < b.front();
        });

        std::vector<std::vector<int>> res;
        res.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] <= res.back()[1]) {
                res.back()[1] = std::max(intervals[i][1], res.back()[1]);
            } else {
                res.push_back(intervals[i]);
            }
        }

        return res;
    }
};
```

### [704. Binary Search](https://leetcode.com/problems/binary-search/)

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        // edge case
        if (nums.empty()) return -1;

        // [left, right]
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] > target) right = mid - 1;
            else if (nums[mid] < target) left = mid + 1;
        }

        return -1;
    }
};
```

### [875. Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/)

#### tag - 思路很难想，双指针中的 left 和 right 指的是速度，if (hours == h) { right = mid - 1; } 里的 right 赋值条件也要注意

```cpp
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        // edge case
        if (piles.empty()) return -1;

        // left and right is the speed
        // the min speed is 1, the max speed is the max number in the array
        // [left, right]
        int left = 1;
        int right = *std::max_element(piles.begin(), piles.end());

        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long hours = 0;

            for (const auto bananas : piles) {
                hours += (bananas + mid - 1) / mid; // ceil(bananas / mid)
            }

            if (hours == h) {
                right = mid - 1; // mid has been verified, need to move to mid - 1
            } else if (hours > h) { // need to be faster
                left = mid + 1;
            } else if (hours < h) { // need to be slower
                right = mid - 1;
            }
        }

        return left;
    }
};
```

### [1011. Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)

```cpp
    class Solution {
    public:
        int shipWithinDays(vector<int>& weights, int days) {
            // edge case
            if (weights.empty()) return -1;

            // left and right is the weight capacity
            // [left, right]
            int left = *std::max_element(weights.begin(), weights.end());
            int right = std::accumulate(weights.begin(), weights.end(), 0);

            while (left <= right) {
                int mid = left + (right - left) / 2;
                int d = 1;

                int currentDayLoad = 0;
                for (const auto weight : weights) {
                    if (currentDayLoad + weight > mid) {
                        ++d;
                        currentDayLoad = weight;
                    } else {
                        currentDayLoad += weight;
                    }
                }

                if (d == days) {
                    right = mid - 1;
                } else if (d > days) { // need to be increase weight capacity
                    left = mid + 1;
                } else if (d < days) { // need to be decrease weight capacity
                    right = mid - 1;
                }
            }

            return left;
        }
    };
```

### [410. Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/)

#### tag - 总结来说，如果发现题目中存在单调关系，就可以尝试使用二分搜索的思路来解决。搞清楚单调性和二分搜索的种类，通过分析，就能够写出最终的代码

```cpp
class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        // edge case
        if (nums.empty()) return -1;

        // left and right are largest sum
        // [left, right]
        int left = *std::max_element(nums.begin(), nums.end());
        int right = std::accumulate(nums.begin(), nums.end(), 0);

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int sliceSize = 1;

            int currentSum = 0;
            for (const auto num : nums) {
                if (currentSum + num > mid) {
                    ++sliceSize;
                    currentSum = num;
                } else {
                    currentSum += num;
                }
            }

            if (sliceSize == k) {
                right = mid - 1;
            } else if (sliceSize > k) { // need to increase largest sum
                left = mid + 1;
            } else if (sliceSize < k) { // need to decrease largest sum
                right = mid - 1;
            }
        }

        return left;
    }
};
```

### [74. Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/)

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // edge case
        if (matrix.empty()) return false;

        int m = matrix.size();
        int n = matrix[0].size();
        // [left, right]
        int left = 0, right = m * n - 1;

        while(left <= right) {
            int mid = left + (right - left) / 2;
            int i = mid / n;
            int j = mid % n;
            int num = matrix[i][j];

            if(num == target)
                return true;
            else if (num < target)
                left = mid + 1;
            else if (num > target)
                right = mid - 1;
        }

        return false;
    }
};
```

### [240. Search a 2D Matrix II](https://leetcode.com/problems/search-a-2d-matrix-ii/)

#### tag - 思路有意思

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // edge case
        if (matrix.empty()) return false;

        int m = matrix.size();
        int n = matrix[0].size();

        int i = 0;
        int j = n - 1;
        while (i <= m - 1 && j >= 0) {
            int num = matrix[i][j];
            if (num == target) return true;
            else if (num > target) --j;
            else if (num < target) ++i;
        }

        return false;
    }
};

/*
starting from the top-left or bottom-right is ambiguous because both directions either strictly increase or strictly decrease
by starting at the top-right, moving left decreases the value and moving down increases it, allowing us to eliminate a row or column at each step like a binary search
*/
```

### [111. Minimum Depth of Binary Tree](https://leetcode.com/problems/minimum-depth-of-binary-tree/)

```cpp
/**
 * Definition for a binary tree node->
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int minDepth(TreeNode* root) {
        // edge case
        if (!root) return 0;

        int depth = 1;

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            auto size = q.size();
            while (size--) {
                auto node = q.front();
                q.pop();
                if (!node->left && !node->right) return depth;
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            ++depth;
        }

        return 0;
    }
};
```

### [222. Count Complete Tree Nodes](https://leetcode.com/problems/count-complete-tree-nodes/)

#### tag - 思路得看一下

```cpp
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
class Solution {
public:
    int countNodes(TreeNode* root) {
        // base case
        if (!root) return 0;

        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);

        if (leftHeight == rightHeight) return (1 << leftHeight) + countNodes(root->right);
        else return (1 << rightHeight) + countNodes(root->left);
    }

    int getHeight(TreeNode* root) {
        int h = 0;

        while (root) {
            ++h;
            root = root->left;
        }

        return h;
    }
};

/*
If left height == right height, the left subtree is a perfect binary tree; 
otherwise, the right subtree is a perfect binary tree.
*/
```

### [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)

```cpp
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
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        // edge case
        if (!root) return {};

        std::vector<std::vector<int>> res;
        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            auto size = q.size();
            std::vector<int> nodes;
            nodes.reserve(size);

            while (size--) {
                auto node = q.front();
                q.pop();
                
                nodes.push_back(node->val);

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            res.push_back(nodes);
        }

        return res;
    }
};
```

### [144. Binary Tree Preorder Traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/)

#### tag - iterative 思路得看一下

#### recursive

```cpp
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
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        // edge case
        if (!root) return {};

        std::vector<int> res;
        preorderTraversal(root, res);
        return res;
    }

    void preorderTraversal(TreeNode* root, std::vector<int>& res) {
        // base case
        if (!root) return;
        res.push_back(root->val);
        preorderTraversal(root->left, res);
        preorderTraversal(root->right, res);
    }
};
```

#### iterative

```cpp
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
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        // edge case
        if (!root) return {};

        std::vector<int> res;
        std::stack<TreeNode*> stk;
        stk.push(root);

        while (!stk.empty()) {
            auto node = stk.top();
            stk.pop();

            res.push_back(node->val);

            if (node->right) stk.push(node->right);
            if (node->left) stk.push(node->left);
        }

        return res;
    }
};
```

### [94. Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/)

#### tag - iterative 思路得看一下

#### recursive

```cpp
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
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        // edge case
        if (!root) return {};

        std::vector<int> res;
        inorderTraversal(root, res);
        return res;
    }

    void inorderTraversal(TreeNode* root, std::vector<int>& res) {
        // base case
        if (!root) return;

        inorderTraversal(root->left, res);
        res.push_back(root->val);
        inorderTraversal(root->right, res);
    }
};
```

#### iterative

```cpp
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
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        // edge case
        if (!root) return {};

        std::vector<int> res;
        std::stack<TreeNode*> stk;
        auto cur = root;

        while (cur || !stk.empty()) {
            if (cur) {
                stk.push(cur);
                cur = cur->left;
            } else {
                cur = stk.top();
                stk.pop();
                res.push_back(cur->val);
                cur = cur->right;
            }
        }

        return res;
    }
};
```

### [145. Binary Tree Postorder Traversal](https://leetcode.com/problems/binary-tree-postorder-traversal/)

#### tag - normal iterative 思路得看一下，I totally cannot understand this solution

#### recursive

```cpp
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
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        // edge case
        if (!root) return {};

        std::vector<int> res;
        postorderTraversal(root, res);
        return res;
    }

    void postorderTraversal(TreeNode* root, std::vector<int>& res) {
        // base case
        if (!root) return;

        postorderTraversal(root->left, res);
        postorderTraversal(root->right, res);
        res.push_back(root->val);
    }
};
```

#### iterative - reverse

```cpp
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
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        // edge case
        if (!root) return {};

        std::vector<int> res;
        std::stack<TreeNode*> stk;
        stk.push(root);

        while (!stk.empty()) {
            auto node = stk.top();
            stk.pop();

            res.push_back(node->val);

            if (node->left) stk.push(node->left);
            if (node->right) stk.push(node->right);
        }

        reverse(res.begin(), res.end());

        return res;
    }
};

/*
since the preorder is root -> left -> right
we can reverse the order of left and right
so the preorder will be root -> right -> left

and then reverse all array
then we will get the postorder, left -> right -> root
*/
```

#### iterative - normal

```cpp
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
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        std::stack<TreeNode*> st;
        TreeNode* curr = root;
        TreeNode* prev = nullptr; // 记录上一个加入 res 的节点
        
        while (curr != nullptr || !st.empty()) {
            // 1. 一路向左，把路径上的节点全部压栈
            while (curr != nullptr) {
                st.push(curr);
                curr = curr->left;
            }
            
            // 2. 此时左边走到头了，查看栈顶节点（先不弹出）
            curr = st.top();
            
            // 3. 判断是否可以处理当前节点
            // 如果右子树为空，或者右子树刚刚被访问过
            if (curr->right == nullptr || curr->right == prev) {
                res.push_back(curr->val);  // 处理该节点
                st.pop();                  // 正式从栈中弹出
                prev = curr;               // 标记该节点已被处理
                curr = nullptr;            // 将 curr 设为空，强制下一轮从栈中弹节点，而不是继续向下走
            } else {
                // 4. 否则，说明右子树还没处理，转向右子树
                curr = curr->right;
            }
        }
        
        return res;
    }
};
```

### [543. Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)

#### tag - 思路很有意思

```cpp
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
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        // edge case
        if (!root) return 0;

        int res = 0;
        maxDepth(root, res);
        return res;
    }

    int maxDepth(TreeNode* node, int& res) {
        // base case
        if (!node) return 0;

        auto leftDepth = maxDepth(node->left, res);
        auto rightDepth = maxDepth(node->right, res);
        
        res = std::max(res, leftDepth + rightDepth);

        return 1 + std::max(leftDepth, rightDepth);
    }
};

/*
the diameter passing through a node = left subtree depth + right subtree depth
*/
```

### [104. Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/)

```cpp
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
class Solution {
public:
    int maxDepth(TreeNode* root) {
        // base case
        if (!root) return 0;

        return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
    }
};
```

### [226. Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/)

#### recursive

```cpp
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
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        // base case
        if (!root) return nullptr;

        invertTree(root->left);
        invertTree(root->right);

        std::swap(root->left, root->right);

        return root;
    }
};
```

#### iterasive

```cpp
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
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        // edge case
        if (!root) return nullptr;

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            auto size = q.size();
            while (size--) {
                auto node = q.front();
                q.pop();

                std::swap(node->left, node->right);

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }

        return root;
    }
};
```

### [116. Populating Next Right Pointers in Each Node](https://leetcode.com/problems/populating-next-right-pointers-in-each-node/)

#### tag - 好题，我感觉这题很容易被考到，follow-up 很多，itrative normal 方法需要好好学习下

#### recursive

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        // base case
        if (!root || (!root->left && !root->right)) return root;

        root->left->next = root->right;
        if (root->next) root->right->next = root->next->left;

        root->left = connect(root->left);
        root->right = connect(root->right);

        return root;
    }
};
```

#### iterative - level

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        // edge case
        if (!root) return nullptr;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            auto size = q.size();
            Node* prev = nullptr;
            while (size--) {
                auto node = q.front();
                q.pop();

                if (prev) prev->next = node;
                prev = node;

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }

        return root;
    }
};
```

#### iterative - normal

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        // edge case
        if (!root) return nullptr;

        auto cur = root;

        while (cur) {
            auto dummy = new Node(0);
            auto tail = dummy;

            while (cur) {
                if (cur->left) {
                    tail->next = cur->left;
                    tail = tail->next;
                }

                if (cur->right) {
                    tail->next = cur->right;
                    tail = tail->next;
                }

                cur = cur->next;
            }

            cur = dummy->next;

            delete dummy;
        }

        return root;
    }
};
```

### [117. Populating Next Right Pointers in Each Node II](https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/)

#### iterative - level

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        // edge case
        if (!root) return nullptr;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            auto size = q.size();
            Node* prev = nullptr;
            while (size--) {
                auto node = q.front();
                q.pop();

                if (prev) prev->next = node;
                prev = node;

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }

        return root;
    }
};
```

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        // edge case
        if (!root) return nullptr;

        auto cur = root;

        while (cur) {
            auto dummy = new Node(0);
            auto tail = dummy;

            while (cur) {
                if (cur->left) {
                    tail->next = cur->left;
                    tail = tail->next;
                }

                if (cur->right) {
                    tail->next = cur->right;
                    tail = tail->next;
                }

                cur = cur->next;
            }

            cur = dummy->next;

            delete dummy;
        }

        return root;
    }
};
```

### [114. Flatten Binary Tree to Linked List](https://leetcode.com/problems/flatten-binary-tree-to-linked-list/)

#### tag - morris method TBD, recursive - reverse 的方法很巧妙，值得研究

#### recursive

```cpp
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
class Solution {
public:
    void flatten(TreeNode* root) {
        // base case
        if (!root) return;
        
        flatten(root->left);
        flatten(root->right);

        auto tmp = root->right;
        root->right = root->left;
        root->left = nullptr;

        auto cur = root;
        while (cur->right) {
            cur = cur->right;
        }
        cur->right = tmp;
    }
};
```

#### recursive - array

```cpp
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
class Solution {
public:
    void flatten(TreeNode* root) {
        // edge case
        if (!root) return;
        
        std::vector<TreeNode*> nodes;
        preOrderTraverse(root, nodes);

        TreeNode* cur = root;

        for (int i = 1; i < nodes.size(); ++i) {
            cur->right = nodes[i];
            cur->left = nullptr;
            cur = cur->right;
        }
    }

    void preOrderTraverse(TreeNode* node, std::vector<TreeNode*>& nodes) {
        // base case
        if (!node) return;

        nodes.push_back(node);
        preOrderTraverse(node->left, nodes);
        preOrderTraverse(node->right, nodes);
    }
};
```

#### recursive - reverse

```cpp
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
class Solution {
private:
    TreeNode* prev = nullptr;

public:
    void flatten(TreeNode* root) {
        // base case
        if (!root) return;

        flatten(root->right);
        flatten(root->left);

        root->right = prev;
        root->left = nullptr;
        prev = root;
    }
};

/*
root -> left -> right
becomes
right -> left -> root
*/
```

#### morris - TBD

```cpp

```

### [654. Maximum Binary Tree](https://leetcode.com/problems/maximum-binary-tree/)

#### tag - Monotonic Stack TBD

#### low performance

```cpp
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
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        // base case
        if (nums.empty()) {
            return nullptr;
        } else if (nums.size() == 1) {
            return new TreeNode(nums[0]);
        }

        auto maxNumIt = std::max_element(nums.begin(), nums.end());
        auto maxNum = *maxNumIt;
        int index = std::distance(nums.begin(), maxNumIt);

        vector<int> leftNums(nums.begin(), maxNumIt);
        vector<int> rightNums(maxNumIt + 1, nums.end());

        auto node = new TreeNode(maxNum);
        node->left = constructMaximumBinaryTree(leftNums);
        node->right = constructMaximumBinaryTree(rightNums);

        return node;
    }
};
```

#### high performance

```cpp
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
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        // edge case
        if (nums.empty()) {
            return nullptr;
        } else if (nums.size() == 1) {
            return new TreeNode(nums[0]);
        }

        return build(nums, 0, nums.size() - 1);
    }

private:
    TreeNode* build(const vector<int>& nums, int left, int right) {
        // edge case
        if (left > right) {
            return nullptr;
        }

        int maxIndex = left;
        for (int i = left + 1; i <= right; ++i) {
            if (nums[i] > nums[maxIndex]) {
                maxIndex = i;
            }
        }

        TreeNode* node = new TreeNode(nums[maxIndex]);

        node->left = build(nums, left, maxIndex - 1);
        node->right = build(nums, maxIndex + 1, right);
        
        return node;
    }
};
```

#### Monotonic Stack TBD

### [105. Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

```cpp
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
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // edge case
        if (preorder.empty() || inorder.empty() || preorder.size() != inorder.size()) return nullptr;

        auto root = new TreeNode(preorder[0]);
        auto rootIt = std::find(inorder.begin(), inorder.end(), preorder[0]);

        int leftSize = std::distance(inorder.begin(), rootIt);
        // [start, end)
        vector<int> preLeft(preorder.begin() + 1, preorder.begin() + 1 + leftSize);
        vector<int> inLeft(inorder.begin(), rootIt);
        vector<int> preRight(preorder.begin() + 1 + leftSize, preorder.end());
        vector<int> inRight(rootIt + 1, inorder.end());

        root->left = buildTree(preLeft, inLeft);
        root->right = buildTree(preRight, inRight);
        return root;
    }
};

/*
preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
root is the preorder[0]
the left side of root in inorder is left subtree
the right side of root in inorder is right subtree
then recursively handle the tree
*/
```

### [106. Construct Binary Tree from Inorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/)

#### tag - closed interval [start, end] requires start > end, as start == end still contains 1 element

```cpp
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
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        // edge case
        if (inorder.empty() || postorder.empty() || inorder.size() != postorder.size()) return nullptr;

        std::unordered_map<int, int> inorderMap;
        for (int i = 0; i != inorder.size(); ++i) {
            inorderMap[inorder[i]] = i;
        }

        return build(inorder, 0, inorder.size() - 1,
                     postorder, 0, postorder.size() - 1,
                     inorderMap);
    }

private:
    // [inStart, inEnd], [postStart, postEnd]
    TreeNode* build(const vector<int>& inorder, int inStart, int inEnd,
                    const vector<int>& postorder, int postStart, int postEnd,
                    const std::unordered_map<int, int>& inorderMap) {
        // base case
        if (inStart > inEnd || postStart > postEnd) return nullptr;

        auto root = new TreeNode(postorder[postEnd]);

        auto rootIdx = inorderMap.at(root->val);

        auto leftSize = rootIdx - inStart;

        root->left = build(inorder, inStart, inStart + leftSize - 1,
                           postorder, postStart, postStart + leftSize - 1,
                           inorderMap);
        root->right = build(inorder, inStart + leftSize + 1, inEnd,
                            postorder, postStart + leftSize, postEnd - 1,
                            inorderMap);

        return root;
    };
};

/*
inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
root is the postorder[postorder.size() - 1]
the left side of root in inorder is left subtree
the right side of root in inorder is right subtree
then recursively handle the tree
*/
```

### [889. Construct Binary Tree from Preorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/)

```cpp
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
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        // edge case
        if (preorder.empty() || postorder.empty() || preorder.size() != postorder.size()) return nullptr;

        std::unordered_map<int, int> postorderMap;
        for (int i = 0; i != postorder.size(); ++i) {
            postorderMap[postorder[i]] = i;
        }

        return build(preorder, 0, preorder.size() - 1,
                     postorder, 0, postorder.size() - 1,
                     postorderMap);
    }

    // [preStart, preEnd], [postStart, postEnd]
    TreeNode* build(const vector<int>& preorder, int preStart, int preEnd,
                    const vector<int>& postorder, int postStart, int postEnd,
                    const std::unordered_map<int, int>& postorderMap) {
        // base case
        if (preStart > preEnd) return nullptr;

        auto root = new TreeNode(preorder[preStart]);

        if (preStart == preEnd) return root;

        auto leftRootIdx = postorderMap.at(preorder[preStart + 1]);

        auto leftSize = leftRootIdx - postStart + 1;

        root->left = build(preorder, preStart + 1, preStart + leftSize,
                           postorder, postStart, postStart + leftSize - 1,
                           postorderMap);
        root->right = build(preorder, preStart + leftSize + 1, preEnd,
                            postorder, postStart + leftSize, postEnd - 1,
                            postorderMap);

        return root;
    };
};
```

### [652. Find Duplicate Subtrees](https://leetcode.com/problems/find-duplicate-subtrees/)

#### tag - 如何 Canonical Representation（规范表示）一棵树，加入打印空节点，中序遍历（Inorder） + 空指针 不可以唯一确认一颗 subtree

#### note

1. 如果你的序列化结果中不包含空指针的信息，且你只给出一种遍历顺序，那么你无法还原出唯一的一棵二叉树。
2. 如果你的序列化结果中不包含空指针的信息，且你会给出两种遍历顺序，分两种情况：
    2.1. 如果你给出的是前序和中序，或者后序和中序，那么你可以还原出唯一的一棵二叉树。
    2.2. 如果你给出前序和后序，那么你无法还原出唯一的一棵二叉树。
3. 如果你的序列化结果中包含空指针的信息，且你只给出一种遍历顺序，也要分两种情况：
    3.1. 如果你给出的是前序或者后序，那么你可以还原出唯一的一棵二叉树。
    3.2. 如果你给出的是中序，那么你无法还原出唯一的一棵二叉树。

```cpp
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
class Solution {
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        // base case
        if (!root) return {};

        std::unordered_map<string, int> counts;
        std::vector<TreeNode*> res;

        std::function<std::string(TreeNode*)> dfs = [&](TreeNode* node) -> std::string {
            if (!node) return "#";
            
            std::string treeStr = std::to_string(node->val) + "," + dfs(node->left) + "," + dfs(node->right);
            
            if (++counts[treeStr] == 2) {
                res.push_back(node);
            }
            
            return treeStr;
        };
        
        dfs(root);
        return res;
    }
};
```

### [297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)

#### tag - 序列化的思想

#### note

1. 如果你的序列化结果中不包含空指针的信息，且你只给出一种遍历顺序，那么你无法还原出唯一的一棵二叉树。
2. 如果你的序列化结果中不包含空指针的信息，且你会给出两种遍历顺序，分两种情况：
    2.1. 如果你给出的是前序和中序，或者后序和中序，那么你可以还原出唯一的一棵二叉树。
    2.2. 如果你给出前序和后序，那么你无法还原出唯一的一棵二叉树。
3. 如果你的序列化结果中包含空指针的信息，且你只给出一种遍历顺序，也要分两种情况：
    3.1. 如果你给出的是前序或者后序，那么你可以还原出唯一的一棵二叉树。
    3.2. 如果你给出的是中序，那么你无法还原出唯一的一棵二叉树。

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        // base case
        if (!root) return "#";

        return std::to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        // edge case
        if (data.empty() || data == "#") return nullptr;

        std::stringstream ss(data);
        return buildTree(ss);
    }

    TreeNode* buildTree(std::stringstream& ss) {
        std::string str;
        
        // base case
        if (!std::getline(ss, str, ',')) {
            return nullptr;
        }

        if (str == "#") {
            return nullptr;
        }

        auto root = new TreeNode(std::stoi(str));
        root->left = buildTree(ss);
        root->right = buildTree(ss);

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

/*
1,2,#,#,3,4,#,#,5,#,#
root = "1"
left = "2,#,#""
right = "3,4,#,#,5,#,#"
*/
```

### [230. Kth Smallest Element in a BST](https://leetcode.com/problems/kth-smallest-element-in-a-bst/)

```cpp
/**d
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
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        // edge case
        if (!root) return -1;

        int res = -1;
        traverse(root, k, res);

        return res;
    }

    void traverse(TreeNode* root, int& k, int& res) {
        // base case
        if (!root) return;

        traverse(root->left, k, res);

        --k;
        if (k == 0) {
            res = root->val;
            return;
        }

        traverse(root->right, k, res);
    }
};
```

### [538. Convert BST to Greater Tree](https://leetcode.com/problems/convert-bst-to-greater-tree/)

#### tag - 思路很有趣，自己想的，kudos to 自己

#### note
| 维度 | 「遍历」思维 | 「分解问题」思维 |
| --- | --- | --- |
| **递归函数长啥样** | 通常是单独写一个 void traverse(...) 辅助函数 | 通常直接利用主函数，**有返回值**（如 int, TreeNode） |
| **结果存在哪里** | 通常需要借助**外部变量/全局变量**来记录结果 | 结果通过函数的 **return 值** 一层层拼接返回 |
| **思考问题的视角** | 把目光聚焦在一个节点上：**“我当前在这个节点，我需要干嘛？”** | 把目光聚焦在整棵树上：**“这棵大树的结果，能不能由左右两棵小树的结果推导出来？”** |

```cpp
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
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        int sum = 0;
        traverse(root, sum);
        return root;
    }

    void traverse(TreeNode* root, int& sum) {
        // base case
        if (!root) return;

        traverse(root->right, sum);
        root->val += sum;
        sum = root->val;
        traverse(root->left, sum);
    }
};

/*
left -> root -> right is inorder traversal
the inorder traversal of a BST is in ascending order
so let's change the order to right -> root -> left
the reverse inorder traversal of a BST is in descending order
*/
```

### [236. Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/)

#### tag - 思路挺难的，要同时在前序和后序位置做判断

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // base case
        if (!root) return nullptr;

        if (root == p || root == q) {
            return root;
        }

        auto left = lowestCommonAncestor(root->left, p, q);
        auto right = lowestCommonAncestor(root->right, p, q);

        if (left && right) {
            return root;
        }

        return left ? left : right;
    }
};

/*
if a node can find p and q in its left and right subtrees respectively,
then this node is their lowest common ancestor
*/
```

### [509. Fibonacci Number](https://leetcode.com/problems/fibonacci-number/)

```cpp
class Solution {
public:
    int fib(int n) {
        // edge case
        if (n < 0) return -1;

        // base case
        if (n <= 1) return n;

        std::vector<int> dp(n + 1, 0);
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};
```

### [70. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)

```cpp
class Solution {
public:
    int climbStairs(int n) {
        // edge case
        if (n < 1 || n > 45) return -1;

        // base case
        if (n == 1 || n == 2) return n;

        std::vector<int> dp(n + 1, 0);
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};
```

### [88. Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/)

#### tag - too many edge cases like nums1 = [4, 5, 6, 0, 0, 0], nums2 = [1, 2, 3]

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // edge case
        if (m + n <= 0) return;

        int ptr1 = m - 1;
        int ptr2 = n - 1;
        int i = m + n -1;

        while (ptr1 >= 0 && ptr2 >= 0) {
            if (nums2[ptr2] >= nums1[ptr1]) {
                nums1[i] = nums2[ptr2];
                --ptr2;
            } else {
                nums1[i] = nums1[ptr1];
                --ptr1;
            }

            --i;
        }

        while (ptr2 >= 0) {
            nums1[i] = nums2[ptr2];
            --i;
            --ptr2;
        }
    }
};

/*
use two pointers
from the back to the front
*/
```

### [804. Unique Morse Code Words](https://leetcode.com/problems/unique-morse-code-words/)

```cpp
class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
        // edge case
        if (words.empty()) return 0;

        static const std::vector<std::string> codes = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

        std::unordered_set<std::string> uset;

        for (const auto& word: words) {
            std::string transformation;
            for (const auto ch : word) {
                transformation.append(codes[ch - 'a']);
            }
            uset.insert(transformation);
        }

        return uset.size();
    }
};
```

### [322. Coin Change](https://leetcode.com/problems/coin-change/)

#### memo

```cpp
static const int NOT_COMPUTED = -2;

class Solution {
private:
    std::vector<int> memo;

public:
    int coinChange(vector<int>& coins, int amount) {
        memo = std::vector<int>(amount + 1, NOT_COMPUTED);
        return dp(coins, amount);
    }

    int dp(vector<int>& coins, int amount) {
        // edge case
        if (amount < 0) return -1;

        // base case
        if (amount == 0) return 0;

        if (memo[amount] != NOT_COMPUTED) return memo[amount];

        int res = INT_MAX;

        for (const auto coin : coins) {
            int subRes = dp(coins, amount - coin);
            if (subRes != -1) {
                res = std::min(res, subRes + 1);
            }
        }

        memo[amount] = res != INT_MAX ? res : -1;
        return memo[amount];
    }
};
```

#### dp table

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // edge case
        if (amount < 0) return -1;

        std::vector<int> dp(amount + 1, INT_MAX - 1);
        // base case
        dp[0] = 0;
        
        for (int i = 0; i < dp.size(); ++i) {
            for (const auto coin : coins) {
                if (i < coin) continue;
                dp[i] = std::min(dp[i], dp[i - coin] + 1);
            }
        }

        return dp[amount] != (INT_MAX - 1) ? dp[amount] : -1;
    }
};
```

### [46. Permutations](https://leetcode.com/problems/permutations/)

#### tag - 最经典的回溯题目

```cpp
class Solution {
private:
    std::vector<std::vector<int>> res;

public:
    vector<vector<int>> permute(vector<int>& nums) {
        // edge case
        if (nums.empty()) return {};

        std::vector<int> path;
        std::vector<bool> used(nums.size(), false);
        backtrack(nums, path, used);
        return res;
    }

    void backtrack(const vector<int>& nums, std::vector<int>& path, std::vector<bool>& used) {
        if (path.size() == nums.size()) {
            // collect result
            res.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); ++i) {
            if (used[i]) continue;

            // make decision
            path.push_back(nums[i]);
            used[i] = true;
            backtrack(nums, path, used);
            // cancel decision
            used[i] = false;
            path.pop_back();
        }
    }
};
```

### [140. Word Break II](https://leetcode.com/problems/word-break-ii/)

```cpp
class Solution {
private:
    std::unordered_set<std::string> wordSet;
    std::unordered_map<int, std::vector<std::string>> memo;

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        wordSet.insert(wordDict.begin(), wordDict.end());
        return dfs(s, 0);
    }

    std::vector<std::string> dfs(const std::string& s, int start) {
        if (memo.count(start)) return memo[start];

        std::vector<std::string> res;

        // base
        if (start == s.size()) {
            res.push_back("");
            return res;
        }

        for (int end = start + 1; end <= s.size(); ++end) {
            auto word = s.substr(start, end - start);
            if (!wordSet.count(word)) continue;

            auto remainingWordList = dfs(s, end);

            for (const auto& remainingWord : remainingWordList) {
                res.push_back(word + (remainingWord.empty() ? "" : " ") + remainingWord);
            }
        }

        memo[start] = res;
        return memo[start];
    }
};
```

### [2. Add Two Numbers](https://leetcode.com/problems/add-two-numbers/)

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        auto dummyNode = new ListNode();
        auto current = dummyNode;
        int carry = 0;
        while (l1 || l2) {
            int val1 = l1 ? l1->val : 0;
            int val2 = l2 ? l2->val : 0;

            int sum = val1 + val2 + carry;

            carry = sum / 10;
            current->next = new ListNode(sum % 10);
            current = current->next;

            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }

        if (carry > 0) {
            current->next = new ListNode(carry);
            current = current->next;
        }

        return dummyNode->next;
    }
};
```