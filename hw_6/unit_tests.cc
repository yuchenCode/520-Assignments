#include <gtest/gtest.h>
#include "random_process.h"
#include "filter.h"
#include "integrator.h"
#include "stopwatch.h"
#include <thread>
#include <chrono>
#include <cmath>

// Test the Stopwatch class
class StopwatchTest : public ::testing::Test {
protected:
    Stopwatch watch;
    
    // Tolerance for time-based tests (in seconds)
    const double epsilon = 0.1;
    
    // Larger tolerance for millisecond tests (in milliseconds)
    const double ms_epsilon = 100.0;
    
    bool approx_equal(double a, double b) {
        return std::abs(a - b) < epsilon;
    }
    
    bool approx_equal_ms(double a, double b) {
        return std::abs(a - b) < ms_epsilon;
    }
};

// Test that a newly constructed Stopwatch starts at zero
TEST_F(StopwatchTest, InitialValueIsZero) {
    EXPECT_DOUBLE_EQ(watch.get_seconds(), 0.0);
}

// Test the start, stop functionality
TEST_F(StopwatchTest, StartStop) {
    watch.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    watch.stop();
    
    // Check approximate equality with tolerance
    EXPECT_TRUE(approx_equal(watch.get_seconds(), 0.5));
    
    // Check that the watch stays stopped
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    EXPECT_TRUE(approx_equal(watch.get_seconds(), 0.5));
}

// Test cumulative timing
TEST_F(StopwatchTest, CumulativeTiming) {
    watch.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    watch.stop();
    
    watch.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    watch.stop();
    
    EXPECT_TRUE(approx_equal(watch.get_seconds(), 1.0));
}

// Test reset functionality
TEST_F(StopwatchTest, Reset) {
    watch.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    watch.stop();
    
    watch.reset();
    EXPECT_DOUBLE_EQ(watch.get_seconds(), 0.0);
}

// Test various time units
TEST_F(StopwatchTest, TimeUnits) {
    watch.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    watch.stop();
    
    EXPECT_TRUE(approx_equal(watch.get_seconds(), 2.0));
    EXPECT_TRUE(approx_equal(watch.get_minutes(), 2.0/60.0));
    
    // Use a larger tolerance for milliseconds test
    EXPECT_TRUE(approx_equal_ms(watch.get_milliseconds(), 2000.0));
    
    // For additional verification, check that milliseconds are in a reasonable range
    EXPECT_GE(watch.get_milliseconds(), 1900.0);
    EXPECT_LE(watch.get_milliseconds(), 2100.0);
    
    // Nanoseconds is too precise to test with sleep, so we just check it's positive
    EXPECT_GT(watch.get_nanoseconds(), 0.0);
}

// Test fixture for RandomProcess
class RandomProcessTest : public ::testing::Test {
protected:
    RandomProcess process{"random_test"};
};

// Test that random values are within range [0,1]
TEST_F(RandomProcessTest, ValuesInRange) {
    // Generate 100 random values
    for (int i = 0; i < 100; i++) {
        process.update();
    }
    
    // Check that all values are in range [0,1]
    for (double value : process.values()) {
        EXPECT_GE(value, 0.0);
        EXPECT_LE(value, 1.0);
    }
}

// Test fixture for Filter
class FilterTest : public ::testing::Test {
protected:
    Filter filter{"filter_test"};
};

// Test initial value is zero
TEST_F(FilterTest, InitialValueIsZero) {
    EXPECT_DOUBLE_EQ(filter.value(), 0.0);
}

// Test updating with single value
TEST_F(FilterTest, SingleValue) {
    filter.update(1.0);
    EXPECT_DOUBLE_EQ(filter.value(), 1.0);
}

// Test running average calculation
TEST_F(FilterTest, RunningAverage) {
    // Add 5 values: 1, 2, 3, 4, 5
    for (int i = 1; i <= 5; i++) {
        filter.update(i);
    }
    
    // Average should be (1+2+3+4+5)/5 = 3.0
    EXPECT_DOUBLE_EQ(filter.value(), 3.0);
}

// Test that filter keeps only last 10 values
TEST_F(FilterTest, KeepsLast10Values) {
    // Add 15 values: 1 through 15
    for (int i = 1; i <= 15; i++) {
        filter.update(i);
    }
    
    // Only the last 10 values (6-15) should be kept
    // Average = (6+7+8+9+10+11+12+13+14+15)/10 = 10.5
    EXPECT_DOUBLE_EQ(filter.value(), 10.5);
    EXPECT_EQ(filter.get_values().size(), 10);
}

// Test alternating values
TEST_F(FilterTest, AlternatingValues) {
    // Add 20 alternating values: 0.25, 0.75, 0.25, 0.75, ...
    for (int i = 0; i < 20; i++) {
        filter.update(i % 2 == 0 ? 0.25 : 0.75);
    }
    
    // The average should converge to 0.5
    EXPECT_DOUBLE_EQ(filter.value(), 0.5);
}

// Test fixture for Integrator
class IntegratorTest : public ::testing::Test {
protected:
    Integrator integrator{"integrator_test"};
    
    // Tolerance for integration tests
    const double epsilon = 0.1;
    
    bool approx_equal(double a, double b) {
        return std::abs(a - b) < epsilon;
    }
};

// Test initial value is zero
TEST_F(IntegratorTest, InitialValueIsZero) {
    EXPECT_DOUBLE_EQ(integrator.value(), 0.0);
}

// Test integration of constant input with manual timing
TEST_F(IntegratorTest, ConstantInput) {
    // First update just initializes the timer
    integrator.update(2.0);
    
    // Sleep for 100ms
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Update with the same value
    integrator.update(2.0);
    
    // Expected value: 2.0 * 0.1 = 0.2 (approximately)
    EXPECT_TRUE(approx_equal(integrator.value(), 0.2));
}

// Test reset functionality
TEST_F(IntegratorTest, Reset) {
    integrator.update(2.0);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    integrator.update(2.0);
    
    integrator.reset();
    EXPECT_DOUBLE_EQ(integrator.value(), 0.0);
}

// More complex integration test with changing values
TEST_F(IntegratorTest, ChangingValues) {
    // First update just initializes the timer
    integrator.update(1.0);
    
    // Perform a sequence of updates with different values and delays
    for (int i = 1; i <= 5; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        integrator.update(i);
    }
    
    // The result will vary based on exact timing, but should be positive
    EXPECT_GT(integrator.value(), 0.0);
}
