#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <string>
#include <chrono>

class Integrator {
private:
    std::string name;
    double integrated_value;  // Stores the current integral value
    std::chrono::time_point<std::chrono::high_resolution_clock> last_update_time;
    bool first_update;

public:
    // Constructor
    Integrator(std::string process_name) : 
        name(process_name), 
        integrated_value(0.0),
        first_update(true) {}

    // Process a new input value with the elapsed time since last update
    void update(double input_value) {
        auto current_time = std::chrono::high_resolution_clock::now();
        
        if (first_update) {
            // Initialize the last update time on first call
            last_update_time = current_time;
            first_update = false;
            return;
        }
        
        // Calculate time difference in seconds
        std::chrono::duration<double> delta = current_time - last_update_time;
        double delta_seconds = delta.count();
        
        // Numerical integration: add delta * input_value to the integrated value
        integrated_value += delta_seconds * input_value;
        
        // Update the last update time
        last_update_time = current_time;
    }

    // Reset the integrator
    void reset() {
        integrated_value = 0.0;
        first_update = true;
    }

    // Get the name of the process
    std::string get_name() const {
        return name;
    }

    // Return the current integrated value
    double value() const {
        return integrated_value;
    }
};

#endif // INTEGRATOR_H