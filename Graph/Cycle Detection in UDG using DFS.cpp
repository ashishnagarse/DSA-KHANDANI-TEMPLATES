#include <bits/stdc++.h>
using namespace std;

/**
 * Time Complexity (TC):
 * - Building the adjacency list: O(E)
 * - DFS traversal: O(V + E) (each node and edge is visited once)
 * - Overall Complexity: O(V + E)
 *
 * Space Complexity (SC):
 * - Adjacency List Storage: O(V + E)
 * - Visited Array: O(V)
 * - Recursive DFS Call Stack: O(V) (in worst case, for a single connected component)
 * - Total Space Complexity: O(V + E)
 */

class Solution {
public:
    /**
     * Detects a cycle in an undirected graph using DFS.
     * 
     * @param adj Adjacency list representation of the graph.
     * @param visited Boolean array to track visited nodes.
     * @param u Current node.
     * @param parent Parent node in the DFS traversal.
     * @return True if a cycle is detected, otherwise false.
     */
    bool isCycleDFS(vector<vector<int>>& adj, vector<bool>& visited, int u, int parent) {
        visited[u] = true;  // Mark the current node as visited
        
        for (auto& v : adj[u]) {  // Traverse all adjacent nodes
            if (v == parent) continue;  // Skip the edge leading back to the parent
            
            if (visited[v]) return true;  // If visited and not parent, cycle is detected
            
            if (isCycleDFS(adj, visited, v, u)) return true;  // Recursively check for cycles
        }
        return false;  // No cycle found
    }

    /**
     * Checks if an undirected graph contains a cycle.
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
            if (!visited[i] && isCycleDFS(adj, visited, i, -1)) {
                return true;  // Cycle detected
            }
        }
        return false;  // No cycle found in any component
    }
};

// Driver Code
int main() {
    Solution sol;
    int V = 2;  // Number of vertices
    vector<vector<int>> edges = {{0, 1}};  // List of edges

    cout << (sol.isCycle(V, edges) ? "true" : "false") << endl;
    return 0;
}
