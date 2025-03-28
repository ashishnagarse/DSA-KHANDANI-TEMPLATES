# **📌 Difference Array Technique 🚀**

The **Difference Array technique** is an efficient method for performing multiple range updates on an array. It allows applying updates in **O(1) time per query** and computing the final values in **O(n) time**.

This method is particularly useful in **competitive programming** and **large datasets** where frequent range updates are required.

---

## **📌 Features**
✅ **Efficient for multiple range updates**  
✅ **Updates in O(1) time per query**  
✅ **Final array computed in O(n) time**  
✅ **Reduces complexity from O(n) per update to O(1)**  
✅ **Used in problems involving frequent bulk updates**  

---

## **🚀 Implementation in C++**
```cpp
#include <bits/stdc++.h>
using namespace std;

// Function to create the Difference Array
vector<int> createDifferenceArray(vector<int> &arr) {
    int n = arr.size();
    vector<int> diff(n + 1, 0); // Difference array of size n+1

    for (int i = 0; i < n; i++) {
        diff[i] = arr[i];
    }

    return diff;
}

// Function to update the range [l, r] by adding 'value'
void updateRange(vector<int> &diff, int l, int r, int value) {
    diff[l] += value;
    if (r + 1 < diff.size()) {
        diff[r + 1] -= value;
    }
}

// Function to compute the final array from the Difference Array
vector<int> getFinalArray(vector<int> &diff) {
    int n = diff.size();
    vector<int> arr(n - 1, 0);
    arr[0] = diff[0];

    for (int i = 1; i < n - 1; i++) {
        arr[i] = arr[i - 1] + diff[i];
    }

    return arr;
}

int main() {
    vector<int> originalArray = {1, 2, 3, 4, 5};
    vector<int> differenceArray = createDifferenceArray(originalArray);

    // Update range [1, 3] by adding 10
    updateRange(differenceArray, 1, 3, 10);

    // Get the final updated array
    vector<int> finalArray = getFinalArray(differenceArray);

    // Print the final updated array
    cout << "Final Updated Array: ";
    for (int num : finalArray) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

