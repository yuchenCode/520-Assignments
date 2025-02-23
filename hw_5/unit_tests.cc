#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "utilities.h"
#include "gtest/gtest.h"
#include <fstream>

namespace {

    TEST(SortByMagnitudeTest, BasicSort) {
        std::vector<double> values = {3.0, -1.0, -5.0, 4.0, 2.0};
        sort_by_magnitude(values);
        EXPECT_EQ(values, std::vector<double>({-1.0, 2.0, 3.0, 4.0, -5.0}));
    }

    TEST(ReadWriteMatrixCSVTest, ReadWrite) {
        std::string filename = "test_matrix.csv";
        TypedArray<TypedArray<double>> matrix;
        TypedArray<double> row1, row2;
        row1.set(0, 1.1); row1.set(1, 2.2);
        row2.set(0, 3.3); row2.set(1, 4.4);
        matrix.set(0, row1);
        matrix.set(1, row2);
        
        write_matrix_csv(matrix, filename);
        TypedArray<TypedArray<double>> read_matrix = read_matrix_csv(filename);
        EXPECT_EQ(read_matrix.safe_get(0).safe_get(0), 1.1);
        EXPECT_EQ(read_matrix.safe_get(0).safe_get(1), 2.2);
        EXPECT_EQ(read_matrix.safe_get(1).safe_get(0), 3.3);
        EXPECT_EQ(read_matrix.safe_get(1).safe_get(1), 4.4);
        
        std::remove(filename.c_str());
    }

    TEST(OccurrenceMapTest, BasicWordCount) {
        std::string filename = "test_text.txt";
        std::ofstream file(filename);
        file << "This is a sentence. Don't think of wier_d strings as words. Really, 123 is a nice number.";
        file.close();
        
        std::map<std::string, int> word_count = occurrence_map(filename);
        EXPECT_EQ(word_count["this"], 1);
        EXPECT_EQ(word_count["is"], 2);
        EXPECT_EQ(word_count["a"], 2);
        EXPECT_EQ(word_count["sentence"], 1);
        EXPECT_EQ(word_count["don't"], 1);
        EXPECT_EQ(word_count["think"], 1);
        EXPECT_EQ(word_count["of"], 1);
        EXPECT_EQ(word_count["strings"], 1);
        EXPECT_EQ(word_count["as"], 1);
        EXPECT_EQ(word_count["words"], 1);
        EXPECT_EQ(word_count["really"], 1);
        EXPECT_EQ(word_count["123"], 1);
        EXPECT_EQ(word_count["nice"], 1);
        EXPECT_EQ(word_count["number"], 1);
        EXPECT_EQ(word_count.find("wier_d"), word_count.end());
        
        std::remove(filename.c_str());
    }

}  // namespace
