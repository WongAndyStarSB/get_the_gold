#include "Fraction.hpp"
#include <string>
#include <cmath>
#include <stdexcept>

// static

int Fraction::default_precision = 6; // default precision for double to fraction conversion

int Fraction::find_gcf(int n1, int n2) {
    if (n1 == 0 && n2 == 0) {
        throw std::invalid_argument("GCF is undefined for (0, 0)");
    }
    int tmp;
    if (n1 < n2) {
        std::swap(n1, n2);
    }
    while (n2 != 0) {
        tmp = n2;
        n2 = n1 % n2;
        n1 = tmp;
    }
    return n1;
}
long long Fraction::find_gcf(long long n1, long long n2) {
    if (n1 == 0 && n2 == 0) {
        throw std::invalid_argument("GCF is undefined for (0, 0)");
    }
    long long tmp;
    if (n1 < n2) {
        std::swap(n1, n2);
    }
    while (n2 != 0) {
        tmp = n2;
        n2 = n1 % n2;
        n1 = tmp;
    }
    return n1;
}


Fraction Fraction::get_fraction_from_double(double value, unsigned int precision) {
    if (!std::isfinite(value)) {
        throw std::invalid_argument("Value must be finite");
    }
    if (precision == 0) {
        return Fraction(static_cast<int>(std::round(value)), 1);
    }
    double factor = std::pow(10, precision);
    if (std::abs(value * factor) > static_cast<double>(LLONG_MAX)) {
        throw std::overflow_error("Value is too large to convert to fraction");
    }
    long long numerator_ll = static_cast<long long>(std::round(value * factor));
    long long denominator_ll = static_cast<long long>(factor);
    if (numerator_ll == 0) {
        return Fraction(0, 1);
    }
    long long gcf = find_gcf(numerator_ll, denominator_ll);
    numerator_ll /= gcf;
    denominator_ll /= gcf;
    if (denominator_ll == 0) {
        throw std::logic_error("Fraction::get_fraction_from_double: ***Unreachable code***: denominator cannot be 0");
    }
    if (numerator_ll < INT_MAX && numerator_ll > INT_MIN &&
        denominator_ll < INT_MAX && denominator_ll > INT_MIN) {
        return Fraction(static_cast<int>(numerator_ll), static_cast<int>(denominator_ll));
    }
    throw std::runtime_error("Fraction::get_fraction_from_double: numerator or denominator exceeds int limits");
}

// public
// Constructor
Fraction::Fraction(const int& dividend, const int& divisor) : numerator(dividend), denominator(divisor) {
    if (denominator == 0) {
        throw ZeroDivisionException("Fraction::Fraction ZeroDivErr: divisor cannot be 0");
    }
    simplify();
}
Fraction::Fraction(double value, unsigned int precision) {
    Fraction tmp = get_fraction_from_double(value, precision);
    numerator = tmp.numerator;
    denominator = tmp.denominator;
}

void Fraction::simplify() {
    if (numerator == 0) {
        denominator = 1;
        return;
    }
    // move negative to numerator if there is
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    // simplify
    int gcf = find_gcf(numerator, denominator);
    numerator /= gcf;
    denominator /= gcf;
}

// member getters
int Fraction::get_numerator() const {
    return numerator;
}
int Fraction::get_denominator() const {
    return denominator;
}

// member setters
void Fraction::set_numerator(int new_numerator) {
    numerator = new_numerator;
    simplify();
}
void Fraction::set_denominator(int new_denominator) {
    if (new_denominator == 0) {
        throw ZeroDivisionException("Fraction::set_denominator ZeroDivErr: divisor cannot be 0");
    }
    denominator = new_denominator;
    simplify();
}

