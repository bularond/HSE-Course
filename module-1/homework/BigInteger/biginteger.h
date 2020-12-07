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
//    void shright();

//    static const BigInteger commonMult(const BigInteger&, const BigInteger&);
//    static const BigInteger shortPower(const BigInteger& a, int n);

private:
    static const int BASE = 100;
    static const int BASE_LENGTH = 2;
    bool sign{false};

    std::vector<int> figures;
};
