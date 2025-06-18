#include "Fraction.hpp"
#include <string>
#include <cmath>

// static
int Fraction::find_gcf(int n1, int n2) {
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

Fraction::GCF_Function_Ptr Fraction::find_greatest_common_factor = &find_gcf;


// public
// Constructor
Fraction::Fraction(const int& dividend, const int& divisor) : numerator(dividend), denominator(divisor) {
    if (denominator == 0) {
        throw ZeroDivisionException("Fraction::Fraction ZeroDivErr: divisor cannot be 0");
    }
    simplify();
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
float Fraction::get_in_float() const {
    return static_cast<float>(numerator)/denominator;
}
int Fraction::floor() const {
    return std::floor(get_in_float());
}
int Fraction::ceil() const {
    return std::ceil(get_in_float());
}
std::pair<int, Fraction> Fraction::get_mixed_fraction() const {
    int integral_part = floor();
    return {integral_part, Fraction(numerator-integral_part*denominator, denominator)};
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
    return Fraction(numerator, denominator*num);
}




// int main() { // testing code
//     Fraction f1(1034, 893);
//     Fraction f2(19, 44);
//     Fraction f = f1 * f2;

//     std::cout << f1.numerator << ", " << f1.denominator << std::endl;
//     std::cout << f1.floor() << ", " << f1.get_mixed_fraction().second.numerator << std::endl;
//     std::cout 
//         << "float:" << f.get_in_float() << ", floor:" << f.floor() << ", ceil:" << f.ceil() 
//         << ", mixed:" << f.get_mixed_fraction().first 
//         << "+" << f.get_mixed_fraction().second.numerator << "/" << f.get_mixed_fraction().second.denominator << std::endl;
// }