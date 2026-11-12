#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    int evaluate(string expression) {
        // edge case
        if (expression.empty()) {
            return 0;
        }

        std::stack<long long> nums;
        std::stack<char> ops;
        int n = expression.size();

        for (int i = 0; i < n; ++i) {
            if (std::isdigit(expression[i])) {
                long long num = 0;
                while (i < n && std::isdigit(expression[i])) {
                    num = num * 10 + (expression[i] - '0');
                    ++i;
                }

                --i;
                nums.push(num);
            } else if (expression[i] == '-') {
                ++i;

                long long num = 0;
                while (i < n && std::isdigit(expression[i])) {
                    num = num * 10 + (expression[i] - '0');
                    ++i;
                }

                --i;
                nums.push(-num);
            } else if (expression[i] == 'a') {
                ops.push('+');
                i += 2;
            } else if (expression[i] == 's') {
                ops.push('-');
                i += 2;
            } else if (expression[i] == '(') {
                // do nothing
            } else if (expression[i] == ')') {
                long long res = 0;
                auto secondNum = nums.top();
                nums.pop();
                auto firstNum = nums.top();
                nums.pop();
                auto operation = ops.top();
                ops.pop();

                if (operation == '+') {
                    res = firstNum + secondNum;
                } else if (operation == '-') {
                    res = firstNum - secondNum;
                }

                nums.push(res);
            }
        }

        return static_cast<int>(nums.top());
    }
};

/*
Time Complexity: O(n)
Space Complexity: O(n)
*/
