// tag - 这道题 union find 解法中用 unordered_map 创建 parent and size，因为 1 ≤ relations[i][j] ≤ 10^9 数据很稀疏。DFS 解法中 adjacency list 不仅可以用 std::vector<std::vector<int>> graph; 构建，如果数据比较稀疏也可以用 std::unordered_map<int, std::vector<int>> graph; 构建
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
private:
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> size;

    int find(int x) {
        if (x == parent[x]) {
            return x;
        }

        auto root = find(parent[x]);
        parent[x] = root;
        return root;
    }

    bool unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA == rootB) {
            return false;
        }

        if (size[rootA] > size[rootB]) {
            parent[rootB] = rootA;
            size[rootA] += size[rootB];
        } else {
            parent[rootA] = rootB;
            size[rootB] += size[rootA];
        }

        return true;
    }

public:
    int findLargestTreeRoot(vector<vector<int>> relations) {
        // edge case
        if (relations.empty()) {
            return -1;
        }

        std::unordered_set<int> children;
        std::unordered_set<int> rootIds;

        // initial parent and size
        for (const auto& relation : relations) {
            auto& c = relation.front();
            auto& p = relation.back();

            parent[c] = c;
            parent[p] = p;
            
            size[c] = 1;
            size[p] = 1;

            children.insert(c);
        }

        for (const auto& relation : relations) {
            auto& c = relation.front();
            auto& p = relation.back();

            unite(c, p);

            if (!children.count(p)) {
                rootIds.insert(p);
            }
        }

        int maxSize = -1;
        int resRootId = INT_MAX;

        for (const auto id : rootIds) {
            int treeSize = size[find(id)];

            if (treeSize > maxSize || (treeSize == maxSize && id < resRootId)) {
                maxSize = treeSize;
                resRootId = id;
            }
        }

        return resRootId;
    }
};

/*
Time Complexity: O(n * alpha(n)), where n is relations.size()
Space Complexity: O(n)
*/

/*
// DFS
#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int findLargestTreeRoot(vector<vector<int>> relations) {
        // edge case
        if (relations.empty()) {
            return -1;
        }

        std::unordered_set<int> children;
        std::unordered_set<int> roots;

        // build a directed adjacency list
        std::unordered_map<int, std::vector<int>> graph;
        for (const auto& relation : relations) {
            const auto child = relation.front();
            const auto parent = relation.back();

            if (!children.count(child)) {
                children.insert(child);
            }

            graph[parent].push_back(child);
        }

        for (const auto& relation : relations) {
            const auto child = relation.front();
            const auto parent = relation.back();

            if (!children.count(parent)) {
                roots.insert(parent);
            }
        }

        int maxSize = -1;
        int resRoot = INT_MAX;

        for (const auto root : roots) {
            int size = 0;
            dfs(graph, root, size);

            if (size > maxSize || (size == maxSize && root < resRoot)) {
                maxSize = size;
                resRoot = root;
            }
        }

        return resRoot;
    }

private:
    void dfs(std::unordered_map<int, std::vector<int>>& graph, int root, int& size) {
        ++size;

        for (const auto child : graph[root]) {
            dfs(graph, child, size);
        }
    }
};

/*
Time Complexity: O(V + E), where V is the size of nodes, E is relations.size
Space Complexity: O(V + E)
*/
*/