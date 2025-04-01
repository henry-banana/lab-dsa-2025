#include <iostream>

int mininalLengthSubArr(const int nums[], const int n, const int target) {
    int left = 0, right = 0, sum = 0, min_length = n + 1;

    while (right < n) {
        sum += nums[right];

        while (sum >= target) {
            min_length = std::min(min_length, right - left + 1);
            sum -= nums[left++];
        }

        right++;
    }

    return (min_length == n + 1) ? 0 : min_length;
}

int main() {
    int nums[] = {2, 3, 1, 2, 4, 3};
    int n = sizeof(nums) / sizeof(nums[0]);
    int target = 7;

    int result = mininalLengthSubArr(nums, n, target);
    std::cout << "Output: " << result << "\n";

    return 0;
}