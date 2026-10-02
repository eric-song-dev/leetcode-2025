#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int collatzSteps(int n) {
        // edge case
        if (n <= 0) return -1;
        
        int steps = 0;
        
        while (n > 1) {
            if (n % 2 == 0) {
                n = n / 2;
            } else {
                n = 3 * n + 1;
            }

            ++steps;
        }

        return steps;
    }
};

class Solution1 {
private:
    std::unordered_map<long long, int> dp;

public:
    int collatzSteps(int n) {
        // edge case
        if (n <= 0) return -1;
        
        // initial dp table
        dp[1] = 0;
        
        return dfs(n, dp);
    }

private:
    int dfs(long long n, std::unordered_map<long long, int>& dp) {
        // base case
        if (n <= 1) return 0;

        if (dp.count(n)) return dp[n];

        if (n % 2 == 0) {
            dp[n] = dfs(n / 2, dp) + 1;
        } else {
            dp[n] = dfs(3 * n + 1, dp) + 1;
        }

        return dp[n];
    }
};

/*
Solution:
    Time Complexity: O(steps)
    Space Complexity: O(1)

Solution1:
    Time Complexity: O(steps)
    Space Complexity: O(steps)
*/

/*
int main(){
    Solution sol;
    cout << sol.collatzSteps(6) << endl; // output:8 ✔
    Solution1 sol1;
    cout << sol1.collatzSteps(6) << endl; // output:8 ✔
    return 0;
}
*/