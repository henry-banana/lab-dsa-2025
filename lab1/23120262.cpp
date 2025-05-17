#include <iostream>     // cin, cout
#include <fstream>      // ifstream, ofstream
#include <string>       // string
#include <vector>       // vector
#include <stack>        // stack
#include <stdexcept>    // runtime_error

class BigInteger;

// Hàm xác định độ ưu tiên của các toán tử
int precedence(const std::string& op);
// Hàm chuyển đổi chuỗi đầu vào thành mảng các token
std::vector<std::string> tokenInit(const std::string& str);
// Hàm chuyển biểu thức từ dạng trung tố sang hậu tố
std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens);
// Hàm tính giá trị của biểu thức hậu tố
BigInteger calculatePostfix(const std::vector<std::string>& tokens);
// Hàm lấy giá trị tuyệt đối của một số nguyên lớn
BigInteger abs(const BigInteger &num);

/**
 * Lớp BigInteger: Đại diện cho số nguyên lớn không giới hạn
 * Lưu trữ số dưới dạng chuỗi và thực hiện các phép toán số học
 */
class BigInteger {
public:
    std::string number;  // Chuỗi chứa các chữ số của số nguyên lớn (không bao gồm dấu)
    bool negative = false;  // Cờ đánh dấu số âm

    // Các hàm khởi tạo và hủy
    BigInteger();  // Khởi tạo mặc định (số 0)
    BigInteger(const std::string &s);  // Khởi tạo từ chuỗi
    BigInteger(const BigInteger &other);  // Khởi tạo sao chép
    BigInteger& operator=(const BigInteger &other);  // Toán tử gán
    ~BigInteger();  // Hàm hủy

    // Các phương thức và toán tử
    bool isZero() const;  // Kiểm tra số có bằng 0 không
    BigInteger operator+(const BigInteger &other) const;  // Toán tử cộng
    BigInteger operator-(const BigInteger &other) const;  // Toán tử trừ
    BigInteger schoolbookMultiply(const BigInteger& num) const;  // Phép nhân theo cách thông thường
    BigInteger karatsubaMultiply(const BigInteger& num) const;  // Phép nhân sử dụng thuật toán Karatsuba
    BigInteger operator*(const BigInteger &other) const;  // Toán tử nhân
    BigInteger operator/(const BigInteger &other) const;  // Toán tử chia
    bool operator==(const BigInteger &other) const;  // Toán tử so sánh bằng
    bool operator>=(const BigInteger &other) const;  // Toán tử so sánh lớn hơn hoặc bằng
    bool operator<(const BigInteger &other) const;  // Toán tử so sánh nhỏ hơn
    bool compareAbsGreaterEqual(const BigInteger &other) const;  // So sánh giá trị tuyệt đối lớn hơn hoặc bằng
    BigInteger addAbs(const BigInteger &other) const;  // Cộng hai giá trị tuyệt đối
    BigInteger subtractAbs(const BigInteger &other) const;  // Trừ hai giá trị tuyệt đối
    void normalizeString();  // Chuẩn hóa chuỗi số (loại bỏ số 0 đứng đầu)
};

// ==================================================================

/**
 * Hàm main: Điểm khởi đầu của chương trình
 * Đọc biểu thức từ file input, tính toán và ghi kết quả ra file output
 */
