#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<bool> rateLimit(vector<int> timestamps, int maxRequests, int windowSize) {
        // edge case
        if (timestamps.empty() || maxRequests < 1 || windowSize < 1) return {};

        const int n = timestamps.size();
        std::vector<bool> res(n, false);
        int left = 0;
        int right = 0;
        int reqNumInWindow = 0;

        while (right < n) {
            auto rightTs = timestamps[right];
            
            int currentWindowStart = (rightTs - windowSize + 1) < 1 ? 1 : (rightTs - windowSize + 1);
            int currentWindowEnd = rightTs;

            while (timestamps[left] < currentWindowStart) {
                if (res[left]) {
                    --reqNumInWindow;
                }

                ++left;
            }

            if (reqNumInWindow < maxRequests) {
                res[right] = true;
                ++reqNumInWindow;
            }

            ++right;
        }

        return res;
    }
};

/*
Time Complexity: O(n), where n is the size of timestamps
Space Complexity: O(n), where n is the size of timestamps
*/

/*
int main() {
    Solution sol;
    auto res = sol.rateLimit({1, 100, 200, 250, 350}, 2, 200);
    for (const auto it : res) {
        std::cout << it << ", ";
    }
}
*/