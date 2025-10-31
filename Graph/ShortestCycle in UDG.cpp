class Solution {
public:
    int bfsShortestCycle(unordered_map<int, vector<int>>& adj, int start, int V) {
        vector<int> dist(V, -1);
        queue<int> q;
        
        q.push(start);
        dist[start] = 0;
        
        int minCycle = INT_MAX;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    // Not visited
                    dist[v] = dist[u] + 1;
                    q.push(v);
                } 
                else if (dist[v] >= dist[u]) {
                    // Found a cycle (back edge or cross edge)
                    // Cycle length = dist[u] + dist[v] + 1
                    minCycle = min(minCycle, dist[u] + dist[v] + 1);
                }
            }
        }
        
        return minCycle;
    }
    
    int shortCycle(int V, vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> adj;
        
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        int minCycle = INT_MAX;
        
        // Run BFS from each node
        for (int i = 0; i < V; i++) {
            minCycle = min(minCycle, bfsShortestCycle(adj, i, V));
        }
        
        return (minCycle == INT_MAX) ? -1 : minCycle;
    }
};

/*
==================================================================================
                            EXPLANATION
==================================================================================

PROBLEM: Find the length of the shortest cycle in an undirected graph.

KEY INSIGHTS:
1. A cycle exists when we encounter an already-visited node during traversal
2. BFS is better than DFS for shortest cycle because it explores level-by-level
3. When BFS finds a back edge (edge to already visited node), we found a cycle
4. Cycle length = distance[u] + distance[v] + 1 (the +1 is for edge u-v)
5. We need to run BFS from EVERY node to find the globally shortest cycle

ALGORITHM:
- Build adjacency list from edges
- For each node as starting point:
    - Run BFS to find shortest cycle starting from that node
    - Track distance of each node from start
    - When we encounter a visited node with dist[v] >= dist[u]:
        * This forms a cycle
        * Calculate cycle length: dist[u] + dist[v] + 1
- Return minimum cycle length found across all BFS runs

WHY dist[v] >= dist[u] CHECK?
- If dist[v] < dist[u], then v is parent/ancestor of u (already processed edge)
- If dist[v] >= dist[u], this is a NEW cycle formation (back/cross edge)

TIME COMPLEXITY: O(V * (V + E)) - BFS from each vertex
SPACE COMPLEXITY: O(V + E) - for adjacency list and distance array

==================================================================================
                            DRY RUN
==================================================================================

EXAMPLE GRAPH:
V = 5 (vertices: 0, 1, 2, 3, 4)
Edges: [[0,1], [1,2], [2,0], [1,3], [3,4]]

Adjacency List:
0 -> [1, 2]
1 -> [0, 2, 3]
2 -> [1, 0]
3 -> [1, 4]
4 -> [3]

Graph visualization:
    0 --- 1 --- 3 --- 4
     \   /
      \ /
       2

CYCLE EXISTS: 0 -> 1 -> 2 -> 0 (length 3)

-----------------------------------------------------------------------------------
BFS FROM NODE 0:
-----------------------------------------------------------------------------------
Initial: dist = [-1, -1, -1, -1, -1], queue = [0], minCycle = INT_MAX

Step 1: Process node 0 (dist[0] = 0)
   - Explore neighbor 1: dist[1] = -1 (not visited)
     -> Set dist[1] = 0 + 1 = 1, queue = [1]
   - Explore neighbor 2: dist[2] = -1 (not visited)
     -> Set dist[2] = 0 + 1 = 1, queue = [1, 2]
   
   dist = [0, 1, 1, -1, -1], queue = [1, 2]

Step 2: Process node 1 (dist[1] = 1)
   - Explore neighbor 0: dist[0] = 0 (visited, dist[0] < dist[1])
     -> Skip (parent direction)
   - Explore neighbor 2: dist[2] = 1 (visited, dist[2] >= dist[1])
     -> CYCLE FOUND! 
     -> Cycle length = dist[1] + dist[2] + 1 = 1 + 1 + 1 = 3
     -> minCycle = min(INT_MAX, 3) = 3
   - Explore neighbor 3: dist[3] = -1 (not visited)
     -> Set dist[3] = 1 + 1 = 2, queue = [2, 3]
   
   dist = [0, 1, 1, 2, -1], queue = [2, 3], minCycle = 3

Step 3: Process node 2 (dist[2] = 1)
   - Explore neighbor 1: Already processed
   - Explore neighbor 0: Already processed
   
   queue = [3], minCycle = 3

Step 4: Process node 3 (dist[3] = 2)
   - Explore neighbor 1: Already processed
   - Explore neighbor 4: dist[4] = -1 (not visited)
     -> Set dist[4] = 2 + 1 = 3, queue = [4]
   
   dist = [0, 1, 1, 2, 3], queue = [4], minCycle = 3

Step 5: Process node 4 (dist[4] = 3)
   - Explore neighbor 3: Already processed
   
   queue = [], minCycle = 3

BFS from node 0 returns: minCycle = 3

-----------------------------------------------------------------------------------
BFS FROM OTHER NODES (1, 2, 3, 4):
-----------------------------------------------------------------------------------
BFS from node 1: Will also find cycle 0-1-2-0, returns 3
BFS from node 2: Will also find cycle 0-1-2-0, returns 3
BFS from node 3: No cycle found in its component, returns INT_MAX
BFS from node 4: No cycle found in its component, returns INT_MAX

-----------------------------------------------------------------------------------
FINAL RESULT:
-----------------------------------------------------------------------------------
minCycle = min(3, 3, 3, INT_MAX, INT_MAX) = 3

Answer: 3 (shortest cycle is 0 -> 1 -> 2 -> 0)

==================================================================================
WHY THIS WORKS:
==================================================================================
1. When we're at node u with distance d[u], and we see neighbor v:
   - If v is not visited: v is a child in BFS tree
   - If v is visited and d[v] < d[u]: v is parent/ancestor (ignore)
   - If v is visited and d[v] >= d[u]: CYCLE FOUND!
      * d[u] = steps from start to u
      * d[v] = steps from start to v
      * d[u] + d[v] + 1 = complete cycle length

2. Example from above: When at node 1 (d[1]=1) and we see node 2 (d[2]=1):
   - Path from 0 to 1: length 1
   - Path from 0 to 2: length 1
   - Edge 1-2: length 1
   - Total cycle: 0->1, 1->2, 2->0 = 1 + 1 + 1 = 3 ✓

3. We run BFS from each node because:
   - Different starting points may reveal different (possibly shorter) cycles
   - Global shortest cycle = minimum across all starting points
==================================================================================
*/
