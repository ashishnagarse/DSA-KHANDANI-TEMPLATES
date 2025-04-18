class Trie {
public:

    // Structure to represent each node in the Trie
    struct trieNode {
        bool isEndOfWord;           // Flag to check if this node marks the end of a valid word
        trieNode* children[26];     // Array of child pointers for each lowercase letter 'a' to 'z'

        // Constructor to initialize node
        trieNode() {
            isEndOfWord = false;
            for (int i = 0; i < 26; ++i)
                children[i] = nullptr; // Initialize all children as null
        }
    };

    trieNode* root; // Root node of the Trie

    // Constructor to initialize the Trie
    Trie() {
        root = new trieNode(); // Root is an empty node with no children and not end of any word
    }

    // Inserts a word into the Trie
    void insert(string &word) {
        trieNode* crawler = root; // Start from the root node

        for (char ch : word) {
            int idx = ch - 'a'; // Map character to index (0 for 'a', 1 for 'b', ..., 25 for 'z')

            // If the corresponding child node doesn't exist, create it
            if (crawler->children[idx] == nullptr) {
                crawler->children[idx] = new trieNode();
            }

            // Move to the child node
            crawler = crawler->children[idx];
        }

        // After inserting all characters, mark the last node as the end of a word
        crawler->isEndOfWord = true;
    }

    // Searches for a complete word in the Trie
    bool search(string &word) {
        trieNode* crawler = root;

        for (char ch : word) {
            int idx = ch - 'a';

            // If at any point the required child doesn't exist, the word is not in the Trie
            if (crawler->children[idx] == nullptr)
                return false;

            crawler = crawler->children[idx];
        }

        // Word is found only if the last node is marked as end of a word
        return crawler != nullptr && crawler->isEndOfWord;
    }

    // Checks if there exists any word in the Trie that starts with the given prefix
    bool isPrefix(string &prefix) {
        trieNode* crawler = root;

        for (char ch : prefix) {
            int idx = ch - 'a';

            // If the path breaks, the prefix does not exist
            if (crawler->children[idx] == nullptr)
                return false;

            crawler = crawler->children[idx];
        }

        // If all characters are found, it's a valid prefix
        return true;
    }
};
