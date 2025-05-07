class Solution {
  public:
    void floydWarshall(vector<vector<int>> &dist) {
        int n = dist.size();            // Number of nodes in the graph
        const int INF = 1e8;            // A large number representing "infinity" (used to indicate no direct path)

        // The Floyd-Warshall algorithm checks for every possible pair of vertices (i, j),
        // if going through an intermediate vertex 'via' provides a shorter path.
        for (int via = 0; via < n; via++) {            // Try every node as an intermediate node
            for (int i = 0; i < n; i++) {              // For every starting node i
                for (int j = 0; j < n; j++) {          // For every destination node j

                    // Only update if both parts of the path exist
                    // i.e., path from i to via and via to j are not "infinity"
                    if (dist[i][via] < INF && dist[via][j] < INF) {
                        // Update the distance from i to j if the path through 'via' is shorter
                        dist[i][j] = min(dist[i][j], dist[i][via] + dist[via][j]);
                    }
                }
            }
        }
    }
};



/*
### 🔍 **Floyd-Warshall Algorithm: Overview**

The **Floyd-Warshall algorithm** is a classic **dynamic programming** algorithm used to find the **shortest paths between all pairs of vertices** in a weighted graph.

#### ✅ **Key Features:**

* Works on **directed or undirected graphs**
* Handles **positive and negative edge weights**
* **Does not work** if there is a **negative weight cycle**
* Time complexity: **O(n³)** where `n` is the number of vertices

---

### 🧠 **Core Idea:**

For every pair of vertices `(i, j)`, we check whether there is a **shorter path** through an intermediate vertex `k`.

We update:

```
dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
```

---

### 📘 **Example:**

Let's consider the following directed graph with 4 nodes (0 to 3):

```
      (0)
     /   \
    5     10
   /       \
 (1)———1——→(2)
   \        /
    \___7__/
       (3)
```

#### Input adjacency matrix (`INF = 1e8` to denote no path):

```cpp
vector<vector<int>> dist = {
    {0,    5,    10,   INF},
    {INF,  0,     1,    7  },
    {INF, INF,   0,    INF},
    {INF, INF,   2,     0 }
};
```

#### After applying Floyd-Warshall:

```cpp
vector<vector<int>> dist = {
    {0,    5,    6,    12},
    {INF,  0,    1,     7},
    {INF, INF,  0,    INF},
    {INF, INF,  2,     0}
};
```

➡️ For example, shortest path from `0 → 2`:

* Originally: 10
* Through node 1: `0 → 1 (5)` and `1 → 2 (1)` = **6**

---

### 🛑 **Negative Cycle Detection (optional):**

After running the algorithm, if any `dist[i][i] < 0`, then the graph has a **negative weight cycle**.

Would you like me to include code for detecting negative cycles as well?
*/
