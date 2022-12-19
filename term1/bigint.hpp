#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class BigInt {
    bool sign;
    static const int BASE = 1000000000;
    std::vector<int> number;

public:
    explicit BigInt();
    BigInt &operator=(const BigInt &x) = default;
    BigInt &operator=(const int &x);
    BigInt &operator+=(const BigInt &x);
    BigInt &operator++();
    BigInt operator++(int);
    BigInt &operator-=(const BigInt &x);
    BigInt &operator--();
    BigInt operator--(int);
    BigInt &operator*=(const BigInt &x);
    BigInt &operator/=(const int &x);

    friend std::istream &operator>>(std::istream &in, BigInt &x);
    friend std::ostream &operator<<(std::ostream &out, const BigInt &x);
    friend bool operator<(const BigInt &x, const BigInt &y);
};

std::istream &operator>>(std::istream &in, BigInt &x);

std::ostream &operator<<(std::ostream &out, const BigInt &x);

bool operator<(const BigInt &x, const BigInt &y);

bool operator>(const BigInt &x, const BigInt &y);

bool operator==(const BigInt &x, const BigInt &y);

bool operator!=(const BigInt &x, const BigInt &y);

bool operator<=(const BigInt &x, const BigInt &y);

bool operator>=(const BigInt &x, const BigInt &y);

BigInt operator+(const BigInt &x, const BigInt &y);

BigInt operator-(const BigInt &x, const BigInt &y);

BigInt operator*(const BigInt &x, const BigInt &y);

BigInt operator/(const BigInt &x, const int &y);

BigInt abs(const BigInt &x);