int main(int argc, char **argv) {
    // Kiểm tra đúng số lượng tham số dòng lệnh (tên chương trình, file input, file output)
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    // Mở các file input và output
    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);

    // Kiểm tra việc mở file có thành công không
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening files\n";
        return 1;
    }

    std::string line;

    // Đọc từng dòng trong file input
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;  // Bỏ qua dòng trống

        try {
            // Chuyển chuỗi biểu thức thành các token
            auto tokens = tokenInit(line);
            if (tokens.size() == 1 && tokens[0] == "ERROR_INVALID_CHAR") {
                throw std::runtime_error("Invalid character in expression");
            }

            // Chuyển biểu thức trung tố thành hậu tố
            auto postfix = infixToPostfix(tokens);
            if (postfix.size() == 1 && postfix[0] == "ERROR_INVALID_PARENTHESIS") {
                throw std::runtime_error("Malformed expression (parentheses mismatch)");
            }

            // Tính toán giá trị của biểu thức hậu tố
            BigInteger result = calculatePostfix(postfix);
            if (result.negative && !result.isZero()) { // Thêm điều kiện !result.isZero() để không in "-0"
                outputFile << "-";
                std::cout << "-";
            }
            outputFile << result.number << '\n';
            std::cout << result.number << '\n';
        } catch (const std::exception &e) {
            // Xử lý các lỗi và in thông báo
            outputFile << "Error: " << e.what() << '\n';
            std::cerr << "Error: " << e.what() << '\n';
        }
    }

    // Đóng các file
    inputFile.close();
    outputFile.close();


    // ================ TEST CASES ==================
    // Phần code kiểm thử
    // std::ifstream testInput(argv[2]);
    // std::ifstream result("results_test.txt");
    // std::string testLine, resultLine;

    // while (std::getline(testInput, testLine) && std::getline(result, resultLine)) {
    //     if (testLine == resultLine) {
    //         std::cout << "Test case passed: " << testLine << "\n";
    //     } else {
    //         std::cout << "Test case failed: " << testLine << " != " << resultLine << "\n";
    //     }
    // }

    // if (testInput.eof() && result.eof()) {
    //     std::cout << "All test cases passed!\n";
    // } else {
    //     std::cout << "Test case count mismatch.\n";
    // }

    // testInput.close();
    // result.close();
    return 0;
}
// ==================================================================

/**
 * Hàm khởi tạo mặc định: Tạo số 0
 */
BigInteger::BigInteger() {
    number = "0";
    negative = false;
}

/**
 * Hàm khởi tạo từ chuỗi: Chuyển đổi chuỗi thành số nguyên lớn
 * @param s: Chuỗi đại diện cho số nguyên (có thể có dấu -)
 */
BigInteger::BigInteger(const std::string &s) {
    if (s.empty()) {
        number = "0";
        negative = false;
        return;
    }

    std::string s_val = s;
    if (s_val[0] == '-') {
        negative = true;
        s_val = s_val.substr(1);  // Bỏ dấu trừ ở đầu
    } else {
        negative = false;
    }

    number = s_val;
    normalizeString();  // Chuẩn hóa chuỗi số

    if (number == "0") {  // Số 0 luôn là số dương
        negative = false;
    }
}

/**
 * Hàm khởi tạo sao chép: Tạo bản sao của một số nguyên lớn khác
 * @param other: Số nguyên lớn cần sao chép
 */
BigInteger::BigInteger(const BigInteger &other) {
    number = other.number;
    negative = other.negative;
}

/**
 * Toán tử gán: Gán giá trị của một số nguyên lớn khác
 * @param other: Số nguyên lớn cần gán
 * @return: Tham chiếu đến đối tượng hiện tại
 */
BigInteger& BigInteger::operator=(const BigInteger &other) {
    if (this != &other) {
        number = other.number;
        negative = other.negative;
    }
    return *this;
}

/**
 * Hàm hủy: Giải phóng tài nguyên. Tuân thủ Rule of Three nên mới có (không cần làm gì trong trường hợp này)
 */
BigInteger::~BigInteger() {}

/**
 * Kiểm tra số có bằng 0 không
 * @return: true nếu số bằng 0, false nếu khác 0
 */
bool BigInteger::isZero() const {
    return number == "0";
}

/**
 * Chuẩn hóa chuỗi số: Loại bỏ các số 0 đứng đầu
 */
