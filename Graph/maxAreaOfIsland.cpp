#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int dfs(vector<vector<char>>& grid, int r, int c) {
        
        
        int rows = grid.size();
        int cols = grid[0].size();

        if(r<0 || r>=rows || c<0 || c >= cols) return 0;
       
        if( grid[r][c] == '0') return 0;        
        
        grid[r][c] = '0';
        
        return 1+ dfs(grid, r+1, c) + dfs(grid, r-1, c) + dfs(grid, r, c+1)+ dfs(grid, r, c-1);
    }

    int maxAreaOfIsland(vector<vector<char>>& grid) {
        int maxArea = 0;

        for(int r=0; r<grid.size(); r++)
        {
            for(int c=0; c< grid[0].size(); c++)
            {
                if(grid[r][c] == '1')
                {
                    int area = dfs(grid, r , c);
                    maxArea = max(maxArea, area);

                }
            }   
        }
        return maxArea;
    }
};

int main() {
    Solution sol;

    // Test 1: max area = 4
    vector<vector<char>> grid1 = {
        {'0','0','1','0','0'},
        {'0','0','1','0','0'},
        {'0','0','1','1','0'},
        {'0','0','0','0','0'}
    };
    cout << "Test 1 (expected 4): " << sol.maxAreaOfIsland(grid1) << endl;

    // Test 2: max area = 6
    vector<vector<char>> grid2 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    cout << "Test 2 (expected 4): " << sol.maxAreaOfIsland(grid2) << endl;

    // Test 3: all water
    vector<vector<char>> grid3 = {
        {'0','0','0'},
        {'0','0','0'}
    };
    cout << "Test 3 (expected 0): " << sol.maxAreaOfIsland(grid3) << endl;

    return 0;
}
