#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
#include <map>
#include "typed_array.h"

// Sorts a vector of doubles by absolute magnitude
void sort_by_magnitude(std::vector<double>& vec);

// Reads a CSV file into a matrix (TypedArray<TypedArray<double>>)
TypedArray<TypedArray<double>> read_matrix_csv(const std::string& path);

// Writes a matrix to a CSV file
void write_matrix_csv(const TypedArray<TypedArray<double>>& matrix, const std::string& path);

// Reads a text file and returns a word frequency map
std::map<std::string, int> occurrence_map(const std::string& path);

#endif // UTILITIES_H
