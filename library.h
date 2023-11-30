#ifndef LIBRARY_H
#define LIBRARY_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <QString>

class BigInteger {
private:
    std::vector<int> digits;
    bool isNegative;

    BigInteger negate() const {
        BigInteger negated = *this;
        negated.isNegative = !negated.isNegative;
        return negated;
    }

public:
    BigInteger() {}

    BigInteger(const std::string& numStr) {
        isNegative = (numStr[0] == '-');

        // Nếu số âm, bỏ qua dấu "-"
        for (int i = numStr.size() - 1; i >= (isNegative ? 1 : 0); --i) {
            digits.push_back(numStr[i] - '0');
        }
    }

    QString toQString() const {
        QString result;
        for (int i = digits.size() - 1; i >= 0; --i) {
            result.append(QChar('0' + digits[i]));
        }
        if (isNegative) {
            result.prepend('-');
        }
        return result;
    }
    BigInteger operator+(const BigInteger& other) const {
        if (isNegative != other.isNegative) {
            if (isNegative) {
                return other - negate();
            } else {
                return *this - other.negate();
            }
        }

        BigInteger result;
        int carry = 0;

        for (size_t i = 0; i < std::max(digits.size(), other.digits.size()) || carry; ++i) {
            if (i == result.digits.size()) {
                result.digits.push_back(0);
            }

            int sum = carry + (i < digits.size() ? digits[i] : 0) + (i < other.digits.size() ? other.digits[i] : 0);
            result.digits[i] = sum % 10;
            carry = sum / 10;
        }

        result.isNegative = isNegative;

        return result;
    }
    BigInteger operator-(const BigInteger& other) const {
        if (isNegative != other.isNegative) {
            if (isNegative) {
                return negate() + other;
            } else {
                return *this + other.negate();
            }
        }

        BigInteger result;
        int borrow = 0;

        for (size_t i = 0; i < std::max(digits.size(), other.digits.size()); ++i) {
            int diff = (i < digits.size() ? digits[i] : 0) - (i < other.digits.size() ? other.digits[i] : 0) - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result.digits.push_back(diff);
        }

        // Xác định dấu
        result.isNegative = (isNegative && (result.digits.back() != 0));

        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }

        return result;
    }
    BigInteger operator*(const BigInteger& other) const {
        BigInteger result;
        result.digits.resize(digits.size() + other.digits.size(), 0);

        for (size_t i = 0; i < digits.size(); ++i) {
            int carry = 0;

            for (size_t j = 0; j < other.digits.size() || carry; ++j) {
                long long current = result.digits[i + j] +
                                    static_cast<long long>(digits[i]) * (j < other.digits.size() ? other.digits[j] : 0) +
                                    carry;

                result.digits[i + j] = current % 10;
                carry = current / 10;
            }
        }
        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }

        return result;
    }
    BigInteger operator/(const BigInteger& other) const {
        if (other == BigInteger("0")) {
            throw std::runtime_error("Division by zero");
        }

        BigInteger quotient;
        BigInteger remainder = *this;
        BigInteger divisor = other;

        while (remainder >= divisor) {
            int multiplier = 1;
            BigInteger product = divisor;

            while (remainder >= product * BigInteger("10")) {
                product = product * BigInteger("10");
                multiplier *= 10;
            }

            while (remainder >= product) {
                remainder = remainder - product;
                quotient = quotient + BigInteger(std::to_string(multiplier));
            }
        }

        return quotient;
    }
    bool operator==(const BigInteger& other) const {
        return digits == other.digits;
    }

    bool operator>(const BigInteger& other) const {
        if (digits.size() != other.digits.size()) {
            return digits.size() > other.digits.size();
        }

        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != other.digits[i]) {
                return digits[i] > other.digits[i];
            }
        }

        return false;
    }

    bool operator<(const BigInteger& other) const {
        return other > *this;
    }

    bool operator>=(const BigInteger& other) const {
        return !(*this < other);
    }

    bool operator<=(const BigInteger& other) const {
        return !(*this > other);
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const BigInteger& num) {
        for (int i = num.digits.size() - 1; i >= 0; --i) {
            os << num.digits[i];
        }
        return os;
    }
};


#endif // LIBRARY_H
