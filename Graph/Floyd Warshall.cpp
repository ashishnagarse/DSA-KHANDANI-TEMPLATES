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
