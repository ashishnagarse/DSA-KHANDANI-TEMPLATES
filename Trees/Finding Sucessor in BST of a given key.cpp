/*
Example:

        20
       /  \
     10    30
    /  \     \
   5   15     40

Find Inorder Successor:
→ The successor of a node is the next node in the in-order traversal (smallest node greater than the given key).

Step-by-step:
- Key = 10 → Inorder: [5, 10, 15, 20, 30, 40] → Successor = 15
- Key = 15 → Inorder: [5, 10, 15, 20, 30, 40] → Successor = 20
- Key = 30 → Inorder: [5, 10, 15, 20, 30, 40] → Successor = 40
- Key = 40 → Inorder: [5, 10, 15, 20, 30, 40] → No successor (returns NULL)

Final Output:
- For key = 10 → Successor = 15
- For key = 15 → Successor = 20
- For key = 40 → Successor = NULL
*/

class Solution {
  public:
    // Function to find the inorder successor of a given key in BST
    Node* findSuc(Node* root, int key) {
        Node* successor = NULL;

        // Traverse the tree
        while (root != NULL) {
            if (key >= root->data) {
                // If key is greater than or equal to current node's data,
                // successor must be in right subtree
                root = root->right;
            } else {
                // Current node is a potential successor
                successor = root;
                root = root->left;
            }
        }

        // Return the final successor (or NULL if none found)
        return successor;
    }
};
