#include "../src/matrix.h"

int main() {
    Matrix a(3, 2);
    Matrix b{{1, 2.2, 3}, {4, 5, 6}, {70001, 8, 95}};
    a.at(1, 0) = 42;
    b.at(2, 1) = 1234.5;
    std::cout << "Matrix A: " <<  std::endl;
    std::cout << a << std::endl;
    std::cout << "Matrix B: " << std::endl;
    std::cout << b << std::endl;
    std::cout << "Value in B at 1, 2: " << b.at(1, 2) << std::endl;
    return 0;
}