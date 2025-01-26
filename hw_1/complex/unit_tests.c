#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(Complex, Add) {
        Complex a = {2.0, 3.0}, b = {4.0, -5.0};
        Complex result = add(a, b);
        EXPECT_EQ(result.real, 6.0);
        EXPECT_EQ(result.im, -2.0);
    }

    TEST(Complex, Negate) {
        Complex a = {2.0, -3.0};
        Complex result = negate(a);
        EXPECT_EQ(result.real, -2.0);
        EXPECT_EQ(result.im, 3.0);
    }

    TEST(Complex, Multiply) {
        Complex a = {1.0, 2.0}, b = {3.0, 4.0};
        Complex result = multiply(a, b);
        EXPECT_EQ(result.real, -5.0);
        EXPECT_EQ(result.im, 10.0);
    }

    TEST(Complex, Magnitude) {
        Complex a = {3.0, 4.0};
        double result = magnitude(a);
        EXPECT_EQ(result, 5.0);
    }

}
