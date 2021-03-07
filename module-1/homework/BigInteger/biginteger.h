#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class BigInteger {

public:
    BigInteger();
    BigInteger(std::string);
    BigInteger(signed int);
    BigInteger(unsigned int);
    BigInteger(const BigInteger&);

    friend std::istream& operator>>(std::istream&, BigInteger&);
    friend std::ostream& operator<<(std::ostream&, const BigInteger&);

    const BigInteger operator-() const;

    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger& operator--();
    BigInteger operator--(int);

    friend bool operator==(const BigInteger&, const BigInteger&);
    friend bool operator!=(const BigInteger&, const BigInteger&);
    friend bool operator<(const BigInteger&, const BigInteger&);
    friend bool operator<=(const BigInteger&, const BigInteger&);
    friend bool operator>(const BigInteger&, const BigInteger&);
    friend bool operator>=(const BigInteger&, const BigInteger&);

    BigInteger& operator+=(const BigInteger&);
    const BigInteger operator+(const BigInteger&) const;
    BigInteger& operator-=(const BigInteger&);
    const BigInteger operator-(const BigInteger&) const;
    BigInteger& operator*=(const BigInteger&);
    const BigInteger operator*(const BigInteger&)const;
    BigInteger& operator/=(const BigInteger&);
    const BigInteger operator/(const BigInteger&) const;
    BigInteger& operator%=(const BigInteger&);
    const BigInteger operator%(const BigInteger&) const;

    friend bool operator==(const BigInteger&, const BigInteger&);
    friend bool operator<(const BigInteger&, const BigInteger&);
    friend bool operator!=(const BigInteger&, const BigInteger&);
    friend bool operator<=(const BigInteger&, const BigInteger&);
    friend bool operator>(const BigInteger&, const BigInteger&);
    friend bool operator>=(const BigInteger&, const BigInteger&);

    operator bool() const;
    operator std::string() const;

    std::string toString() const { return std::string(*this); }

    void trim();

private:
    static const int BASE = 10;
    static const int BASE_LENGTH = 1;
    bool sign{false};

    std::vector<int> figures;

    void shift_fight();
};
