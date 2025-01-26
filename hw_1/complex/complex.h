#ifndef COMPLEX_H
#define COMPLEX_H

/*! @file */

/*! \brief Complex number structure and method definitions
 *
 * A complex number is a struct with a real part and an imaginary part.
 * Various methods are provided to perform arithmetic operations and
 * calculate the magnitude.
 */
typedef struct {
    double real;
    double im;
} Complex;

/*! Add two complex numbers
 *  \param a The first summand
 *  \param b The second summand
 */
Complex add(Complex a, Complex b);

/*! Negate a complex number
 *  \param a The complex number to negate
 */
Complex negate(Complex a);

/*! Multiply two complex numbers
 *  \param a The first term
 *  \param b The second term
 */
Complex multiply(Complex a, Complex b);

/*! Calculate the magnitude of a complex number
 *  \param a The complex number
 *  \return The magnitude as a double
 */
double magnitude(Complex a);

#endif // COMPLEX_H
