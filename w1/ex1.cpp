#include <iostream>

int fibonacci(int n) {
    if (n < 2) {
        return n;  // Điều kiện dừng: Fibonacci(0) = 0, Fibonacci(1) = 1
    }
    return fibonacci(n - 1) + fibonacci(n - 2);  // Công thức đệ quy Fibonacci
}

int main() {
    int n;
    std::cout << "Input: ";
    std::cin >> n;
    std::cout << "Output: ";

    // In dãy Fibonacci từ 0 đến n-1
    for (int i = 0; i < n; i++) {
        std::cout << fibonacci(i) << " ";
    }
    std::cout << "\n";

    return 0;
}