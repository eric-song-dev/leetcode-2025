[TOC]

### [242. 有效的字母异位词](https://leetcode-cn.com/problems/valid-anagram/)

```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        // edge case
        if (s.size() != t.size()) return false;

        std::unordered_map<char, int> charToNumMap;

        for (const auto& ch : s) {
            ++charToNumMap[ch];
        }

        for (const auto& ch : t) {
            --charToNumMap[ch];
        }

        for (const auto& pair : charToNumMap) {
            if (pair.second != 0) return false;
        }

        return true;
    }
};
```

### [349. 两个数组的交集](https://leetcode-cn.com/problems/intersection-of-two-arrays/)

```cpp
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        // edge case
        if (nums1.empty() || nums2.empty()) return {};

        std::unordered_set<int> numSet(nums1.begin(), nums1.end());
        std::unordered_set<int> resSet;

        for (const auto& num : nums2) {
            if (numSet.count(num)) {
                resSet.insert(num);
            }
        }

        std::vector<int> res(resSet.begin(), resSet.end());
        return res;
    }
};
```

### [202. 快乐数](https://leetcode-cn.com/problems/happy-number/)

```cpp
class Solution {
public:
    bool isHappy(int n) {
        // edge case
        if (n < 1) return false;
        std::unordered_set<int> numSet;

        while (true) {
            int sum = 0;
            for ( ; n > 0; n /= 10) {
                
                sum += std::pow(n % 10, 2);
                
            }
            if (sum == 1) return true;
            
            if (numSet.count(sum)) return false;
            else numSet.insert(sum);
            
            n = sum;
        }

        return true;
    }
};
```

### [1. 两数之和](https://leetcode-cn.com/problems/two-sum/)

#### 双循环嵌套（性能差）

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // edge case
        if (nums.empty()) return {};

        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                if (nums[i] + nums[j] == target) return {i, j};
            }
        }

        return {};
    }
};
```

#### Hash Table

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // edge case
        if (nums.empty()) return {};

        std::unordered_map<int, int> umap;

        for (int i = 0; i < nums.size(); ++i) {
            if (umap.count(target - nums[i])) return {i, umap[target - nums[i]]};
            else umap.insert({nums[i], i});
        }

        return {};
    }
};
```

### [454. 四数相加 II](https://leetcode-cn.com/problems/4sum-ii/)

```cpp
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        int res = 0;
        std::unordered_map<int, int> umap;

        for (const auto& num1 : nums1) {
            for (const auto& num2: nums2) {
                ++umap[num1 + num2];
            }
        }

        for (const auto& num3 : nums3) {
            for (const auto& num4: nums4) {
                if (umap.count(- num3 - num4)) res += umap[- num3 - num4];
            }
        }

        return res;
    }
};
```

### [383. 赎金信](https://leetcode-cn.com/problems/ransom-note/)

```cpp
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        // edge case
        if (ransomNote.empty() && magazine.empty()) return true;
        else if (ransomNote.empty() || magazine.empty()) return false;

        std::unordered_map<char, int> umap;

        for (const auto& ch : magazine) {
            ++umap[ch];
        }

        for (const auto& ch : ransomNote) {
            --umap[ch];

            if (umap[ch] < 0) return false;
        }

        return true;
    }
};
```

### [15. 三数之和](https://leetcode-cn.com/problems/3sum/)

#### Hash Table(Time Limit Exceeded, bad solution...)

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // edge case
        if (nums.size() < 3) return {{}};

        vector<vector<int>> res;
        std::set<std::vector<int>> toDuplicateRes;
        std::set<std::vector<int>> indexTriplets;
        // key: nums[i] + nums[j], value: {i, j}
        std::unordered_multimap<int, std::unordered_set<int>> umap;

        for (int i = 0; i < nums.size() - 1; ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                umap.insert({nums[i] + nums[j], {i, j}});
            }
        }

        for (int k = 0; k < nums.size(); ++k) {
            if (umap.count(- nums[k])) {
                auto range = umap.equal_range(-nums[k]);
                for (auto it = range.first; it != range.second; ++it) {
                    if (!it->second.count(k)) {
                        std::vector<int> indexTriplet;
                        indexTriplet.push_back(k);
                        for (const auto& index : it->second) {
                            indexTriplet.push_back(index);
                        }
                        std::sort(indexTriplet.begin(), indexTriplet.end());
                        indexTriplets.insert(indexTriplet);
                    }
                }
            }
        }

        for (const auto& indexTriplet : indexTriplets) {
            std::vector<int> numTriplet;
            for (const auto& index : indexTriplet) {
                numTriplet.push_back(nums[index]);
            }
            std::sort(numTriplet.begin(), numTriplet.end());
            toDuplicateRes.insert(numTriplet);
        }

        for (const auto& numTriplet : toDuplicateRes) {
            res.push_back(numTriplet);
        }

        return res;
    }
};
```


#### 双指针

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // edge case
        if (nums.size() < 3) return {{}};

        vector<vector<int>> res;

        std::sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > 0) return res;

            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right) {
                auto sum = nums[i] + nums[left] + nums[right];
                if (sum == 0) {
                    res.push_back({nums[i], nums[left], nums[right]});

                    while (left < right && nums[right - 1] == nums[right]) --right;
                    while (left < right && nums[left + 1] == nums[left]) ++left;

                    --right;
                    ++left;
                } else if (sum > 0) {
                    --right;
                } else /* if (sum < 0) */ {
                    ++left;
                }
            }
        }

        return res;
    }
};
```

### [18. 四数之和](https://leetcode-cn.com/problems/4sum/)

#### 抄答案的

```cpp
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int k = 0; k < nums.size(); k++) {
            // 这种剪枝是错误的，这道题目target 是任意值
            // if (nums[k] > target) {
            //     return result;
            // }
            // 去重
            if (k > 0 && nums[k] == nums[k - 1]) {
                continue;
            }
            for (int i = k + 1; i < nums.size(); i++) {
                // 正确去重方法
                if (i > k + 1 && nums[i] == nums[i - 1]) {
                    continue;
                }
                int left = i + 1;
                int right = nums.size() - 1;
                while (right > left) {
                    // nums[k] + nums[i] + nums[left] + nums[right] > target 会溢出
                    if (nums[k] + nums[i] > target - (nums[left] + nums[right])) {
                        right--;
                    } else if (nums[k] + nums[i] < target - (nums[left] + nums[right])) {
                        left++;
                    } else {
                        result.push_back(vector<int>{nums[k], nums[i], nums[left], nums[right]});
                        // 去重逻辑应该放在找到一个四元组之后
                        while (right > left && nums[right] == nums[right - 1]) right--;
                        while (right > left && nums[left] == nums[left + 1]) left++;

                        // 找到答案时，双指针同时收缩
                        right--;
                        left++;
                    }
                }

            }
        }
        return result;
    }
};
```

