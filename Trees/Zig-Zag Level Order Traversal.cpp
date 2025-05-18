
/*
Example:

        1
       / \
      2   3
     / \   \
    7   6   5

Spiral Order Traversal:
→ Level 1: right to left → [1]
→ Level 2: left to right → [2, 3]
→ Level 3: right to left → [5, 6, 7]

Final Output: [1, 2, 3, 5, 6, 7]
*/

class Solution {
  public:
    // Function to return a list containing the spiral (zigzag) level order traversal of a binary tree.
    vector<int> findSpiral(Node* root) {
        vector<int> result; // This will store the final spiral order traversal
        
        // If the tree is empty, return an empty result
        if(root == NULL) return result;
        
        // Queue to perform level order traversal (BFS)
        queue<Node*> lot;
        lot.push(root);
        
        // Boolean flag to alternate the direction of traversal at each level
        bool leftToRight = false;  // Start with right to left as per spiral definition
        
        // Traverse the tree level by level
        while(!lot.empty()) {
            int size = lot.size();  // Number of nodes at the current level
            vector<int> row(size);  // Temporary vector to store the current level's values in the required order
            
            // Process all nodes at the current level
            for(int i = 0; i < size; i++) {
                Node* node = lot.front();
                lot.pop();
                
                // Determine the correct index based on traversal direction
                int idx = (leftToRight) ? i : (size - 1 - i);
                row[idx] = node->data;
                
                // Enqueue left and right children of the current node
                if(node->left) lot.push(node->left);
                if(node->right) lot.push(node->right);
            }
            
            // Flip the traversal direction for the next level
            leftToRight = !leftToRight;
            
            // Append current level's values to the final result
            for(auto ele : row) {
                result.push_back(ele);
            }
        }
        
        // Return the spiral (zigzag) order traversal
        return result;
    }
};


