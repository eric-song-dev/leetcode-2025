#include <vector>
#include <string>
#include <iostream>
#include <climits>
#include <queue>
using namespace std;

class Solution {
public:
    string findOptimalCommute(vector<vector<char>> grid, vector<string> modes, vector<int> costs, vector<int> times) {
        const int m = grid.size();
        const int n = grid[0].size();
        const int k = modes.size();

        int sX = 0;
        int sY = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'S') {
                    sX = i;
                    sY = j;
                    break;
                }
            }
        }

        static const std::vector<std::pair<int, int>> directions = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}
        };

        int minCost = INT_MAX;
        int minTime = INT_MAX;
        std::string minMode;

        for (int i = 0; i < k; ++i) {
            auto mode = modes[i];
            char modeDigit = i + '1';
            int step = 0;
            bool accessD = false;

            std::queue<std::pair<int, int>> q;
            q.push({sX, sY});

            while (!q.empty()) {
                auto size = q.size();

                while (size--) {
                    auto current = q.front();
                    q.pop();

                    for (const auto& [dx, dy] : directions) {
                        int nextX = current.first + dx;
                        int nextY = current.second + dy;

                        if (nextX < 0 || nextX >= m ||
                            nextY < 0 || nextY >= n) {
                            continue;
                        }

                        if (grid[nextX][nextY] != modeDigit && grid[nextX][nextY] != 'D') {
                            continue;
                        }

                        if (grid[nextX][nextY] == 'D') {
                            accessD = true;
                            break;
                        }

                        q.push({nextX, nextY});
                        grid[nextX][nextY] = 'X';
                    }

                    if (accessD) {
                        break;
                    }
                }

                ++step;

                if (accessD) {
                    break;
                }
            }

            if (!accessD) {
                continue;
            }

            int totalCost = costs[i] * step;
            int totalTime = times[i] * step;

            if (totalTime < minTime || (totalTime == minTime && totalCost < minCost)) {
                minCost = totalCost;
                minTime = totalTime;
                minMode = mode;
            }
        }

        return minMode;
    }
};

/*
Time Complexity: O(k * 4 * m * n) = O(k * m * n)
Space Complexity: O(m * n)
*/
