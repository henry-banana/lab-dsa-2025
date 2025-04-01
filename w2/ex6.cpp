#include <iostream>

bool binarySearch (const int arr[], const int n, const int k) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == k) {
            return true;
        } else if (arr[mid] < k) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return false;
}

bool existSum (const int arr[], const int n, const int k) {
    for (int i = 0; i < n; i++) {
        if (binarySearch(arr, n, k - arr[i])) {
            return true;
        }
    }
    
    return false;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int k = 5;
    bool result = existSum(arr, n, k);
    std::cout << "Output: " << (result ? "YES" : "NOPE") << "\n";

    return 0;
}