void BigInteger::normalizeString() {
    // Loại bỏ các số 0 đứng đầu
    while (number.size() > 1 && number[0] == '0') {
        number.erase(0, 1);
    }
    if (number == "") {
        number = "0";
        negative = false;  // Số 0 luôn là số dương
    }
}

/**
 * Phép cộng giá trị tuyệt đối của hai số nguyên lớn
 * @param other: Số nguyên lớn thứ hai
 * @return: Kết quả của phép cộng (không tính dấu)
 */
BigInteger BigInteger::addAbs(const BigInteger &other) const {
    std::string result = "";
    int carry = 0;
    int maxLength = std::max(number.size(), other.number.size());
    
    // Duyệt qua từng chữ số từ phải qua trái (chữ số có trọng số thấp nhất đến cao nhất)
    for (int i = 0; i < maxLength || carry; ++i) {
        int digitA = (i < number.size()) ? number[number.size() - 1 - i] - '0' : 0;
        int digitB = (i < other.number.size()) ? other.number[other.number.size() - 1 - i] - '0' : 0;
        int sum = digitA + digitB + carry;
        result = std::string(1, (sum % 10) + '0') + result;  // Thêm chữ số kết quả vào đầu chuỗi
        carry = sum / 10;  // Tính nhớ cho bước tiếp theo
    }
    
    return BigInteger(result);
}

/**
 * Phép trừ giá trị tuyệt đối của hai số nguyên lớn (giả sử số thứ nhất lớn hơn hoặc bằng số thứ hai)
 * @param other: Số nguyên lớn trừ đi
 * @return: Kết quả của phép trừ (không tính dấu)
 */
