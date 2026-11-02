#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<string> findOriginals(string encoded) {
        // edge case
        if (encoded.size() <= 1) {
            return {};
        }

        std::vector<std::string> res;
        std::string path;

        backtrack(encoded, res, path, 0);

        return res;
    }

    void backtrack(const std::string& encoded,
                   std::vector<std::string>& res,
                   std::string& path,
                   int startIndex) {
        const int n = encoded.size();

        // collect results
        if (startIndex == n) {
            res.push_back(path);
            return;
        }

        if (encoded[startIndex] == '0') {
            return;
        }

        if (startIndex + 1 >= n) {
            return;
        }

        if (startIndex + 1 < n) {
            // make decision
            int count = encoded[startIndex] - '0';
            char num = encoded[startIndex + 1];
            path.append(count, num);

            backtrack(encoded, res, path, startIndex + 2);

            // cancel decision
            path.erase(path.size() - count);
        }

        if (startIndex + 2 < n) {
            // make decision
            int count = (encoded[startIndex] - '0') * 10 + (encoded[startIndex + 1] - '0');
            char num = encoded[startIndex + 2];
            path.append(count, num);

            backtrack(encoded, res, path, startIndex + 3);

            // cancel decision
            path.erase(path.size() - count);
        }
    }
};

/*
Time Complexity: O(n * 2^(n / 2))
Space Complexity: O(k * res.size()), where k is the average size of path
*/
