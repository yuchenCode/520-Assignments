#include "complex.h"
#include <math.h>

Complex add(Complex a, Complex b) {
    Complex result;
    result.real = a.real + b.real;
    result.im = a.im + b.im;
    return result;
}

Complex negate(Complex a) {
    Complex result;
    result.real = -a.real;
    result.im = -a.im;
    return result;
}

Complex multiply(Complex a, Complex b) {
    Complex result;
    result.real = a.real * b.real - a.im * b.im;
    result.im = a.real * b.im + a.im * b.real;
    return result;
}

double magnitude(Complex a) {
    return sqrt(a.real * a.real + a.im * a.im);
}
