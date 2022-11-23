#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class BigInt {
    bool sign;
    std::vector<int> number;

public:
    explicit BigInt() : sign(true) {}
    BigInt &operator=(const BigInt &x) = default;
    BigInt &operator=(const int &x) {
        number.clear();
        if (x < 0) {
            sign = false;
        } else {
            sign = true;
        }
        int copy = x;
        while (copy != 0) {
            number.push_back(copy % 1000000000);
            copy = copy / 1000000000;
        }
        return *this;
    }
    
    BigInt &operator+=(const BigInt &x) {
        if (sign && !x.sign || !sign && x.sign) {
            BigInt copy_this = *this;
            copy_this.sign = true;
            BigInt copy_x = x;
            copy_x.sign = true;
            if (copy_x < copy_this) {
                copy_this -= copy_x;
                number = copy_this.number;
                return *this;
            } else {
                copy_x -= copy_this;
                number = copy_x.number;
                sign = !sign;
                return *this;
            }
        }
        int in_mind = 0;
        for (int i = 0; i < std::max(x.number.size(), number.size()) || in_mind != 0; ++i) {
            if (i >= number.size()) number.push_back(0);
            number[i] += ((i < x.number.size() ? x.number[i] : 0) + in_mind);
            in_mind = number[i] / 1000000000;
            number[i] %= 1000000000;
        }
        return *this;
    }
    BigInt operator++() {
        BigInt one;
        one.number.push_back(1);
        *this += one;
        return *this;
    }
    BigInt operator++(int) {
        BigInt copy = *this;
        ++*this;
        return copy;
    }
    
    BigInt operator-=(const BigInt &x) {
        if (!sign && x.sign) {
            sign = true;
            *this += x;
            sign = false;
            return *this;
        }
        if (sign && !x.sign) {
            BigInt copy = x;
            copy.sign = true;
            *this += copy;
            return *this;
        }
        BigInt copy_this = *this;
        copy_this.sign = true;
        BigInt copy_x = x;
        copy_x.sign = true;
        if (copy_this < copy_x) {
            sign = !sign;
            copy_x -= copy_this;
            number = copy_x.number;
            return *this;
        }
        int in_mind = 0;
        for (size_t i = 0; i < x.number.size() || in_mind != 0; ++i) {
            number[i] -= in_mind + (i < x.number.size() ? x.number[i] : 0);
            in_mind = number[i] < 0;
            if (in_mind != 0) number[i] += 1000000000;
        }
        while (number.size() > 1 && number.back() == 0)
            number.pop_back();
        return *this;
    }
    BigInt operator--() {
        BigInt one;
        one.number.push_back(1);
        *this -= one;
        return *this;
    }
    BigInt operator--(int) {
        BigInt copy = *this;
        --*this;
        return copy;
    }
    
    BigInt operator*=(const BigInt &x) {
        sign = (sign == x.sign);
        std::vector<int> result(number.size() + x.number.size());
        for (size_t i = 0; i < number.size(); ++i)
            for (int j = 0, in_mind = 0; j < (int) x.number.size() || in_mind; ++j) {
                long long cur = result[i + j] + number[i] * 1ll * (j < (int) x.number.size() ? x.number[j] : 0) + in_mind;
                result[i + j] = int(cur % 1000000000);
                in_mind = int(cur / 1000000000);
            }
        while (result.size() > 1 && result.back() == 0)
            result.pop_back();
        number.clear();
        for (int i: result)
            number.push_back(i);
        return *this;
    }
    
    BigInt operator/=(const int &x) {
        sign = (sign == (x > 0));
        int in_mind = 0;
        for (int i = (int) number.size() - 1; i >= 0; --i) {
            long long cur = number[i] + in_mind * 1ll * 1000000000;
            number[i] = int(cur / abs(x));
            in_mind = int(cur % abs(x));
        }
        while (number.size() > 1 && number.back() == 0)
            number.pop_back();
        return *this;
    }
    
    friend std::istream &operator>>(std::istream &in, BigInt &x);
    friend std::ostream &operator<<(std::ostream &out, const BigInt &x);
    friend bool operator<(const BigInt &x, const BigInt &y);
};

std::istream &operator>>(std::istream &in, BigInt &x) {
    std::string s;
    in >> s;
    if (!s.empty() && s[0] == '-') {
        x.sign = false;
        s.erase(0, 1);
    }
    for (int i = (int) s.size() - 1; i >= 0; i -= 9) {
        if (i < 8)
            x.number.push_back(std::stoi(s.substr(0, i + 1)));
        else
            x.number.push_back(std::stoi(s.substr(i - 8, 9)));
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const BigInt &x) {
    if (x.number.size() == 1 && x.number[0] == 0) {
        out << 0;
        return out;
    }
    if (!x.sign) out << '-';
    out << x.number.back();
    for (int i = (int) x.number.size() - 2; i >= 0; --i) {
        int copy = x.number[i];
        while (copy != 0 && copy < 100000000) {
            out << 0;
            copy *= 10;
        }
        if (copy == 0) out << "00000000";
        out << x.number[i];
    }
    return out;
}

bool operator<(const BigInt &x, const BigInt &y) {
    if (!x.sign && y.sign) return true;
    if (x.sign && !y.sign) return false;
    if (x.sign && y.sign) {
        if (x.number.size() != y.number.size()) return x.number.size() < y.number.size();
        for (int i = (int) x.number.size() - 1; i >= 0; --i) {
            if (x.number[i] != y.number[i]) return x.number[i] < y.number[i];
        }
    } else {
        if (x.number.size() != y.number.size()) return x.number.size() > y.number.size();
        for (int i = (int) x.number.size() - 1; i >= 0; --i) {
            if (x.number[i] != y.number[i]) return x.number[i] > y.number[i];
        }
    }
    return false;
}

bool operator>(const BigInt &x, const BigInt &y) {
    return y < x;
}

bool operator==(const BigInt &x, const BigInt &y) {
    return !(x < y || y < x);
}

bool operator!=(const BigInt &x, const BigInt &y) {
    return !(x == y);
}

bool operator<=(const BigInt &x, const BigInt &y) {
    return !(x > y);
}

bool operator>=(const BigInt &x, const BigInt &y) {
    return !(x < y);
}

BigInt operator+(const BigInt &x, const BigInt &y) {
    BigInt copy = x;
    copy += y;
    return copy;
}

BigInt operator-(const BigInt &x, const BigInt &y) {
    BigInt copy = x;
    copy -= y;
    return copy;
}

BigInt operator*(const BigInt &x, const BigInt &y) {
    BigInt copy = x;
    copy *= y;
    return copy;
}

BigInt operator/(const BigInt &x, const int &y) {
    BigInt copy = x;
    copy /= y;
    return copy;
}

BigInt abs(const BigInt &x) {
    BigInt zero;
    zero = 0;
    return x < zero ? zero - x : x;
}

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
