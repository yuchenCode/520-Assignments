#include <math.h>
#include "complex.h"

// Returns the magnitude (absolute value) of the complex number
double Complex::magnitude() const {
    return sqrt(re * re + im * im);
}

// Returns the real part
double Complex::real() const {
    return re;
}

// Returns the imaginary part
double Complex::imaginary() const {
    return im;
}

// Returns the complex conjugate
Complex Complex::conjugate() const {
    return Complex(re, -im);
}

// Overloads the + operator for complex addition
Complex Complex::operator+(const Complex& other) const {
    return Complex(re + other.re, im + other.im);
}

// Overloads the * operator for complex multiplication
Complex Complex::operator*(const Complex& other) const {
    return Complex(re * other.re - im * other.im, re * other.im + im * other.re);
}

// Overloads the == operator for equality comparison
bool Complex::operator==(const Complex& other) const {
    return (re == other.re) && (im == other.im);
}
