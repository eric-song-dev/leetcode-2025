/*
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
private:
    std::vector<int> res;
    int curIndex = 0;

public:
    Solution(const vector<int>& a, const vector<int>& b) {
        res.reserve(b.size() + a.size());
        
        std::unordered_set<int> visited;

        for (const auto num : b) {
            res.push_back(num);
            visited.insert(num);
        }

        for (const auto num : a) {
            if (visited.count(num)) {
                continue;
            }

            res.push_back(num);
        }
    }

    bool hasNext() {
        return curIndex < res.size();
    }

    int next() {
        if (!hasNext()) {
            throw out_of_range("Out of Range");
        }

        return res[curIndex++];
    }
};

int main() {
    vector<int> a1 = {1, 2, 3, 4, 5};
    vector<int> b1 = {3, 5};
    Solution iter1(a1, b1);
    cout << "Test Case 1: ";
    while (iter1.hasNext()) {
        cout << iter1.next() << " ";
    }
    cout << endl; // Expected output: 3 5 1 2 4

    vector<int> a2 = {10, 20, 30, 40};
    vector<int> b2 = {20, 50};
    Solution iter2(a2, b2);
    cout << "Test Case 2: ";
    while (iter2.hasNext()) {
        cout << iter2.next() << " ";
    }
    cout << endl; // Expected output: 20 50 10 30 40

    vector<int> a3 = {7, 8, 9};
    vector<int> b3 = {1, 2, 3};
    Solution iter3(a3, b3);
    cout << "Test Case 3: ";
    while (iter3.hasNext()) {
        cout << iter3.next() << " ";
    }
    cout << endl; // Expected output: 1 2 3 7 8 9

    vector<int> a4 = {1, 1, 2, 2};
    vector<int> b4 = {2, 2};
    Solution iter4(a4, b4);
    cout << "Test Case 4: ";
    while (iter4.hasNext()) {
        cout << iter4.next() << " ";
    }
    cout << endl; // Expected output: 2 2 1 1

    return 0;
}
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
private:
    const vector<int>& a;
    const vector<int>& b;
    std::unordered_set<int> visited;
    int i = 0;
    int j = 0;

public:
    Solution(const vector<int>& a, const vector<int>& b) : a(a), b(b) {
        for (const auto num : b) {
            visited.insert(num);
        }
    }

    bool hasNext() {
        if (j < b.size()) {
            return true;
        }

        while (i < a.size() && visited.count(a[i])) {
            ++i;
        }

        return i < a.size();
    }

    int next() {
        if (!hasNext()) {
            throw out_of_range("Out of Range");
        }

        if (j < b.size()) {
            return b[j++];
        }

        return a[i++];
    }
};

int main() {
    vector<int> a1 = {1, 2, 3, 4, 5};
    vector<int> b1 = {3, 5};
    Solution iter1(a1, b1);
    cout << "Test Case 1: ";
    while (iter1.hasNext()) {
        cout << iter1.next() << " ";
    }
    cout << endl; // Expected output: 3 5 1 2 4

    vector<int> a2 = {10, 20, 30, 40};
    vector<int> b2 = {20, 50};
    Solution iter2(a2, b2);
    cout << "Test Case 2: ";
    while (iter2.hasNext()) {
        cout << iter2.next() << " ";
    }
    cout << endl; // Expected output: 20 50 10 30 40

    vector<int> a3 = {7, 8, 9};
    vector<int> b3 = {1, 2, 3};
    Solution iter3(a3, b3);
    cout << "Test Case 3: ";
    while (iter3.hasNext()) {
        cout << iter3.next() << " ";
    }
    cout << endl; // Expected output: 1 2 3 7 8 9

    vector<int> a4 = {1, 1, 2, 2};
    vector<int> b4 = {2, 2};
    Solution iter4(a4, b4);
    cout << "Test Case 4: ";
    while (iter4.hasNext()) {
        cout << iter4.next() << " ";
    }
    cout << endl; // Expected output: 2 2 1 1

    return 0;
}
