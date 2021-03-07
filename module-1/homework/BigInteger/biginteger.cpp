#include "biginteger.h"

void reverse(std::string::iterator first, std::string::iterator last) {
    while ((first != last) && (first != --last)) {
        std::iter_swap(first++, last);
    }
}

void BigInteger::trim() {
    while (figures.size() > 1 && figures.back() == 0) {
        figures.pop_back();
    }

    if(figures.size() == 1 && figures.front() == 0) {
        sign = false;
    }
}

BigInteger::BigInteger() {
    sign = false;
    figures.push_back(0);
}

BigInteger::BigInteger(std::string str) {
    if (str.empty()) {
        BigInteger();
    }
    else {
        if(str[0] == '-') {
            sign = true;
            str = str.substr(1);
        }
        else {
            sign = false;
        }

        for (int i = str.size(); i > 0; i -= BigInteger::BASE_LENGTH) {
            if (i < BigInteger::BASE_LENGTH) {
                figures.push_back(std::atoi(str.substr(0, i).c_str()));
            }
            else {
                figures.push_back(std::atoi(
                        str.substr(i - BigInteger::BASE_LENGTH, BigInteger::BASE_LENGTH).c_str()));
            }
        }

        trim();
    }
}

BigInteger::BigInteger(signed int n) {
    sign = (n < 0);

    while (n) {
        figures.push_back(std::abs(n) % BigInteger::BASE);
        n /= BigInteger::BASE;
    }
}

BigInteger::BigInteger(unsigned int n) {
    sign = false;
    while (n) {
        figures.push_back(n % BigInteger::BASE);
        n /= BigInteger::BASE;
    }
}

BigInteger::BigInteger(const BigInteger& other) {
    sign = other.sign;
    figures = other.figures;
}

std::istream &operator>>(std::istream &is, BigInteger &n) {
    std::string str;
    is >> str;
    n = BigInteger(str);
    return is;
}

std::ostream &operator<<(std::ostream& os, const BigInteger &n) {
    if (n.sign) {
        os << '-';
    }

    os << n.figures.back();
    int tmp = 0;
    std::string str;
    for (int i = n.figures.size() - 2; i >= 0; i--) {
        str = "";
        tmp = n.figures[i];
        while (tmp != 0) {
            str.push_back(char('0' + tmp % 10));
            tmp /= 10;
        }

        while (str.size() < BigInteger::BASE_LENGTH) {
            str.push_back('0');
        }
        reverse(str.begin(), str.end());
        os << str;
    }

    return os;
}

bool operator==(const BigInteger& l, const BigInteger& r) {
    return l.sign == r.sign && l.figures == r.figures;
}

bool operator!=(const BigInteger& l, const BigInteger& r) {
    return !(l == r);
}

bool operator<(const BigInteger& l, const BigInteger& r) {
    if(l.sign != r.sign) {
        return l.sign > r.sign;
    }

    bool negative = l.sign == 1;
    if (l.figures.size() != r.figures.size()) {
        return negative ^ (l.figures.size() < r.figures.size());
    }
    for(size_t i = l.figures.size() - 1; i >= 0; i--) {
        if(l.figures[i] != r.figures[i]) {
            return negative ^ (l.figures[i] < r.figures[i]);
        }
    }

    return false;
}

bool operator<=(const BigInteger& l, const BigInteger& r) {
    return l == r || l < r;
}

bool operator>(const BigInteger& l, const BigInteger& r) {
    return !(l <= r);
}

bool operator>=(const  BigInteger& l, const BigInteger& r) {
    return !(l < r);
}

const BigInteger BigInteger::operator-() const {
    BigInteger copy(*this);
    copy.sign = !copy.sign;
    return copy;
}

BigInteger& BigInteger::operator+=(const BigInteger& r) {
    if (sign && !r.sign) {
        return *this = r - (-(*this));
    }
    else if (!sign && r.sign) {
        return *this = *this - (-r);
    }

    int carry = 0;
    for (size_t i = 0; i < std::max(figures.size(), r.figures.size()) || carry; i++) {
        if (i == figures.size()) {
            figures.push_back(0);
        }
        figures[i] += (i < r.figures.size() ? r.figures[i] : 0) + carry;
        carry = figures[i] / BigInteger::BASE;
        figures[i] %= BigInteger::BASE;
    }

    return *this;
}