BigInteger BigInteger::subtractAbs(const BigInteger &other) const {
    std::string result = "";
    int borrow = 0;
    
    // Duyệt qua từng chữ số từ phải qua trái
    for (int i = 0; i < number.size(); ++i) {
        int digitA = number[number.size() - 1 - i] - '0';
        int digitB = (i < other.number.size()) ? other.number[other.number.size() - 1 - i] - '0' : 0;
        int diff = digitA - digitB - borrow;
        
        if (diff < 0) {
            diff += 10;  // Mượn 1 từ chữ số bên trái
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result = std::string(1, diff + '0') + result;  // Thêm chữ số kết quả vào đầu chuỗi
    }
    
    return BigInteger(result);
}

/**
 * Toán tử so sánh bằng
 * @param other: Số nguyên lớn cần so sánh
 * @return: true nếu hai số bằng nhau, false nếu khác nhau
 */
bool BigInteger::operator==(const BigInteger &other) const {
    return (number == other.number && negative == other.negative);
}

/**
 * Toán tử so sánh lớn hơn hoặc bằng
 * @param other: Số nguyên lớn cần so sánh
 * @return: true nếu số hiện tại lớn hơn hoặc bằng other, false nếu ngược lại
 */
bool BigInteger::operator>=(const BigInteger &other) const {
    if (number.size() != other.number.size()) {
        return number.size() > other.number.size();
    }
    
    if (number == other.number) {
        return negative == other.negative;  // Cùng dấu thì bằng nhau
    }
    
    return number > other.number;  // So sánh chuỗi số (giá trị tuyệt đối)
}

/**
 * Toán tử so sánh nhỏ hơn
 * @param other: Số nguyên lớn cần so sánh
 * @return: true nếu số hiện tại nhỏ hơn other, false nếu ngược lại
 */
bool BigInteger::operator<(const BigInteger &other) const {
    return !(*this >= other);  // Đối lập với >=
}

/**
 * So sánh giá trị tuyệt đối lớn hơn hoặc bằng
 * @param other: Số nguyên lớn cần so sánh
 * @return: true nếu giá trị tuyệt đối của số hiện tại lớn hơn hoặc bằng giá trị tuyệt đối của other
 */
bool BigInteger::compareAbsGreaterEqual(const BigInteger &other) const {
    if (number.size() != other.number.size()) {
        return number.size() > other.number.size();
    }
    return number >= other.number;  // So sánh chuỗi số (giá trị tuyệt đối)
}

/**
 * Toán tử cộng hai số nguyên lớn
 * @param other: Số nguyên lớn cần cộng
 * @return: Kết quả của phép cộng
 */
BigInteger BigInteger::operator+(const BigInteger &other) const {
    if (negative == other.negative) {
        // Nếu hai số cùng dấu, cộng giá trị tuyệt đối và giữ dấu
        BigInteger res = addAbs(other);
        res.negative = negative;
        if (res.isZero()) res.negative = false;  // Đảm bảo 0 không âm
        return res;
    } else {
        // Nếu hai số khác dấu, thực hiện phép trừ
        if (this->isZero()) return other;
        if (other.isZero()) return *this;

        // Sử dụng hàm so sánh giá trị tuyệt đối
        if (this->compareAbsGreaterEqual(other)) {
            // |this| >= |other|
            BigInteger res = subtractAbs(other);  // |this| - |other|
            res.negative = this->negative;  // Dấu của kết quả theo số có giá trị tuyệt đối lớn hơn
            if (res.isZero()) res.negative = false;
            return res;
        } else {
            // |this| < |other|
            BigInteger res = other.subtractAbs(*this);  // |other| - |this|
            res.negative = other.negative;  // Dấu của kết quả theo số có giá trị tuyệt đối lớn hơn
            if (res.isZero()) res.negative = false;
            return res;
        }
    }
}

/**
 * Toán tử trừ hai số nguyên lớn
 * @param other: Số nguyên lớn bị trừ
 * @return: Kết quả của phép trừ
 */
BigInteger BigInteger::operator-(const BigInteger &other) const {
    BigInteger temp = other;
    temp.negative = !temp.negative;  // Đổi dấu của số bị trừ
    return *this + temp;  // Chuyển phép trừ thành phép cộng
}

/**
 * Phép nhân số nguyên lớn theo cách thông thường (schoolbook)
 * @param num: Số nguyên lớn thứ hai trong phép nhân
 * @return: Kết quả của phép nhân
 */
BigInteger BigInteger::schoolbookMultiply(const BigInteger& num) const {
    // Xử lý trường hợp một trong hai số bằng 0
    if (this->isZero() || num.isZero()) {
        return BigInteger("0");
    }
    
    BigInteger result;
    result.number.assign(this->number.size() + num.number.size(), '0');
    
    // Duyệt qua từng chữ số của số thứ nhất (từ phải qua trái trong biểu diễn chuỗi)
    for (size_t i = 0; i < this->number.size(); ++i) {
        int carry = 0;
        // Duyệt qua từng chữ số của số thứ hai và số nhớ còn lại
        for (size_t j = 0; j < num.number.size() || carry; ++j) {
            // Tính vị trí trong kết quả
            size_t pos = i + j;
            
            // Lấy các chữ số (số được lưu trữ với chữ số có giá trị lớn nhất ở vị trí 0)
            int digit1 = this->number[this->number.size() - 1 - i] - '0';
            int digit2 = (j < num.number.size()) ? num.number[num.number.size() - 1 - j] - '0' : 0;
            
            // Tính giá trị tại vị trí hiện tại: chữ số kết quả hiện tại + (digit1 * digit2) + carry
            long long cur = (result.number[result.number.size() - 1 - pos] - '0') + 
                          digit1 * 1LL * digit2 + carry;
            
            // Cập nhật kết quả tại vị trí này
            result.number[result.number.size() - 1 - pos] = (cur % 10) + '0';
            carry = cur / 10;  // Tính nhớ cho bước tiếp theo
        }
    }
    
    // Loại bỏ các số 0 đứng đầu
    while (result.number.size() > 1 && result.number[0] == '0') {
        result.number.erase(0, 1);
    }
    
    // Xác định dấu - kết quả âm nếu chính xác một trong hai số đầu vào là âm
    result.negative = (this->negative != num.negative) && !result.isZero();
    return result;
}

/**
 * Phép nhân số nguyên lớn sử dụng thuật toán Karatsuba
 * Thuật toán Karatsuba nhằm giảm độ phức tạp của phép nhân xuống O(n^log2(3))
 * @param num: Số nguyên lớn thứ hai trong phép nhân
 * @return: Kết quả của phép nhân
 */
BigInteger BigInteger::karatsubaMultiply(const BigInteger& num) const {
    if (this->isZero() || num.isZero()) {
        return BigInteger("0");
    }

    // Đảm bảo cả hai số đều dương cho thuật toán
    BigInteger a = *this;
    BigInteger b = num;
    a.negative = false;
    b.negative = false;

    int n = std::max(a.number.size(), b.number.size());
    
    // Trường hợp cơ sở: sử dụng phép nhân thông thường cho số nhỏ
    if (n < 10) {
        return a.schoolbookMultiply(b);
    }

    // Làm cho n chẵn bằng cách thêm số 0 vào đầu nếu cần
    if (n % 2 != 0) {
        n++;
    }
    a.number = std::string(n - a.number.size(), '0') + a.number;
    b.number = std::string(n - b.number.size(), '0') + b.number;

    int half = n / 2;

    // Chia các số thành phần cao và phần thấp
    BigInteger a_high(a.number.substr(0, half));  // Phần cao của a
    BigInteger a_low(a.number.substr(half));      // Phần thấp của a
    BigInteger b_high(b.number.substr(0, half));  // Phần cao của b
    BigInteger b_low(b.number.substr(half));      // Phần thấp của b

    // Ba phép nhân đệ quy
    BigInteger z0 = a_low.karatsubaMultiply(b_low);                  // z0 = a_low * b_low
    BigInteger z1 = (a_low + a_high).karatsubaMultiply(b_low + b_high);  // z1 = (a_low + a_high) * (b_low + b_high)
    BigInteger z2 = a_high.karatsubaMultiply(b_high);                // z2 = a_high * b_high

    // Tính phần ở giữa
    BigInteger middle = z1 - z2 - z0;  // middle = z1 - z2 - z0 = a_low * b_high + a_high * b_low

    // Kết hợp các kết quả với phép dịch phù hợp: result = z2 * 10^(2*half) + middle * 10^half + z0
    std::string z2_str = z2.number + std::string(2 * half, '0');  // z2 * 10^(2*half)
    std::string middle_str = middle.number + std::string(half, '0');  // middle * 10^half
    
    BigInteger result(BigInteger(z2_str) + BigInteger(middle_str) + z0);
    // Xác định dấu của kết quả
    result.negative = (this->negative != num.negative);
    result.normalizeString();  // Chuẩn hóa kết quả
    
    return result;
}

/**
 * Toán tử nhân hai số nguyên lớn
 * Chọn thuật toán phù hợp (thông thường hoặc Karatsuba) dựa trên kích thước của các số
 * @param other: Số nguyên lớn thứ hai trong phép nhân
 * @return: Kết quả của phép nhân
 */
BigInteger BigInteger::operator*(const BigInteger &other) const {
    const int KARATSUBA_THRESHOLD = 4;  // Ngưỡng để sử dụng thuật toán Karatsuba

    if (this->isZero() || other.isZero()) {
        return BigInteger("0");
    }

    std::string s1 = this->number;
    std::string s2 = other.number;
    int len1 = s1.length();
    int len2 = s2.length();

    if (len1 < KARATSUBA_THRESHOLD || len2 < KARATSUBA_THRESHOLD) {
        // Với số nhỏ, phép nhân thông thường nhanh hơn do Karatsuba có chi phí khởi tạo lớn
        return this->schoolbookMultiply(other);
    }

    // Với số lớn, sử dụng thuật toán Karatsuba
    return this->karatsubaMultiply(other);
}

/**
 * Toán tử chia hai số nguyên lớn
 * @param other: Số nguyên lớn chia (số chia)
 * @return: Kết quả của phép chia (phần nguyên)
 */
BigInteger BigInteger::operator/(const BigInteger &other) const {
    // Kiểm tra chia cho 0
    if (other.isZero()) {
        throw std::runtime_error("Division by zero");
    }
    // 0 chia cho bất kỳ số nào khác 0 đều bằng 0
    if (this->isZero()) {
        return BigInteger("0");
    }

    // Lấy giá trị tuyệt đối của số bị chia và số chia
    BigInteger dividend_abs = abs(*this);  // Giá trị tuyệt đối của số bị chia
    BigInteger divisor_abs = abs(other);   // Giá trị tuyệt đối của số chia

    // Trường hợp đặc biệt: nếu |số bị chia| < |số chia|, kết quả là 0
    if (divisor_abs >= dividend_abs) { 
        return BigInteger("0");
    }
    // Trường hợp đặc biệt: nếu |số bị chia| = |số chia|, kết quả là 1 (có dấu tùy theo dấu của đầu vào)
    if (divisor_abs == dividend_abs) {
        BigInteger res("1");
        res.negative = (this->negative != other.negative);  // Dấu khác nhau thì âm
        return res;
    }
    
    std::string quotient_str = "";  // Chuỗi kết quả thương
    BigInteger current_dividend_part; 
    // Khởi tạo phần đang xét của số bị chia là chuỗi rỗng
    current_dividend_part.number = ""; 

    // Duyệt qua các chữ số của số bị chia từ trái sang phải
    for (char digit_char : dividend_abs.number) {
        // Nếu phần đang xét là "0", reset nó để chỉ lấy chữ số mới
        if (current_dividend_part.isZero() && current_dividend_part.number == "0") { 
            current_dividend_part.number = "";
        }
        current_dividend_part.number += digit_char;  // Thêm chữ số tiếp theo vào phần đang xét
        current_dividend_part.normalizeString();  // Chuẩn hóa phần đang xét (ví dụ "05" thành "5")

        int q_digit = 0;  // Chữ số thương cho bước này
        // Chỉ thực hiện chia nếu phần đang xét >= số chia
        if (abs(current_dividend_part) >= divisor_abs) {
            // Tìm chữ số q_digit (0-9) lớn nhất sao cho divisor_abs * q_digit <= current_dividend_part
            // Sử dụng tìm kiếm nhị phân để tìm chữ số q_digit
            int low = 0, high = 9;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                BigInteger prod = divisor_abs * BigInteger(std::to_string(mid));  // Nhân thử
                if (current_dividend_part >= prod) {
                    q_digit = mid;  // mid là một chữ số thương có thể
                    low = mid + 1;  // Thử chữ số lớn hơn
                } else {
                    high = mid - 1;  // Tích quá lớn, thử chữ số nhỏ hơn
                }
            }
            // Cập nhật phần còn lại của current_dividend_part
            current_dividend_part = current_dividend_part - (divisor_abs * BigInteger(std::to_string(q_digit)));
        }
        quotient_str += std::to_string(q_digit);  // Thêm chữ số thương vào kết quả
    }

    // Tạo số nguyên lớn từ chuỗi thương
    BigInteger final_quotient(quotient_str); 
    final_quotient.negative = (this->negative != other.negative);  // Xác định dấu của kết quả
    // Đảm bảo 0 không bao giờ âm
    if (final_quotient.isZero()) {
        final_quotient.negative = false;
    }
    
    return final_quotient;
}

