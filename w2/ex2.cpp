#include <iostream>

int sentinelLinearSearch(int a[], int n, int k) {
    int last = a[n - 1];
    a[n - 1] = k;
    
    int i = 0;
    while (a[i] != k) {
        i++;
    }
    
    a[n - 1] = last;
    
    if (i < n - 1 || a[n - 1] == k) {
        return i;
    }
    
    return -1;
}

int main() {
    int arr[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 5;

    int index = sentinelLinearSearch(arr, n, k);
    std::cout << "Output: " << index << "\n";

    return 0;
}