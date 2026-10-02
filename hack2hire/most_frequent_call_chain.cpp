#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
private:
    static inline const std::string FUNCTION_CALL = "->";
    static inline const std::string FUNCTION_RETURN = "<-";

public:
    vector<string> findMostFrequentCallStack(vector<string> traces) {
        // edge case
        if (traces.empty()) return {};

        std::stack<std::string> stk;
        std::string currentCallChain;
        std::unordered_map<std::string, std::pair<int, int>> umap; // key: call chain, value: <frequency, depth>

        int depth = 0;
        for (const auto& function : traces) {
            auto functionType = function.substr(0, 2);
            auto functionName = function.substr(3);

            if (functionType == FUNCTION_CALL) {
                stk.push(function);
                currentCallChain.append(function + " ");
                ++depth;
            } else if (functionType == FUNCTION_RETURN) {
                if (stk.empty()) {
                    continue;
                }

                auto preFunction = stk.top();
                auto preFunctionType = preFunction.substr(0, 2);
                auto preFunctionName = preFunction.substr(3);

                if (preFunctionName != functionName) {
                    continue;
                }

                stk.pop();

                if (umap.count(currentCallChain)) {
                    ++umap[currentCallChain].first;
                } else {
                    umap[currentCallChain] = {1, depth};
                }

                --depth;

                auto pos = currentCallChain.rfind(FUNCTION_CALL);
                if (pos != std::string::npos) {
                    currentCallChain.erase(pos);
                }
            }
        }

        if (umap.empty()) return {};

        auto maxIt = std::max_element(umap.begin(), umap.end(), [](const auto& a, const auto& b) {
            if (a.second.first != b.second.first) {
                return a.second.first < b.second.first;
            } else {
                return a.second.second < b.second.second;
            }
        });

        std::string callChain = maxIt->first;

        callChain = callChain.substr(3); // delete first "-> "
        callChain.pop_back(); // delete last " "

        std::vector<std::string> res;
        res.push_back(callChain);
        res.push_back(std::to_string(maxIt->second.first));

        return res;
    }
};

/*
Time Complexity: O(n * L), where n is traces.size(), L is average callChain.size()
Space Complexity: O(n * L), where n is traces.size(), L is average callChain.size()
*/

/*
int main() {
    Solution sol;
    auto res = sol.findMostFrequentCallStack({"-> func","<- func","-> func","<- func","-> func","<- func"});
    for (const auto it : res) {
        std::cout << it << ", ";
    }
}
*/