/**
 * Hàm chuyển đổi chuỗi đầu vào thành mảng các token
 * @param str: Chuỗi biểu thức đầu vào
 * @return: Mảng các token (số, toán tử, dấu ngoặc)
 */
std::vector<std::string> tokenInit(const std::string& str) {
    std::vector<std::string> tokens;
    std::string current_token_buffer;  // Bộ đệm để xây dựng token số hoặc token có thể dài hơn 1 ký tự

    for (int i = 0; i < str.length(); ++i) {
        char currentChar = str[i];

        // 1. Bỏ qua khoảng trắng
        if (std::isspace(currentChar)) {
            continue;  // Chuyển sang ký tự tiếp theo
        }

        // 2. Nếu là chữ số: Bắt đầu hoặc tiếp tục một token số
        if (std::isdigit(currentChar)) {
            current_token_buffer.clear();  // Xóa bộ đệm nếu có token cũ
            current_token_buffer += currentChar;
            // Đọc tất cả các chữ số liên tiếp
            while (i + 1 < str.length() && std::isdigit(str[i + 1])) {
                i++;
                current_token_buffer += str[i];
            }
            tokens.push_back(current_token_buffer);
        }
        // 3. Nếu là toán tử hoặc dấu ngoặc đơn ký tự
        else if (currentChar == '+' || currentChar == '*' || currentChar == '/' || currentChar == '(' || currentChar == ')') {
            tokens.push_back(std::string(1, currentChar));  // Chuyển char thành string 1 ký tự
        }
        // 4. Xử lý dấu trừ '-' (có thể là toán tử trừ hoặc dấu của số âm)
        else if (currentChar == '-') {
            // Kiểm tra xem nó là dấu âm (unary minus) hay phép trừ (binary minus)
            // Dấu '-' là unary minus nếu:
            //   a. Nó ở đầu biểu thức (tokens rỗng)
            //   b. Hoặc token ngay trước nó là một toán tử khác hoặc dấu mở ngoặc.
            if (tokens.empty() ||
                tokens.back() == "(" ||
                tokens.back() == "+" ||
                tokens.back() == "-" ||  // Trường hợp này cần cẩn thận, ví dụ: 5--2. Tùy theo quy ước, có thể không cho phép.
                tokens.back() == "*" ||
                tokens.back() == "/")
            {
                // Đây là dấu âm của một số
                current_token_buffer.clear();
                current_token_buffer += currentChar;  // Thêm dấu '-'

                // Kiểm tra ký tự tiếp theo phải là số
                if (i + 1 < str.length() && std::isdigit(str[i + 1])) {
                    i++;  // Di chuyển đến chữ số đầu tiên của số âm
                    current_token_buffer += str[i];
                    // Đọc phần còn lại của số
                    while (i + 1 < str.length() && std::isdigit(str[i + 1])) {
                        i++;
                        current_token_buffer += str[i];
                    }
                    tokens.push_back(current_token_buffer);
                } else {
                    // Lỗi: Dấu trừ đứng một mình hoặc theo sau không phải là số
                    // (ví dụ: "5 - ", hoặc "5 - (")
                    tokens.clear();  // Xóa tất cả token đã đọc
                    tokens.push_back("ERROR_INVALID_MINUS");  // Đánh dấu lỗi
                    return tokens;
                }
            } else {
                // Đây là toán tử trừ (binary minus)
                tokens.push_back(std::string(1, currentChar));
            }
        }
        // 5. Ký tự không hợp lệ
        else {
            // Xử lý lỗi: gặp ký tự không được phép
            tokens.clear();
            tokens.push_back("ERROR_INVALID_CHAR");
            return tokens;
        }
    }
    return tokens;
}

