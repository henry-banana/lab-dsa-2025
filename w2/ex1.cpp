#include <iostream>

int linearSearch(const int arr[], int n, int k) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == k) {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 5;

    int index = linearSearch(arr, n, k);

    std::cout << "Output: " << index << "\n";

    return 0;
}