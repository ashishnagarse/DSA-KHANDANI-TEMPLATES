# **BFS on Matrix (Generic Template) 🚀**

This repository contains a **generic BFS template** for traversing a **2D grid (matrix)** using **4-directional** and **8-directional** movement. BFS is commonly used in pathfinding, connected components detection, and shortest path problems.

---

## **📌 Features**
✅ **Works on any 2D grid (matrix)**  
✅ **Supports both 4-directional and 8-directional movement**  
✅ **Prevents revisiting nodes using a `visited` array**  
✅ **Handles obstacles (`grid[x][y] == 1`)**  
✅ **Boundary check to prevent out-of-bounds errors**  

---

## **🚀 BFS Implementation in C++**
```cpp
#include <bits/stdc++.h>
using namespace std;

// 4-directional movement (Up, Down, Left, Right)
vector<pair<int, int>> directions4 = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 8-directional movement (Up, Down, Left, Right, and diagonals)
vector<pair<int, int>> directions8 = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

void bfs(vector<vector<int>> &grid, int startX, int startY) {
    int n = grid.size();
    int m = grid[0].size();

    queue<pair<int, int>> q;
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    // Start BFS
    q.push({startX, startY});
    visited[startX][startY] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        cout << "Visiting: (" << x << ", " << y << ")\n";

        // Move in 4 directions (change to directions8 for 8-way movement)
        for (auto [dx, dy] : directions4) {
            int newX = x + dx, newY = y + dy;

            // Check if the new position is within bounds and not visited
            if (newX >= 0 && newX < n && newY >= 0 && newY < m && !visited[newX][newY] && grid[newX][newY] == 0) {
                q.push({newX, newY});
                visited[newX][newY] = true;
            }
        }
    }
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}
    };

    int startX = 0, startY = 0; // Starting point of BFS
    bfs(grid, startX, startY);

    return 0;
}

