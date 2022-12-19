#include "bigint.hpp"

int main() {
    BigInt a, b;
    std::cin >> a >> b;
    a += b;
    std::cout << a << ' ' << b << std::endl;
    a = a + b;
    std::cout << a << ' ' << b << std::endl;
    a = a - b;
    std::cout << a << ' ' << b << std::endl;
    a -= b;
    a -= b;
    std::cout << a << ' ' << b << std::endl;
    std::cout << (a < b) << ' ' << abs(a) << std::endl;
    a += b;
    a += b;
    std::cout << a << ' ' << b << std::endl;
    a *= b;
    std::cout << a << ' ' << b << std::endl;
    a /= -1000000000;
    std::cout << a << ' ' << b << std::endl;
    return 0;
}
