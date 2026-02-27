#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // DFS helper — climbs uphill from ocean border
    void dfs(vector<vector<int>>& heights, vector<vector<bool>>& visited,
             int r, int c, int prevHeight) {

        int rows = heights.size();
        int cols = heights[0].size();

        // TODO 1: bounds check → return
        if(r< 0 || r >= rows || c < 0 || c >= cols ) return; 

        // TODO 2: already visited → return
        if(visited[r][c]) return;

        // TODO 3: height check → return if heights[r][c] < prevHeight
        if(heights[r][c] < prevHeight) return; // can't climb here — too low

        // TODO 4: mark visited
        visited[r][c] = true; 

        // TODO 5: recurse in 4 directions (pass heights[r][c] as prevHeight)
        dfs(heights, visited, r-1, c, heights[r][c]);
        dfs(heights, visited, r+1, c, heights[r][c]);
        dfs(heights, visited, r, c-1, heights[r][c]);
        dfs(heights, visited, r, c+1, heights[r][c]);

    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int R = heights.size();
        int C = heights[0].size();

        vector<vector<bool>> pacific(R, vector<bool>(C, false));
        vector<vector<bool>> atlantic(R, vector<bool>(C, false));

        // TODO 6: seed Pacific DFS from top row + left col
        for(int c=0; c < C; c++)
            dfs(heights, pacific, 0, c, 0);
        for(int r=0; r < R; r++)
            dfs(heights, pacific, r, 0, 0);

        // TODO 7: seed Atlantic DFS from bottom row + right col
        for(int c=0; c < C; c++)
            dfs(heights, atlantic, R-1, c, 0);
        for(int r=0; r < R; r++)
            dfs(heights, atlantic, r, C-1, 0);

        // TODO 8: collect cells reachable by BOTH
        vector<vector<int>> result;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                // if pacific[r][c] AND atlantic[r][c] → add {r,c} to result
                if(pacific[r][c] && atlantic[r][c])
                    result.push_back({r, c});
            }
        }
        return result;
    }
};

int main() {
    Solution sol;

    // Test 1: expected = [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
    vector<vector<int>> heights = {
        {1, 2, 2, 3, 5},
        {3, 2, 3, 4, 4},
        {2, 4, 5, 3, 1},
        {6, 7, 1, 4, 5},
        {5, 1, 1, 2, 4}
    };

    auto result = sol.pacificAtlantic(heights);
    cout << "Result cells:" << endl;
    for (auto& cell : result) {
        cout << "[" << cell[0] << "," << cell[1] << "] ";
    }
    cout << endl;

    return 0;
}
