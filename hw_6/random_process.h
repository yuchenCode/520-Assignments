#ifndef RANDOM_PROCESS_H
#define RANDOM_PROCESS_H

#include <random>
#include <chrono>
#include <vector>

class RandomProcess {
private:
    std::string name;
    std::random_device rd;     // Will be used to obtain a seed for the random number engine
    std::mt19937 gen;          // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis;  // Uniform distribution between 0 and 1
    std::vector<double> output_values;     // Store generated values

public:
    // Constructor
    RandomProcess(std::string process_name) : 
        name(process_name),
        gen(rd()), 
        dis(0.0, 1.0) {}

    // Generate a new random value and store it
    void update() {
        // Generate a random double between 0 and 1
        double random_value = dis(gen);
        
        // Store the random value
        output_values.push_back(random_value);
    }

    // Get the name of the process
    std::string get_name() const {
        return name;
    }

    // Get the latest generated value
    double latest() const {
        if (output_values.empty()) {
            return 0.0;
        }
        return output_values.back();
    }

    // Get all generated values
    const std::vector<double>& values() const {
        return output_values;
    }

    // Clear all stored values
    void clear() {
        output_values.clear();
    }
};

#endif // RANDOM_PROCESS_H