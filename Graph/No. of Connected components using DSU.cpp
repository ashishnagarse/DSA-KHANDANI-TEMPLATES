#include <iostream>
#include <vector>
#include <unordered_set>

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
        if(x == parent[x]){
          return x;
        }
        return parent[x] = find(parent[x]); // Path compression
    }

    void union(int x, int y) {
        int x_parent = find(x);
        int y_parent = find(y);

        if(x_parent == y_parent) return;

        if(rank[x_parent] < rank[y_parent]) {
            parent[x_parent] = y_parent;
        } else if(rank[x_parent] > rank[y_parent]) {
            parent[y_parent] = x_parent;
        } else {
            parent[y_parent] = x_parent;
            rank[x_parent]++;
        }
    }
};

int countComponents(int n, vector<pair<int, int>>& edges) {
    DSU dsu(n);

    for(auto& edge : edges) {
        dsu.union(edge.first, edge.second);
    }

    unordered_set<int> uniqueRoots;
    for(int i = 0; i < n; ++i) {
        uniqueRoots.insert(dsu.find(i));
    }

    return uniqueRoots.size();
}

int main() {
    int n = 5; // Number of nodes
    vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {3, 4}}; // Edges

    cout << "Number of components: " << countComponents(n, edges) << endl;

    return 0;
}
