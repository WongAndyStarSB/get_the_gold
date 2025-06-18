#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <string>
#include <exception>
#include <utility>

class ZeroDivisionException : public std::exception {
    private:
        std::string default_msg = "divisor cannot be zero";
        std::string msg;
    
    public:
        ZeroDivisionException(const char* arg_message = "")
            : msg(arg_message) {
                msg = ((msg == "")? default_msg : msg);
        }
        ZeroDivisionException(const std::string arg_message)
            : msg(arg_message) {
                msg = ((msg == "")? default_msg : msg);
        }
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
        using GCF_Function_Ptr = int(*)(int n1, int n2);
        static GCF_Function_Ptr find_greatest_common_factor;

        explicit Fraction(const int& dividend = 0, const int& divisor = 1);
        inline Fraction(const Fraction& other) = default; // copy constructor
        inline Fraction(Fraction&&) noexcept = default; // move constructor

        void simplify();

        int get_numerator() const;
        int get_denominator() const;

        void set_numerator(int new_numerator);
        void set_denominator(int new_denominator);


        std::string to_string(bool add_prefix = true) const;
        float get_in_float() const;
        int floor() const;
        int ceil() const;
        std::pair<int, Fraction> get_mixed_fraction() const;

        
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