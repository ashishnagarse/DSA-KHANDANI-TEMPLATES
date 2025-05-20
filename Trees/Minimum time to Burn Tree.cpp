/*
🔥 Burning Tree Problem

Input:
        1
      /   \
     2     3
    / \     \
   4   5     6

Target = 5

Fire spreads in all directions: left, right, parent.
Final Output: 4 seconds
*/

class Solution {
  public:

    // Step 1: Build parent map and find target node
    void mapParents(Node* root, unordered_map<Node*, Node*>& parent, Node*& targetNode, int target) {
        queue<Node*> q;
        q.push(root);
        while(!q.empty()) {
            Node* current = q.front(); q.pop();

            if(current->data == target) {
                targetNode = current;
            }

            if(current->left) {
                parent[current->left] = current;
                q.push(current->left);
            }
            if(current->right) {
                parent[current->right] = current;
                q.push(current->right);
            }
        }
    }

    // Step 2: BFS from target node to simulate fire
    int burnTree(Node* targetNode, unordered_map<Node*, Node*>& parent) {
        unordered_map<Node*, bool> visited;
        queue<Node*> q;
        q.push(targetNode);
        visited[targetNode] = true;

        int time = 0;

        while(!q.empty()) {
            int size = q.size();
            bool burnedThisSecond = false;

            for(int i = 0; i < size; i++) {
                Node* current = q.front(); q.pop();

                // Check left child
                if(current->left && !visited[current->left]) {
                    visited[current->left] = true;
                    q.push(current->left);
                    burnedThisSecond = true;
                }

                // Check right child
                if(current->right && !visited[current->right]) {
                    visited[current->right] = true;
                    q.push(current->right);
                    burnedThisSecond = true;
                }

                // Check parent
                if(parent[current] && !visited[parent[current]]) {
                    visited[parent[current]] = true;
                    q.push(parent[current]);
                    burnedThisSecond = true;
                }
            }

            if(burnedThisSecond) time++;
        }

        return time;
    }

    // Main function
    int minTime(Node* root, int target) {
        unordered_map<Node*, Node*> parent; // child → parent
        Node* targetNode = NULL;

        mapParents(root, parent, targetNode, target
