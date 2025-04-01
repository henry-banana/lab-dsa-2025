#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> findTriplet(const int nums[], const int n) {
    std::vector<std::vector<int>> result;
    if (n < 3) return result;
    
    std::vector<int> sortedNums(nums, nums + n);
    std::sort(sortedNums.begin(), sortedNums.end());
    
    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && sortedNums[i] == sortedNums[i-1]) continue;
        
        int left = i + 1;
        int right = n - 1;
        
        while (left < right) {
            int sum = sortedNums[i] + sortedNums[left] + sortedNums[right];
            
            if (sum < 0) {
                left++;
            } else if (sum > 0) {
                right--;
            } else {
                result.push_back({sortedNums[i], sortedNums[left], sortedNums[right]});

                while (left < right && sortedNums[left] == sortedNums[left+1]) {
                    left++;
                }

                while (left < right && sortedNums[right] == sortedNums[right-1]) {
                    right--;
                };
                
                left++;
                right--;
            }
        }
    }
    
    return result;
}

int main() {
    int nums[] = {-1, 0, 1, 2, -1, -4};
    int n = sizeof(nums) / sizeof(nums[0]);
    
    std::vector<std::vector<int>> result = findTriplet(nums, n);
    
    std::cout << "Output:\n";

    for (const auto& triplet : result) {
        std::cout << "[";

        for (int i = 0; i < triplet.size(); ++i) {
            std::cout << triplet[i];
            if (i < triplet.size() - 1) std::cout << ", ";
        }

        std::cout << "]" << "\n";
    }
    
    return 0;
}