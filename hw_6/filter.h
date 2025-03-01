#ifndef FILTER_H
#define FILTER_H

#include <deque>
#include <string>
#include <vector>

class Filter {
private:
    std::string name;
    std::deque<double> values;  // Stores the last 10 values
    double running_avg;         // Running average of the values

    // Update the running average
    void update_average() {
        if (values.empty()) {
            running_avg = 0.0;
            return;
        }
        
        double sum = 0.0;
        for (double val : values) {
            sum += val;
        }
        running_avg = sum / values.size();
    }

public:
    // Constructor
    Filter(std::string process_name) : name(process_name), running_avg(0.0) {}

    // Process a new input value
    void update(double input_value) {
        // Add the new value to our collection
        values.push_back(input_value);
        
        // Keep only the last 10 values
        if (values.size() > 10) {
            values.pop_front();
        }
        
        // Update the running average
        update_average();
    }

    // Get the name of the process
    std::string get_name() const {
        return name;
    }

    // Return the current running average
    double value() const {
        return running_avg;
    }

    // Get the values in the filter
    const std::deque<double>& get_values() const {
        return values;
    }
};

#endif // FILTER_H