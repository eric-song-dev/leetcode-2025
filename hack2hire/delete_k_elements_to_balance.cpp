#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    int findSmallestIndex(vector<int> nums, int k) {
        // edge case
        if (nums.empty() || k < 1 || k > nums.size()) return -1;

        const int windowSize = k;
        const int n = nums.size();
        std::vector<long long> evenPreSum(n + 1, 0);
        std::vector<long long> oddPreSum(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            evenPreSum[i + 1] = evenPreSum[i];
            oddPreSum[i + 1] = oddPreSum[i];

            if (i % 2 == 0) {
                evenPreSum[i + 1] += nums[i];
            } else {
                oddPreSum[i + 1] += nums[i];
            }
        }

        for (int left = 0; left + windowSize <= n; ++left) {
            // [left, rightStart - 1]
            int rightStart = left + windowSize;

            long long leftEvenSum = evenPreSum[left];
            long long leftOddSum = oddPreSum[left];

            long long rightEvenSum = evenPreSum[n] - evenPreSum[rightStart];
            long long rightOddSum = oddPreSum[n] - oddPreSum[rightStart];

            if (windowSize % 2 != 0) {
                // swap even and odd in right side
                std::swap(rightEvenSum, rightOddSum);
            }

            if (leftEvenSum + rightEvenSum == leftOddSum + rightOddSum) {
                return left;
            }
        }

        return -1;
    }
};

/*
Time Complexity: O(n), where n is nums.size()
Space Complexity: O(n), where n is nums.size()
*/
