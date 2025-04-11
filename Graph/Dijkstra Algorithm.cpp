// User Function Template
class Solution {
  public:
    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
        // Code here
        
        unordered_map<int , vector<pair<int , int>>> adj;
        
        for(auto& edge : edges){
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            
            adj[u].push_back({ v , wt }); // u->{v,wt}
            adj[v].push_back({ u , wt }); // v->{u,wt}
        }
        
        vector<int> dist(V , INT_MAX);
        dist[src] = 0;
        
        // // u->{v,wt}
        priority_queue<pair<int , int> , vector<pair<int  , int>> , greater<>> pq;
        pq.push({0 , src}); //distance , node
        
        while(!pq.empty()){
            auto curr  = pq.top();
            pq.pop();
            
            // From Min-heap : (distance , node)
            int currDist = curr.first;
            int node = curr.second;
            
            for(auto& v : adj[node]){
                // From adj : u->{v,wt}
                int ngbr = v.first;
                int weight = v.second;
                
                if( (currDist + weight) < dist[ngbr] ){
                    dist[ngbr] = currDist + weight;
                    pq.push({currDist+weight , ngbr}); // Min-heap : (distance , node)
                }
            }
        }
        return dist;
    }
};
