#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void dfs(vector<vector<char>>& grid, int r, int c) {
        int row = grid.size();
        int cols = grid[0].size();
        // Step 1: bounds check
        if (r < 0 || r >= row || c < 0 || c >= cols) return;
        // Step 2: water check
        if (grid[r][c] == '0') return;
        // Step 3: mark visited
        grid[r][c] = '0';
        // Step 4: explore 4 directions
        dfs(grid, r+1, c);
        dfs(grid, r-1, c);
        dfs(grid, r, c+1);
        dfs(grid, r, c-1);
    }

    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[0].size(); c++) {
                if (grid[r][c] == '1') {
                    dfs(grid, r, c);
                    count++;
                }
            }
        }
        return count;
    }
};

int main() {
    Solution sol;

    // Test 1: 3 islands
    vector<vector<char>> grid1 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    cout << "Test 1 (expected 3): " << sol.numIslands(grid1) << endl;

    // Test 2: 1 island
    vector<vector<char>> grid2 = {
        {'1','1','1'},
        {'0','1','0'},
        {'1','1','1'}
    };
    cout << "Test 2 (expected 1): " << sol.numIslands(grid2) << endl;

    // Test 3: all water
    vector<vector<char>> grid3 = {
        {'0','0','0'},
        {'0','0','0'}
    };
    cout << "Test 3 (expected 0): " << sol.numIslands(grid3) << endl;

    return 0;
}