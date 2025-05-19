/*
Example:

        20
       /  \
     10    30
    /  \     \
   5   15     40

Inorder Traversal: [5, 10, 15, 20, 30, 40]

Key = 15
→ Predecessor = 10 (just before 15 in inorder)
→ Successor   = 20 (just after 15 in inorder)

Key = 5
→ Predecessor = NULL
→ Successor   = 10

Final Output (for key = 15): [10, 20]
*/

class Solution {
  public:

    // Helper function to find predecessor and successor
    void helper(Node* root, Node*& pre, Node*& suc, int key) {
        if (root == NULL) return;

        if (root->data == key) {
            // Find predecessor: rightmost node in left subtree
            if (root->left != NULL) {
                Node* temp = root->left;
                while (temp->right)
                    temp = temp->right;
                pre = temp;
            }

            // Find successor: leftmost node in right subtree
            if (root->right != NULL) {
                Node* temp = root->right;
                while (temp->left)
                    temp = temp->left;
                suc = temp;
            }
            return;
        }

        if (key < root->data) {
            // Current node could be successor
            suc = root;
            helper(root->left, pre, suc, key);
        } else {
            // Current node could be predecessor
            pre = root;
            helper(root->right, pre, suc, key);
        }
    }

    // Main function
    vector<Node*> findPreSuc(Node* root, int key) {
        Node* pre = NULL;
        Node* suc = NULL;

        // Start recursion
        helper(root, pre, suc, key);

        // Return both as a vector
        return {pre, suc};
    }
};
