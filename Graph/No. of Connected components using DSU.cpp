#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class DSU {
public:
    vector<int> parent, rank;
    
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; ++i) parent[i] = i;
    }
    
    int find(int x) {
        if(x == parent[x]) {  // Fixed: was x = parent[x]
            return x;
        }
        return parent[x] = find(parent[x]); // Path compression
    }
    
    void union_sets(int x, int y) {  // Renamed from union
        int x_parent = find(x);
        int y_parent = find(y);
        
        cout << "  find(" << x << ") = " << x_parent 
             << ", find(" << y << ") = " << y_parent << endl;
        
        if(x_parent == y_parent) {
            cout << "  Already in same component!" << endl;
            return;
        }
        
        if(rank[x_parent] < rank[y_parent]) {
            parent[x_parent] = y_parent;
            cout << "  Make " << y_parent << " parent of " << x_parent << endl;
        } else if(rank[x_parent] > rank[y_parent]) {
            parent[y_parent] = x_parent;
            cout << "  Make " << x_parent << " parent of " << y_parent << endl;
        } else {
            parent[y_parent] = x_parent;
            rank[x_parent]++;
            cout << "  Make " << x_parent << " parent of " << y_parent 
                 << " (same rank, increment rank[" << x_parent << "])" << endl;
        }
    }
};

struct ComponentInfo {
    int nodes = 0;
    int edges = 0;
};

void analyzeComponents(int n, vector<pair<int, int>>& edges) {
    DSU dsu(n);
    
    cout << "=== STEP 1: Union all edges ===" << endl;
    for(auto& edge : edges) {
        cout << "Union(" << edge.first << ", " << edge.second << ")" << endl;
        dsu.union_sets(edge.first, edge.second);
    }
    
    cout << "\n=== STEP 2: Find root for each node ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << "Node " << i << " -> Root " << dsu.find(i) << endl;
    }
    
    cout << "\n=== STEP 3: Count nodes per component ===" << endl;
    unordered_map<int, ComponentInfo> components;
    for(int i = 0; i < n; ++i) {
        int root = dsu.find(i);
        components[root].nodes++;
    }
    
    for(auto& [root, info] : components) {
        cout << "Component (root=" << root << "): " << info.nodes << " nodes" << endl;
    }
    
    cout << "\n=== STEP 4: Count edges per component ===" << endl;
    for(auto& edge : edges) {
        int root = dsu.find(edge.first);  // Can use either endpoint
        components[root].edges++;
        cout << "Edge {" << edge.first << "," << edge.second 
             << "} belongs to component with root " << root << endl;
    }
    
    cout << "\n=== FINAL RESULTS ===" << endl;
    cout << "Total components: " << components.size() << endl;
    for(auto& [root, info] : components) {
        cout << "Component " << root << ": " 
             << info.nodes << " nodes, " 
             << info.edges << " edges" << endl;
    }
}

int main() {
    int n = 7; // 7 nodes (0-6)
    vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {3, 4}, {5, 6}};
    
    cout << "Graph: " << n << " nodes, edges: ";
    for(auto& e : edges) {
        cout << "{" << e.first << "," << e.second << "} ";
    }
    cout << "\n\n";
    
    analyzeComponents(n, edges);
    
    return 0;
}


## EXAMPLE

Graph: 7 nodes, edges: {0,1} {1,2} {3,4} {5,6} 

=== STEP 1: Union all edges ===
Union(0, 1)
  find(0) = 0, find(1) = 1
  Make 0 parent of 1 (same rank, increment rank[0])
Union(1, 2)
  find(1) = 0, find(2) = 2
  Make 0 parent of 2 (same rank, increment rank[0])
Union(3, 4)
  find(3) = 3, find(4) = 4
  Make 3 parent of 4 (same rank, increment rank[3])
Union(5, 6)
  find(5) = 5, find(6) = 6
  Make 5 parent of 6 (same rank, increment rank[5])

=== STEP 2: Find root for each node ===
Node 0 -> Root 0
Node 1 -> Root 0
Node 2 -> Root 0
Node 3 -> Root 3
Node 4 -> Root 3
Node 5 -> Root 5
Node 6 -> Root 5

=== STEP 3: Count nodes per component ===
Component (root=0): 3 nodes
Component (root=3): 2 nodes
Component (root=5): 2 nodes

=== STEP 4: Count edges per component ===
Edge {0,1} belongs to component with root 0
Edge {1,2} belongs to component with root 0
Edge {3,4} belongs to component with root 3
Edge {5,6} belongs to component with root 5

=== FINAL RESULTS ===
Total components: 3
Component 0: 3 nodes, 2 edges
Component 3: 2 nodes, 1 edge
Component 5: 2 nodes, 1 edge