const BigInteger BigInteger::operator+(const BigInteger& r) const {
    BigInteger out = *this;
    out += r;
    return out;
}

BigInteger& BigInteger::operator-=(const BigInteger& r) {
    if(r.sign) {
        return *this = *this + (-r);
    }
    else if(sign) {
        return *this = r + (-(*this));
    }
    else if(*this < r) {
        return *this = -(r - *this);
    }

    int carry = 0;
    for (size_t i = 0; i < std::max(figures.size(), r.figures.size()) || carry; i++) {
        figures[i] -= carry + (i < r.figures.size() ? r.figures[i] : 0);
        carry = figures[i] < 0;
        figures[i] += figures[i] < 0 ? BigInteger::BASE : 0;
    }

    trim();
    return *this;
}

const BigInteger BigInteger::operator-(const BigInteger& r) const {
    BigInteger out(*this);
    out -= r;
    return out;
}

BigInteger& BigInteger::operator*=(const BigInteger& r) {
    BigInteger l;
    l.figures.resize(figures.size() + r.figures.size());

    long long carry = 0;
    for (size_t i = 0; i < figures.size(); i++) {
        for (size_t j = 0; j < r.figures.size() || carry; j++) {
            long long cur = l.figures[i + j] + figures[i] * (j < r.figures.size() ? r.figures[j] : 0) + carry;
            l.figures[i + j] = cur % BigInteger::BASE;
            carry = cur / BigInteger::BASE;
        }
    }

    l.trim();
    figures = l.figures;
    sign != r.sign;
    return *this;
}

const BigInteger BigInteger::operator*(const BigInteger& r) const {
    BigInteger out(*this);
    out *= r;
    return out;
}

void BigInteger::shift_fight() {
    if (figures.empty()) {
        figures.push_back(0);
        return;
    }

    figures.push_back(figures[figures.size() - 1]);
    for (int i = figures.size() - 2; i > 0; i--) {
        figures[i] = figures[i - 1];
    }

    figures[0] = 0;
}

BigInteger& BigInteger::operator/=(const BigInteger& r) {
    if (r == BigInteger(0)) {
        throw std::logic_error("division by zero");
    }

    BigInteger base = r;
    base.sign = false;
    BigInteger res, cur;
    res.figures.resize(figures.size());

    for (size_t i = 1; i <= figures.size(); i++) {
        cur.shift_fight();
        cur.figures[0] = figures[figures.size() - i];
        cur.trim();

        int ans = 0;
        int left = 0;
        int right = BigInteger::BASE;
        int middle;

        while (left <= right) {
            middle = (left + right) / 2;
            if (base * BigInteger(middle) <= cur) {
                ans = middle;
                left = middle + 1;
            }
            else {
                right = middle - 1;
            }
        }

        res.figures[figures.size() - i] = ans;
        cur = cur - base * BigInteger(ans);
    }

    res.sign = sign != r.sign;
    res.trim();
    return *this = res;
}

const BigInteger BigInteger::operator/(const BigInteger& r) const {
    BigInteger out(*this);
    out /= r;
    return out;
}

BigInteger& BigInteger::operator%=(const BigInteger& r) {
    *this -= (*this / r) * r;
    if (sign) {
        *this += r;
    }
    return *this;
}

const BigInteger BigInteger::operator%(const BigInteger& r) const {
    BigInteger out(*this);
    out %= r;
    return out;
}

BigInteger& BigInteger::operator++() {
    return *this = (*this += BigInteger(1));
}

BigInteger BigInteger::operator++(int) {
    *this += BigInteger(1);
    return (*this - BigInteger(1));
}

BigInteger& BigInteger::operator--() {
    return *this = (*this -= BigInteger(1));
}

BigInteger BigInteger::operator--(int) {
    *this -= BigInteger(1);
    return (*this + BigInteger(1));
}

BigInteger::operator bool() const {
    return *this != BigInteger(0);
}

BigInteger::operator std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}
