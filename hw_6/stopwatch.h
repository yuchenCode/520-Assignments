#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class Stopwatch {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop_time;
    bool running;
    std::chrono::nanoseconds elapsed;

public:
    // Constructor initializes the stopwatch to 0 seconds
    Stopwatch() : running(false), elapsed(std::chrono::nanoseconds::zero()) {}

    // Start the timer
    void start() {
        if (!running) {
            start_time = std::chrono::high_resolution_clock::now();
            running = true;
        }
    }

    // Stop the timer
    void stop() {
        if (running) {
            stop_time = std::chrono::high_resolution_clock::now();
            elapsed += std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time);
            running = false;
        }
    }

    // Reset the timer to zero
    void reset() {
        elapsed = std::chrono::nanoseconds::zero();
        running = false;
    }

    // Get the total elapsed time in minutes
    double get_minutes() {
        return get_nanoseconds() / (60.0 * 1e9);
    }

    // Get the total elapsed time in seconds
    double get_seconds() {
        return get_nanoseconds() / 1e9;
    }

    // Get the total elapsed time in milliseconds
    double get_milliseconds() {
        return get_nanoseconds() / 1e6;
    }

    // Get the total elapsed time in nanoseconds
    double get_nanoseconds() {
        if (running) {
            auto current_time = std::chrono::high_resolution_clock::now();
            auto current_elapsed = elapsed + std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - start_time);
            return static_cast<double>(current_elapsed.count());
        } else {
            return static_cast<double>(elapsed.count());
        }
    }
};

#endif // STOPWATCH_H