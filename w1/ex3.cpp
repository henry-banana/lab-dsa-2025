#include <iostream>
#include <string>

void generateBinaryStrings(int n, std::string str) {
    if (n == 0) {
        std::cout << str << "\n";  // In chuỗi khi đạt độ dài n
        return;
    }
    // Đệ quy thêm '0' hoặc '1' vào chuỗi
    generateBinaryStrings(n - 1, str + "0");
    generateBinaryStrings(n - 1, str + "1");
}

int main() {
    int n;
    std::cout << "Input: ";
    std::cin >> n;
    std::cout << "Output:\n";
    generateBinaryStrings(n, "");

    return 0;
}