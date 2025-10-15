[TOC]

### [344. 反转字符串](https://leetcode-cn.com/problems/reverse-string/)

#### 双指针

```cpp
class Solution {
public:
    void reverseString(vector<char>& s) {
        for (int i = 0, j = s.size() - 1; i <= j; ++i, --j) {
            swap(s[i], s[j]);
        }
    }
};
```

### [541. 反转字符串 II](https://leetcode-cn.com/problems/reverse-string-ii/)

#### 没使用库函数

```cpp
class Solution {
public:
    string reverseStr(string s, int k) {
        // special case
        if (s.empty()) return "";

        int time = s.size() / (2 * k);
        int offset = 0;

        while (time--) {
            int left = offset;
            int right = left + k - 1;
            while (left < right) {
                swap(s[left], s[right]);
                ++left;
                --right;
            }

            offset += (2 * k);
        }

        int surplus = s.size() % (2 * k);
        if (surplus < k) {
            int left = offset;
            int right = left + surplus - 1;
            while (left < right) {
                swap(s[left], s[right]);
                ++left;
                --right;
            }
        } else {
            int left = offset;
            int right = left + k - 1;
            while (left < right) {
                swap(s[left], s[right]);
                ++left;
                --right;
            }
        }

        return s;
    }
};
```

#### 使用库函数（使用到下标最好使用 for(int i = 0; ...; ...) 形式的循环）

```cpp
class Solution {
public:
    string reverseStr(string s, int k) {
        for (int i = 0; i < s.size(); i += 2 * k) {
            if (s.size() - i < k) {
                std::reverse(s.begin() + i, s.end());
            } else {
                std::reverse(s.begin() + i, s.begin() + i + k);
            }
        }

        return s;
    }
};
```

### [剑指 Offer 05. 替换空格](https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof/)

#### 创建一个新对象

```cpp
class Solution {
public:
    string replaceSpace(string s) {
      	// special case
        if (s.empty()) return "";
        string res;
        for (auto ch : s) {
            if (ch == ' ') res.append("%20");
            else res.insert(res.size(), 1, ch);
        }

        return res;
    }
};
```

#### 双指针

```cpp
class Solution {
public:
    string replaceSpace(string s) {
      	// special case
        if (s.empty()) return "";
        
        int countOfSpace = 0;
        int oldSize = s.size();

        for (auto ch : s) {
            if (ch == ' ') ++countOfSpace;
        }

        if (countOfSpace == 0) return s;

        int newSize = oldSize + 2 * countOfSpace;
        s.resize(newSize);

        for (int i = oldSize - 1, j = newSize - 1; i < j; --i, --j) {
            if (s[i] == ' ') {
                s[j] = '0';
                s[--j] = '2';
                s[--j] = '%';
            } else {
                s[j] = s[i];
            }
        }

        return s;
    }
};
```

### [151. 翻转字符串里的单词](https://leetcode-cn.com/problems/reverse-words-in-a-string/)

#### 使用额外空间

```cpp
class Solution {
public:
    string reverseWords(string s) {
        string res;

        for (int i = s.size() - 1; i >= 0; --i) {
            if (s[i] != ' ') {
                string str;
                while (i >= 0 && s[i] != ' ') {
                    str.push_back(s[i]);
                    --i;
                }
                std::reverse(str.begin(), str.end());
                res.append(str);
                res.push_back(' ');
            }
        }

        if (res.size() > 0 && res.back() == ' ') res.pop_back();

        return res;
    }
};
```

#### 整体反转 + 局部反转：1. 移除多余空格 2. 将整个字符串反转 3. 将每个单词反转（建议直接看答案）

```cpp
class Solution {
public:
    // 反转字符串s中左闭又闭的区间[start, end]
    void reverse(string& s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }

    // 移除冗余空格：使用双指针（快慢指针法）O(n)的算法
    void removeExtraSpaces(string& s) {
        int slowIndex = 0, fastIndex = 0; // 定义快指针，慢指针
        // 去掉字符串前面的空格
        while (s.size() > 0 && fastIndex < s.size() && s[fastIndex] == ' ') {
            fastIndex++;
        }
        for (; fastIndex < s.size(); fastIndex++) {
            // 去掉字符串中间部分的冗余空格
            if (fastIndex - 1 > 0
                    && s[fastIndex - 1] == s[fastIndex]
                    && s[fastIndex] == ' ') {
                continue;
            } else {
                s[slowIndex++] = s[fastIndex];
            }
        }
        if (slowIndex - 1 > 0 && s[slowIndex - 1] == ' ') { // 去掉字符串末尾的空格
            s.resize(slowIndex - 1);
        } else {
            s.resize(slowIndex); // 重新设置字符串大小
        }
    }

    string reverseWords(string s) {
        removeExtraSpaces(s);
        reverse(s, 0, s.size() - 1);
        for(int i = 0; i < s.size(); i++) {
            int j = i;
            // 查找单词间的空格，翻转单词
            while(j < s.size() && s[j] != ' ') j++;
            reverse(s, i, j - 1);
            i = j;
        }
        return s;
    }
};
```

### [剑指 Offer 58 - II. 左旋转字符串](https://leetcode-cn.com/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/)

#### 使用额外空间

```cpp
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        // special case
        if (s.empty()) return "";

        string leftStr = s.substr(0, n);
        string rightStr = s.substr(n);

        return rightStr + leftStr;
    }
};
```

#### 局部反转 + 整体反转：1. 反转区间为前 n 的子串 2. 反转区间为 n 到末尾的子串 3. 反转整个字符串

```cpp
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        // special case
        if (s.empty()) return "";

        reverse(s.begin(), s.begin() + n);
        reverse(s.begin() + n, s.end());
        reverse(s.begin(), s.end());

        return s;
    }
};
```

### [28. 实现 strStr()](https://leetcode-cn.com/problems/implement-strstr/)

#### 暴力，快慢指针 O(n * m)

```cpp
class Solution {
public:
    int strStr(string haystack, string needle) {
        // edge case
        if (haystack.empty() || needle.empty()) return -1;

        int slow = 0;
        for (int fast = 0; fast < haystack.size(); ++fast) {
            if (haystack[fast] == needle[0]) {
                slow = fast;
                int i = 1;
                while (fast + i < haystack.size() && haystack[fast + i] == needle[i]) {
                    ++i;
                }
                if (i == needle.size()) {
                    return slow;
                }
            }
        }

        return -1;
    }
};
```

#### KMP，现在不会，需要多做

```cpp
```

### [459. 重复的子字符串](https://leetcode-cn.com/problems/repeated-substring-pattern/)

#### 暴力枚举法

```cpp
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        // special case
        if (s.empty()) return true;

        for (int i = 1; i * 2 <= s.size(); ++i) {
            if (s.size() % i == 0) {
                bool match = true;

                for (int j = i; j != s.size(); ++j) {
                    if (s[j] != s[j - i]) {
                        match = false;
                        break;
                    }
                }

                if (match) return true;
            }
        }

        return false;
    }
};
```

#### KMP，现在不会，需要多做

```cpp
```

