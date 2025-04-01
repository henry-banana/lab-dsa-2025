#include <iostream>

int shipWithinDays(const int weights[], int n, int days) {
    int left = 0, right = 0;
    
    for (int i = 0; i < n; i++) {
        left = std::max(left, weights[i]);
        right += weights[i];
    }
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        int total = 0, count = 1;
        
        for (int i = 0; i < n; i++) {
            total += weights[i];
            if (total > mid) {
                total = weights[i];
                count++;
            }
        }
        
        if (count > days) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

int main() {
    int weights[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(weights) / sizeof(weights[0]);
    int days = 5;

    int result = shipWithinDays(weights, n, days);
    std::cout << "Output: " << result << "\n";
    
    return 0;
}