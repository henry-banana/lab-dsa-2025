#include <iostream>

int factorial(int n) {
    if (n == 0) {
        return 1;  // Điều kiện để dừng: 0! = 1
    }
    return n * factorial(n - 1);  // Công thức đệ quy: n! = n * (n-1)!
}

int main() {
    int n;
    std::cout << "Input: ";
    std::cin >> n;
    std::cout << "Output: " << factorial(n) << "\n";

    return 0;
}