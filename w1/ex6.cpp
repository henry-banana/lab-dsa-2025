#include <iostream>

const int SIZE = 8;  // Kích thước bàn cờ
int col[SIZE] = {0};  // Kiểm tra cột
int diag1[2 * SIZE - 1] = {0};  // Kiểm tra đường chéo chính
int diag2[2 * SIZE - 1] = {0};  // Kiểm tra đường chéo phụ
int solution = 0;

void solveNQueens(int row) {
    if (row == SIZE) {
        ++solution;  // Tìm thấy một giải pháp
        return;
    }

    for (int i = 0; i < SIZE; ++i) {

        // Kiểm tra có thể đặt hậu tại (row, i) không
        if (col[i] == 0 && diag1[row - i + SIZE - 1] == 0 && diag2[row + i] == 0) {
            col[i] = diag1[row - i + SIZE - 1] = diag2[row + i] = 1;  // Đánh dấu vị trí đã chiếm

            solveNQueens(row + 1);  // Đệ quy hàng tiếp theo
            
            // Backtrack: bỏ đánh dấu để thử vị trí khác
            col[i] = diag1[row - i + SIZE - 1] = diag2[row + i] = 0;
        }
    }
}

int main() {
    solveNQueens(0);  // Bắt đầu từ hàng 0
    std::cout << solution << "\n";
    return 0;
}