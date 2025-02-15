#ifndef COMPLEX
#define COMPLEX

#include <iostream>

class Complex {
public:
    Complex(double x, double y) : re(x), im(y) {}
    Complex(double a) : re(a), im(0) {}

    double magnitude() const;
    double real() const;         // Returns the real part
    double imaginary() const;    // Returns the imaginary part
    Complex conjugate() const;   // Returns the complex conjugate

    // Operator Overloads
    Complex operator+(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    bool operator==(const Complex& other) const;

private:
    double re, im;
};

#endif
