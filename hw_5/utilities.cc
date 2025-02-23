#include "utilities.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <unordered_map>

// Sorts a vector of doubles by absolute magnitude
void sort_by_magnitude(std::vector<double>& vec) {
    std::sort(vec.begin(), vec.end(), [](double x, double y) {
        return std::abs(x) < std::abs(y);
    });
}

// Reads a CSV file into a matrix (TypedArray<TypedArray<double>>)
TypedArray<TypedArray<double>> read_matrix_csv(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + path);
    }

    TypedArray<TypedArray<double>> matrix;
    std::string line;
    while (std::getline(file, line)) {
        TypedArray<double> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            try {
                row.set(row.size(), std::stod(cell));
            } catch (const std::invalid_argument&) {
                throw std::runtime_error("Invalid format in CSV file");
            }
        }
        if (matrix.size() > 0 && row.size() != matrix.safe_get(0).size()) {
            throw std::runtime_error("Inconsistent row sizes in CSV file");
        }
        matrix.set(matrix.size(), row);
    }

    return matrix;
}

// Writes a matrix to a CSV file
void write_matrix_csv(const TypedArray<TypedArray<double>>& matrix, const std::string& path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for writing: " + path);
    }

    for (int i = 0; i < matrix.size(); ++i) {
        const TypedArray<double>& row = matrix.safe_get(i);
        for (int j = 0; j < row.size(); ++j) {
            file << row.safe_get(j);
            if (j < row.size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }
}

std::map<std::string, int> occurrence_map(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + path);
    }

    std::map<std::string, int> word_count;
    std::string word;
    char ch;
    while (file.get(ch)) {
        if (std::isalnum(ch) || ch == '\'') {
            word += std::tolower(ch);
        } else if (!word.empty()) {
            word_count[word]++;
            word.clear();
        }
    }
    if (!word.empty()) {
        word_count[word]++;
    }

    return word_count;
}

