#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <string>
#include <exception>
#include <utility>
#include <cmath>

class ZeroDivisionException : public std::exception {
    private:
        std::string default_msg = "divisor cannot be zero";
        std::string msg;
    
    public:
        inline explicit ZeroDivisionException(const char* arg_message = "")
            : msg((arg_message && *arg_message) ? arg_message : default_msg) 
        {}
        inline explicit ZeroDivisionException(const std::string& arg_message = "")
            : msg(arg_message.empty() ? default_msg : arg_message) 
        {}
        inline const char* what() const throw() override {
            return msg.c_str();
        }
};

class Fraction {
    private:
        int numerator;
        int denominator;
    public:
        static int find_gcf(int n1, int n2);
        static long long find_gcf(long long n1, long long n2);
        static int default_precision;
        static Fraction get_fraction_from_double(double value, unsigned int precision = default_precision);

        explicit Fraction(const int& dividend = 0, const int& divisor = 1);
        explicit Fraction(double value, unsigned int precision = default_precision);
        inline Fraction(const Fraction& other) = default; // copy constructor
        inline Fraction(Fraction&&) noexcept = default; // move constructor

        void simplify();

        int get_numerator() const;
        int get_denominator() const;

        void set_numerator(int new_numerator);
        void set_denominator(int new_denominator);


        std::string to_string(bool add_prefix = true) const;
        double get_in_double() const;
        int floor() const;
        int ceil() const;
        std::pair<int, Fraction> get_mixed_fraction() const;


        
        // Assignment operator
        Fraction& operator=(const Fraction& other);
        Fraction& operator=(int num);
        Fraction& operator=(double value);

        bool operator==(const Fraction& other) const;
        bool operator<(const Fraction& other) const;
        bool operator>(const Fraction& other) const;
        bool operator!=(const Fraction& other) const;
        bool operator<=(const Fraction& other) const;
        bool operator>=(const Fraction& other) const;
        Fraction operator+(const Fraction& other) const;
        Fraction operator-(const Fraction& other) const;
        Fraction operator*(const Fraction& other) const;
        Fraction operator/(const Fraction& other) const;

        bool operator==(const int& num) const;
        bool operator<(const int& num) const;
        bool operator>(const int& num) const;
        bool operator!=(const int& num) const;
        bool operator<=(const int& num) const;
        bool operator>=(const int& num) const;
        Fraction operator+(const int& num) const;
        Fraction operator-(const int& num) const;
        Fraction operator*(const int& num) const;
        Fraction operator/(const int& num) const;
};


#endif // FRACTION_HPP