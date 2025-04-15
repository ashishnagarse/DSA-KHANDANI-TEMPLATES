class Solution {
  public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
        vector<int> dist(V, 1e8); // Or use INT_MAX for clarity
        dist[src] = 0;

        // Relax all edges V - 1 times
        for (int i = 0; i < V - 1; ++i) {
            for (auto& edge : edges) {
                int u = edge[0], v = edge[1], w = edge[2];
                if (dist[u] != 1e8 && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }

        // Optional: Check for negative weight cycles
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (dist[u] != 1e8 && dist[u] + w < dist[v]) {
                // We found a negative cycle. Panic? Nah, just return an error indicator.
                return {-1}; 
            }
        }

        return dist;
    }
};
