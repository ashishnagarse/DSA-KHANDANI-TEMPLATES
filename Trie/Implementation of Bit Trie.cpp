class BitTrie {
public:
    // Each node in the Bit Trie
    struct trieNode {
        trieNode* left;   // Represents bit 0
        trieNode* right;  // Represents bit 1

        // Constructor initializes both children to null
        trieNode() {
            left = nullptr;
            right = nullptr;
        }
    };

    trieNode* root;

    // Constructor initializes the root node of the trie
    BitTrie() {
        root = new trieNode();
    }

    // Function to insert a number into the trie
    void insert(int num) {
        trieNode* node = root;

        // Loop through the bits of the number from most significant bit (31) to least (0)
        for (int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1; // Right shift 'num' by i and get the last bit

            if (bit == 0) {
                // If bit is 0, go left
                if (!node->left)
                    node->left = new trieNode(); // Create new node if it doesn't exist
                node = node->left;
            } else {
                // If bit is 1, go right
                if (!node->right)
                    node->right = new trieNode(); // Create new node if it doesn't exist
                node = node->right;
            }
        }

        // No need to mark "end of number" because we're dealing with fixed 32-bit integers
    }
