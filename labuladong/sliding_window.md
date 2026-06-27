[TOC]

**The sliding window algorithm is mainly used to solve subarray problems, such as finding the longest or shortest subarray that meets certain conditions.**

With this template, if you get a substring or subarray problem, just answer these three questions:

1. When should you move right to expand the window? What data should you update when adding a character to the window?
2. When should you stop expanding and start moving left to shrink the window? What data should you update when removing a character from the window?
3. When should you update the result?

```cpp
// 滑动窗口算法伪码框架
void slidingWindow(string s) {
    // 用合适的数据结构记录窗口中的数据，根据具体场景变通
    // 比如说，我想记录窗口中元素出现的次数，就用 map
    // 如果我想记录窗口中的元素和，就可以只用一个 int
    auto window = ...

    int left = 0, right = 0;
    while (right < s.size()) {
        // c 是将移入窗口的字符
        char c = s[right];
        // 增大窗口
        right++;

        // flip side A: 进行窗口内数据的一系列更新 like ++window[c];
        ...

        // 这儿可能可以做一些事，如果有些结果是在窗口收缩前完成

        // *** debug 输出的位置 ***
        printf("window: [%d, %d)\n", left, right);
        // 注意在最终的解法代码中不要 print
        // 因为 IO 操作很耗时，可能导致超时

        // 判断左侧窗口是否要收缩
        while (window needs shrink) {
            // 这儿可以做一些事，如果有些结果是在窗口收缩时完成

            // d 是将移出窗口的字符
            char d = s[left];
            // 缩小窗口
            left++;

            // flip side B: 进行窗口内数据的一系列更新 like --window[c];
            ...
        }

        // 这儿依旧可以做一些事，如果有些结果是在窗口收缩后才完成
    }
}
```

### [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/description/)

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        // edge case
        if (s.empty() || t.empty()) return "";

        std::unordered_map<char, int> need, window;
        for (const auto ch : t) {
            ++need[ch];
        }

        // [left, right)
        int left = 0, right = 0;
        int chMatchNum = 0;
        int start = 0, len = INT_MAX;
        string res;

        while (right < s.size()) {
            const auto rch = s[right];
            ++right;

            if (need.count(rch)) {
                ++window[rch];
                if (window[rch] == need[rch]) {
                    ++chMatchNum;
                }
            }

            while (chMatchNum == need.size()) {
                if (right - left < len) {
                    start = left;
                    len = right - left;
                }

                const auto lch = s[left];
                ++left;

                if (need.count(lch)) {
                    if (window[lch] == need[lch]) {
                        --chMatchNum;
                    }
                    --window[lch];
                }
            }
        }

        return len == INT_MAX ? "" : s.substr(start, len);
    }
};
```

### [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/description/)

```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        // edge case
        if (s1.empty() || s2.empty()) return false;

        std::unordered_map<char, int> need, window;
        for (const auto ch : s1) {
            ++need[ch];
        }

        // [left, right)
        int left = 0, right = 0;
        int chMatchNum = 0;

        while (right < s2.size()) {
            const auto rch = s2[right];
            ++right;

            if (need.count(rch)) {
                ++window[rch];
                if (need[rch] == window[rch]) {
                    ++chMatchNum;
                }
            }

            while (chMatchNum == need.size()) {
                if (right - left == s1.size()) return true;

                const auto lch = s2[left
                ++left;

                if (need.count(lch)) {
                    if (need[lch] == window[lch]) {
                        --chMatchNum;
                    }
                    --window[lch];
                }
            }
        }

        return false;
    }
};
```

### [438. Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/description/)

```cpp
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        // edge case
        if (s.empty() || p.empty()) return {};

        std::unordered_map<char, int> need, window;
        for (const auto ch : p) {
            ++need[ch];
        }

        // [left, right)
        int left = 0, right = 0;
        int chMatchNum = 0;
        vector<int> res;

        while (right < s.size()) {
            const auto rch = s[right];
            ++right;

            if (need.count(rch)) {
                ++window[rch];
                if (need[rch] == window[rch]) {
                    ++chMatchNum;
                }
            }

            while (chMatchNum == need.size()) {
                if (right - left == p.size()) {
                    res.push_back(left);
                }

                const auto lch = s[left];
                ++left;

                if (need.count(lch)) {
                    if (need[lch] == window[lch]) {
                        --chMatchNum;
                    }
                    --window[lch];
                }
            }
        }

        return res;
    }
};
```

### [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/description/)

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // edge
        if (s.empty()) return 0;

        std::unordered_map<char, int> window;

        // [left, right)
        int left = 0, right = 0;
        int res = 0;

        while (right < s.size()) {
            const auto rch = s[right];
            ++right;

            ++window[rch];

            while (window[rch] > 1) {
                const auto lch = s[left];
                ++left;

                --window[lch];
            }

            res = std::max(res, right - left);
        }

        return res;
    }
};
```