/**
 * Hàm chuyển biểu thức từ dạng trung tố sang hậu tố (sử dụng thuật toán Shunting Yard)
 * @param tokens: Mảng các token biểu thức trung tố
 * @return: Mảng các token biểu thức hậu tố
 */
std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens) {
    std::vector<std::string> output;  // Hàng đợi đầu ra
    std::stack<std::string> ops;  // Ngăn xếp toán tử

    // Duyệt qua từng token
    for (const auto& token : tokens) {
        // Nếu là số (cả số dương và số âm)
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            output.push_back(token);  // Thêm trực tiếp vào đầu ra
        } 
        // Nếu là dấu mở ngoặc
        else if (token == "(") {
            ops.push(token);  // Đẩy vào ngăn xếp
        } 
        // Nếu là dấu đóng ngoặc
        else if (token == ")") {
            // Lấy toán tử ra cho đến khi gặp dấu mở ngoặc
            while (!ops.empty() && ops.top() != "(") {
                output.push_back(ops.top());
                ops.pop();
            }
            if (!ops.empty()) ops.pop();  // Loại bỏ dấu mở ngoặc
        } 
        // Nếu là toán tử
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            // Lấy các toán tử có độ ưu tiên cao hơn hoặc bằng từ ngăn xếp
            while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                if (ops.top() == "(") break;  // Không lấy dấu mở ngoặc
                output.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);  // Đẩy toán tử hiện tại vào ngăn xếp
        } 
        // Token không hợp lệ
        else {
            return {"ERROR_INVALID_TOKEN"};
        }
    }

    // Lấy tất cả toán tử còn lại từ ngăn xếp
    while (!ops.empty()) {
        if (ops.top() == "(") return {"ERROR_INVALID_PARENTHESIS"};  // Nếu còn dấu mở ngoặc, coi như lỗi
        output.push_back(ops.top());
        ops.pop();
    }

    return output;
}

