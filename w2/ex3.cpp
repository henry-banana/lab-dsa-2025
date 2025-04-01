#include <iostream>

/*
Suppose an array of length n sorted in ascending order is rotated between 1 and n times.
For example, the array
nums = [0, 1, 2, 4, 5, 6, 7]
might become:
• [4, 5, 6, 7, 0, 1, 2] if it was rotated 4 times.
• [0, 1, 2, 4, 5, 6, 7] if it was rotated 7 times.
Notice that rotating an array
[a0, a1, a2, . . . , an−1]
one time results in the array
[an−1, a0, a1, a2, . . . , an−2].
Given the sorted rotated array nums of unique elements, return the minimum element
of this array.
Your algorithm must run in O(log n) time.
Example
Input
5
3 4 5 1 2
Output
1
*/

int findMin(const int arr[], int n) {
    int left = 0, right = n - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] > arr[right]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return arr[left];
}

int main() {
    int arr[] = {3, 4, 5, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    int minElement = findMin(arr, n);
    std::cout << "Output: " << minElement << "\n";

    return 0;
}