#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(TypedArray, PushPop) {
        TypedArray<int> arr;
        arr.push(1);
        arr.push(2);
        arr.push(3);

        EXPECT_EQ(arr.size(), 3);
        EXPECT_EQ(arr.pop(), 3);
        EXPECT_EQ(arr.size(), 2);
        EXPECT_EQ(arr.pop(), 2);
        EXPECT_EQ(arr.size(), 1);
        EXPECT_EQ(arr.pop(), 1);
        EXPECT_EQ(arr.size(), 0);

        // Testing popping from an empty array
        EXPECT_THROW(arr.pop(), std::range_error);
    }

    TEST(TypedArray, PushFrontPopFront) {
        TypedArray<int> arr;
        arr.push_front(1);
        arr.push_front(2);
        arr.push_front(3);

        EXPECT_EQ(arr.size(), 3);
        EXPECT_EQ(arr.pop_front(), 3);
        EXPECT_EQ(arr.size(), 2);
        EXPECT_EQ(arr.pop_front(), 2);
        EXPECT_EQ(arr.size(), 1);
        EXPECT_EQ(arr.pop_front(), 1);
        EXPECT_EQ(arr.size(), 0);

        // Testing popping from an empty array
        EXPECT_THROW(arr.pop_front(), std::range_error);
    }

    TEST(TypedArrayTests, Concat) {
        TypedArray<int> arr1;
        arr1.push(1);
        arr1.push(2);
        arr1.push(3);

        TypedArray<int> arr2;
        arr2.push(4);
        arr2.push(5);

        // Concatenate arr1 and arr2
        TypedArray<int> result = arr1.concat(arr2);

        // Test the size of the concatenated array
        EXPECT_EQ(result.size(), 5);  // 3 from arr1 and 2 from arr2

        // Test the values
        EXPECT_EQ(result.get(0), 1);
        EXPECT_EQ(result.get(1), 2);
        EXPECT_EQ(result.get(2), 3);
        EXPECT_EQ(result.get(3), 4);
        EXPECT_EQ(result.get(4), 5);
    }

    TEST(TypedArrayTests, Reverse) {
        TypedArray<int> arr;
        arr.push(1);
        arr.push(2);
        arr.push(3);

        // Reverse the array
        arr.reverse();

        // Test the reversed array
        EXPECT_EQ(arr.size(), 3);
        EXPECT_EQ(arr.get(0), 3);
        EXPECT_EQ(arr.get(1), 2);
        EXPECT_EQ(arr.get(2), 1);
    }

    TEST(TypedArrayTests, OperatorPlus) {
        TypedArray<int> arr1;
        arr1.push(1);
        arr1.push(2);

        TypedArray<int> arr2;
        arr2.push(3);
        arr2.push(4);

        // Use operator+ to concatenate arr1 and arr2
        TypedArray<int> result = arr1 + arr2;

        // Test the size of the concatenated array
        EXPECT_EQ(result.size(), 4);  // 2 from arr1 and 2 from arr2

        // Test the values
        EXPECT_EQ(result.get(0), 1);
        EXPECT_EQ(result.get(1), 2);
        EXPECT_EQ(result.get(2), 3);
        EXPECT_EQ(result.get(3), 4);
    }

    TEST(TypedArrayTests, EdgeCases) {
        TypedArray<int> arr;

        // Test concatenating with an empty array
        TypedArray<int> empty;
        TypedArray<int> result = arr.concat(empty);
        EXPECT_EQ(result.size(), 0);

        // Test reversing an empty array
        arr.reverse();
        EXPECT_EQ(arr.size(), 0);

        // Test operator+ with an empty array
        TypedArray<int> emptyResult = arr + empty;
        EXPECT_EQ(emptyResult.size(), 0);
    }

    TEST(Complex, BasicOperations) {
        Complex a(3, 4);
        EXPECT_DOUBLE_EQ(a.real(), 3.0);
        EXPECT_DOUBLE_EQ(a.imaginary(), 4.0);
        EXPECT_DOUBLE_EQ(a.magnitude(), 5.0);  // sqrt(3^2 + 4^2) = 5

        Complex b(1, -1);
        EXPECT_DOUBLE_EQ(b.real(), 1.0);
        EXPECT_DOUBLE_EQ(b.imaginary(), -1.0);
        EXPECT_DOUBLE_EQ(b.magnitude(), sqrt(2));
    }

    TEST(Complex, Conjugate) {
        Complex a(3, 4);
        Complex a_conj = a.conjugate();
        EXPECT_DOUBLE_EQ(a_conj.real(), 3.0);
        EXPECT_DOUBLE_EQ(a_conj.imaginary(), -4.0);
    }

    TEST(Complex, Addition) {
        Complex a(3, 4);
        Complex b(1, -1);
        Complex sum = a + b;
        EXPECT_DOUBLE_EQ(sum.real(), 4.0);
        EXPECT_DOUBLE_EQ(sum.imaginary(), 3.0);
    }

    TEST(Complex, Multiplication) {
        Complex a(3, 4);
        Complex b(1, -1);
        Complex product = a * b;  // (3+4i) * (1-1i) = 3 - 3i + 4i - 4 = 7 + i
        EXPECT_DOUBLE_EQ(product.real(), 7.0);
        EXPECT_DOUBLE_EQ(product.imaginary(), 1.0);
    }

    TEST(Complex, Equality) {
        Complex a(3, 4);
        Complex b(3, 4);
        Complex c(1, -1);

        EXPECT_TRUE(a == b);
        EXPECT_FALSE(a == c);
    }

}