/**
 * Hàm xác định độ ưu tiên của các toán tử
 * @param op: Toán tử cần xác định độ ưu tiên
 * @return: Độ ưu tiên của toán tử (càng lớn càng ưu tiên)
 */
int precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;  // Độ ưu tiên thấp nhất
    if (op == "*" || op == "/") return 2;  // Độ ưu tiên cao hơn
    return 0;  // Toán tử không hợp lệ hoặc dấu ngoặc
}

/**
 * Hàm tính giá trị của biểu thức hậu tố
 * @param tokens: Mảng các token biểu thức hậu tố
 * @return: Giá trị của biểu thức
 */
BigInteger calculatePostfix(const std::vector<std::string>& tokens) {
    std::stack<BigInteger> stack;  // Ngăn xếp để lưu các giá trị trung gian

    // Duyệt qua từng token
    for (const auto& token : tokens) {
        // Nếu là số (cả số dương và số âm)
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1]))) {
            stack.push(BigInteger(token));  // Đẩy số vào ngăn xếp
        } 
        // Nếu là toán tử
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            // Kiểm tra có đủ toán hạng không
            if (stack.size() < 2) throw std::runtime_error("Invalid postfix expression");
            
            // Lấy hai toán hạng từ ngăn xếp
            BigInteger b = stack.top(); stack.pop();
            BigInteger a = stack.top(); stack.pop();
            BigInteger result;
            
            // Thực hiện phép tính tương ứng
            if (token == "+") {
                result = a + b;
            } else if (token == "-") {
                result = a - b;
            } else if (token == "*") {
                result = a * b;
            } else if (token == "/") {
                result = a / b;
            }

            // Đẩy kết quả vào ngăn xếp
            stack.push(result);
        } else {
            // Token không hợp lệ
            throw std::runtime_error("Invalid token in postfix expression");
        }
    }

    // Kiểm tra xem biểu thức có hợp lệ không (ngăn xếp phải chỉ còn 1 phần tử)
    if (stack.size() != 1) {
        throw std::runtime_error("Invalid postfix expression");
    }

    // Kết quả cuối cùng là phần tử duy nhất còn lại trong ngăn xếp
    return stack.top();
}

/**
 * Hàm lấy giá trị tuyệt đối của một số nguyên lớn
 * @param num: Số nguyên lớn cần lấy giá trị tuyệt đối
 * @return: Giá trị tuyệt đối của số
 */
BigInteger abs(const BigInteger &num) {
    BigInteger result = num;
    result.negative = false;  // Đặt dấu của kết quả là dương
    return result;
}