#include <bits/stdc++.h>
using namespace std;

/**
 * Time Complexity (TC):
 * - Building the adjacency list: O(E)
 * - BFS traversal: O(V + E) (each node and edge is visited once)
 * - Overall Complexity: O(V + E)
 *
 * Space Complexity (SC):
 * - Adjacency List Storage: O(V + E)
 * - Visited Array: O(V)
 * - Queue for BFS: O(V) (in the worst case)
 * - Total Space Complexity: O(V + E)
 */

class Solution {
public:
    /**
     * Detects a cycle in an undirected graph using BFS.
     * 
     * @param adj Adjacency list representation of the graph.
     * @param visited Boolean array to track visited nodes.
     * @param start Starting node for BFS.
     * @return True if a cycle is detected, otherwise false.
     */
    bool isCycleBFS(vector<vector<int>>& adj, vector<bool>& visited, int start) {
        queue<pair<int, int>> q; // Queue stores {node, parent}
        q.push({start, -1});
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front().first;
            int parent = q.front().second;
            q.pop();

            // Traverse all adjacent nodes
            for (auto& neighbor : adj[node]) {
                if (!visited[neighbor]) {  // If neighbor is not visited, push to queue
                    visited[neighbor] = true;
                    q.push({neighbor, node});
                } else if (neighbor != parent) {  
                    // If visited and not parent, a cycle is detected
                    return true;
                }
            }
        }
        return false;  // No cycle found
    }

    /**
     * Checks if an undirected graph contains a cycle using BFS.
     * 
     * @param V Number of vertices in the graph.
     * @param edges List of edges representing the graph.
     * @return True if the graph contains a cycle, otherwise false.
     */
    bool isCycle(int V, vector<vector<int>>& edges) {
        vector<bool> visited(V, false);  // Tracks visited nodes
        vector<vector<int>> adj(V);  // Adjacency list representation of the graph

        // Construct adjacency list from the given edges
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Check for cycles in each connected component
        for (int i = 0; i < V; i++) {
            if (!visited[i] && isCycleBFS(adj, visited, i)) {
                return true;  // Cycle detected
            }
        }
        return false;  // No cycle found in any component
    }
};

// Driver Code
int main() {
    Solution sol;
    int V = 3;  // Number of vertices
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}};  // List of edges

    cout << (sol.isCycle(V, edges) ? "true" : "false") << endl;
    return 0;
}
