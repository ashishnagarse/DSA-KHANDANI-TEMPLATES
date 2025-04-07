class Solution {
  public:
    bool isCyclic(int V, vector<vector<int>> &edges) {
        // Build the adjacency list
        vector<vector<int>> adj(V);
        vector<int> indegree(V, 0);

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            indegree[v]++;
        }

        queue<int> q;

        // Start with all nodes having 0 indegree
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        int processed = 0;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            processed++;

            for (int neighbor : adj[curr]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // If we couldn't process all nodes, cycle exists
        return (processed != V);
    }
};
