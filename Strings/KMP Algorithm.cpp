/*
KMP String Matching Algorithm - Simple & Commented Version

Example:
---------
Pattern: "ababcababd"
Text:    "ababcababcababdababcababd"

Expected Output:
Pattern found at index: 6
Pattern found at index: 19

Explanation:
The pattern "ababcababd" occurs starting at positions 6 and 19 (1-based index).
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> search(string &pattern, string &text) {
        int m = pattern.size();
        int n = text.size();
        vector<int> lps(m, 0);
        vector<int> positions;

        // STEP 1: Build the LPS (Longest Prefix Suffix) array
        int len = 0; // length of the current longest prefix suffix
        int i = 1;   // start from the second character

        while (i < m) {
            if (pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1]; // try the previous longest prefix suffix
                } else {
                    lps[i] = 0; // no prefix found
                    i++;
                }
            }
        }

        // STEP 2: KMP Search
        i = 0; // index for text
        int j = 0; // index for pattern

        while (i < n) {
            if (pattern[j] == text[i]) {
                // characters match, move both pointers
                i++;
                j++;
            }

            if (j == m) {
                // full match found, store the starting position (1-based)
                positions.push_back(i - j + 1);

                // look for next match using lps
                j = lps[j - 1];
            } else if (i < n && pattern[j] != text[i]) {
                if (j != 0) {
                    // mismatch after some matches, jump using lps
                    j = lps[j - 1];
                } else {
                    // mismatch at the start, just move to the next character in text
                    i++;
                }
            }
        }

        return positions;
    }
};

// Usage example
int main() {
    string text = "ababcababcababdababcababd";
    string pattern = "ababcababd";

    Solution sol;
    vector<int> result = sol.search(pattern, text);

    for (int pos : result) {
        cout << "Pattern found at index: " << pos << endl;
    }

    return 0;
}