// other getters
std::string Fraction::to_string(bool add_prefix) const {
    return (add_prefix? "Fraction(" : "(") + std::to_string(numerator) + "/" + std::to_string(denominator) + ")";
}
double Fraction::get_in_double() const {
    return static_cast<double>(numerator)/denominator;
}
int Fraction::floor() const {
    return std::floor(get_in_double());
}
int Fraction::ceil() const {
    return std::ceil(get_in_double());
}
std::pair<int, Fraction> Fraction::get_mixed_fraction() const {
    int integral_part = floor();
    return {integral_part, Fraction(numerator-integral_part*denominator, denominator)};
}



Fraction& Fraction::operator=(const Fraction& other) {
    if (this == &other) {
        return *this; // self-assignment check
    }
    numerator = other.numerator;
    denominator = other.denominator;
    return *this;
}
Fraction& Fraction::operator=(int num) {
    numerator = num;
    denominator = 1;
    return *this;
}
Fraction& Fraction::operator=(double value) {
    Fraction tmp = get_fraction_from_double(value);
    numerator = tmp.numerator;
    denominator = tmp.denominator;
    return *this;
}


bool Fraction::operator==(const Fraction& other) const {
    return numerator==other.numerator && denominator==other.denominator;
}
bool Fraction::operator<(const Fraction& other) const {
    return numerator*other.denominator < other.numerator*denominator;
}
bool Fraction::operator>(const Fraction& other) const {
    return numerator*other.denominator > other.numerator*denominator;
}
bool Fraction::operator!=(const Fraction& other) const {
    return !operator==(other);
}
bool Fraction::operator<=(const Fraction& other) const {
    return operator<(other) || operator==(other);
}
bool Fraction::operator>=(const Fraction& other) const {
    return operator>(other) || operator==(other);
}
Fraction Fraction::operator+(const Fraction& other) const {
    return Fraction(numerator*other.denominator+other.numerator*denominator, denominator*other.denominator);
}
Fraction Fraction::operator-(const Fraction& other) const {
    return Fraction(numerator*other.denominator-other.numerator*denominator, denominator*other.denominator);
}
Fraction Fraction::operator*(const Fraction& other) const {
    return Fraction(numerator*other.numerator, denominator*other.denominator);
}
Fraction Fraction::operator/(const Fraction& other) const {
    return Fraction(numerator*other.denominator, denominator*other.numerator);
}

bool Fraction::operator==(const int& num) const {
    return denominator==1 && numerator==num;
}
bool Fraction::operator<(const int& num) const {
    return numerator < num*denominator;
}
bool Fraction::operator>(const int& num) const {
    return numerator > num*denominator;
}
bool Fraction::operator!=(const int& num) const {
    return !operator==(num);
}
bool Fraction::operator<=(const int& num) const {
    return operator<(num) || operator==(num);
}
bool Fraction::operator>=(const int& num) const {
    return operator>(num) || operator==(num);
}
Fraction Fraction::operator+(const int& num) const {
    return Fraction(numerator+num*denominator, denominator);
}
Fraction Fraction::operator-(const int& num) const {
    return Fraction(numerator-num*denominator, denominator);
}
Fraction Fraction::operator*(const int& num) const {
    return Fraction(numerator*num, denominator);
}
Fraction Fraction::operator/(const int& num) const {
    if (num == 0) {
        throw ZeroDivisionException("Fraction::operator/(int) ZeroDivErr: divisor cannot be 0");
    }
    return Fraction(numerator, denominator*num);
}




// int main() { // testing code
//     Fraction f1(1034, 893);
//     Fraction f2(19, 44);
//     Fraction f = f1 * f2;

//     std::cout << f1.numerator << ", " << f1.denominator << std::endl;
//     std::cout << f1.floor() << ", " << f1.get_mixed_fraction().second.numerator << std::endl;
//     std::cout 
//         << "float:" << f.get_in_double() << ", floor:" << f.floor() << ", ceil:" << f.ceil() 
//         << ", mixed:" << f.get_mixed_fraction().first 
//         << "+" << f.get_mixed_fraction().second.numerator << "/" << f.get_mixed_fraction().second.denominator << std::endl;
// }