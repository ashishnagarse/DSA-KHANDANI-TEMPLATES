/*
Example:

        1
       / \
      2   3
     / \   \
    7   6   5

Level Order Traversal (BFS):
→ Visit level by level from top to bottom, left to right.

Step-by-step:
- Level 1: [1]
- Level 2: [2, 3]
- Level 3: [7, 6, 5]

Final Output: [1, 2, 3, 7, 6, 5]
*/

class Solution {
  public:
    // Function to return a list containing the level order traversal of a binary tree.
    vector<int> levelOrder(Node* root) {
        vector<int> result;  // To store the final level order traversal
        
        // If the tree is empty, return an empty vector
        if(root == NULL) return result;
        
        // Queue to process nodes level by level (BFS)
        queue<Node*> q;
        q.push(root);
        
        // Traverse the tree
        while(!q.empty()) {
            Node* node = q.front();
            q.pop();
            
            // Add current node's data to result
            result.push_back(node->data);
            
            // Enqueue left and right children
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        
        // Return the level order traversal
        return result;
    }
};


