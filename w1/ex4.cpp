#include <iostream>

void towerOfHanoi(const int& n, const char& src, const char& dest, const char& temp) {
    if (n == 1) {
        // Di chuyển đĩa cuối cùng từ src sang dest
        std::cout << "Move disk 1 from " << src << " to " << dest << "\n";
        return;
    }

    // Di chuyển n-1 đĩa từ src sang temp (dùng dest làm trung gian)
    towerOfHanoi(n - 1, src, temp, dest);

    // Di chuyển đĩa n từ src sang dest
    std::cout << "Move disk " << n << " from " << src << " to " << dest << "\n";

    // Di chuyển n-1 đĩa từ temp sang dest (dùng src làm trung gian)
    towerOfHanoi(n - 1, temp, dest, src);
}

int main() {
    int n = 5;
    towerOfHanoi(n, 'A', 'C', 'B');
    return 0;
}