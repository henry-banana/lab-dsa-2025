#include <iostream>

bool isSorted(int arr[], const int& n) {
    if (n == 1 || n == 0) {
        return true;  // Mảng rỗng hoặc có 1 phần tử luôn đã sắp xếp
    }
    
    if (arr[n - 2] > arr[n - 1]) {
        return false;  // Phát hiện phần tử không đúng thứ tự
    }

    return isSorted(arr, n - 1);  // Kiểm tra đệ quy với mảng nhỏ hơn
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (isSorted(arr, n)) {
        std::cout << "The array is sorted.\n";
    } else {
        std::cout << "The array is NOT sorted, buddy.\n";
    }

    return 0;
}