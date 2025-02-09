#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

static int array_count = 0;

// Private function prototypes
static int index_to_offset(const DynamicArray *da, int index);
static int out_of_buffer(DynamicArray *da, int offset);
static void extend_buffer(DynamicArray *da);
int compare_doubles(const void *a, const void *b);

// Convert index to buffer offset
static int index_to_offset(const DynamicArray *da, int index) {
    return index + da->origin;
}

// Check if offset is outside the buffer
static int out_of_buffer(DynamicArray *da, int offset) {
    return offset < 0 || offset >= da->capacity;
}

// Extend buffer to accommodate more elements
static void extend_buffer(DynamicArray *da) {
    int new_capacity = 2 * da->capacity;
    double *new_buffer = (double *)calloc(new_capacity, sizeof(double));
    int new_origin = (new_capacity - DynamicArray_size(da)) / 2;
    int new_end = new_origin + DynamicArray_size(da);

    for (int i = 0; i < DynamicArray_size(da); i++) {
        new_buffer[new_origin + i] = DynamicArray_get(da, i);
    }

    free(da->buffer);
    da->buffer = new_buffer;
    da->capacity = new_capacity;
    da->origin = new_origin;
    da->end = new_end;
}

// Create a new dynamic array
DynamicArray *DynamicArray_new(void) {
    DynamicArray *da = (DynamicArray *)malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;
    da->buffer = (double *)calloc(da->capacity, sizeof(double));
    da->origin = da->capacity / 2;
    da->end = da->origin;
    array_count++;
    return da;
}

// Destroy a dynamic array
void DynamicArray_destroy(DynamicArray *da) {
    free(da->buffer);
    da->buffer = NULL;
    array_count--;
}

// Return the number of elements in the array
int DynamicArray_size(const DynamicArray *da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

// Set an element in the array at the specified index
void DynamicArray_set(DynamicArray *da, int index, double value) {
    assert(da != NULL);
    while (index >= DynamicArray_size(da)) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if (index >= DynamicArray_size(da)) {
        da->end = index_to_offset(da, index + 1);
    }
}

// Get an element from the array at the specified index
double DynamicArray_get(const DynamicArray *da, int index) {
    assert(da != NULL);
    if (index < 0 || index >= DynamicArray_size(da)) {
        return 0;  // Optionally handle error more explicitly
    }
    return da->buffer[index_to_offset(da, index)];
}

// Mathematical operations
double DynamicArray_min(const DynamicArray *da) {
    assert(da != NULL && DynamicArray_size(da) > 0);
    double min = da->buffer[da->origin];
    for (int i = 1; i < DynamicArray_size(da); i++) {
        double value = DynamicArray_get(da, i);
        if (value < min) {
            min = value;
        }
    }
    return min;
}

double DynamicArray_max(const DynamicArray *da) {
    assert(da != NULL && DynamicArray_size(da) > 0);
    double max = da->buffer[da->origin];
    for (int i = 1; i < DynamicArray_size(da); i++) {
        double value = DynamicArray_get(da, i);
        if (value > max) {
            max = value;
        }
    }
    return max;
}

double DynamicArray_mean(const DynamicArray *da) {
    assert(da != NULL && DynamicArray_size(da) > 0);
    double sum = 0;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        sum += DynamicArray_get(da, i);
    }
    return sum / DynamicArray_size(da);
}

double DynamicArray_median(DynamicArray *da) {
    assert(da != NULL && DynamicArray_size(da) > 0);
    DynamicArray *copy = DynamicArray_copy(da);
    qsort(copy->buffer + copy->origin, DynamicArray_size(copy), sizeof(double), compare_doubles);
    double median = (DynamicArray_size(copy) % 2 == 0) ?
                    (copy->buffer[copy->origin + DynamicArray_size(copy) / 2 - 1] +
                     copy->buffer[copy->origin + DynamicArray_size(copy) / 2]) / 2.0 :
                    copy->buffer[copy->origin + DynamicArray_size(copy) / 2];
    DynamicArray_destroy(copy);
    return median;
}

double DynamicArray_sum(const DynamicArray *da) {
    double sum = 0;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        sum += DynamicArray_get(da, i);
    }
    return sum;
}

// Returns the first element in the array
double DynamicArray_first(const DynamicArray *da) {
    assert(da != NULL && DynamicArray_size(da) > 0);  // Ensure the array is not empty
    return DynamicArray_get(da, 0);
}

// Returns the last element in the array
double DynamicArray_last(const DynamicArray *da) {
    assert(da != NULL && DynamicArray_size(da) > 0);  // Ensure the array is not empty
    return DynamicArray_get(da, DynamicArray_size(da) - 1);
}

// Copy a dynamic array
DynamicArray *DynamicArray_copy(const DynamicArray *da) {
    assert(da != NULL);
    DynamicArray *new_da = DynamicArray_new();
    for (int i = 0; i < DynamicArray_size(da); i++) {
        DynamicArray_push(new_da, DynamicArray_get(da, i));
    }
    return new_da;
}

// Create a new array from a range of values
DynamicArray *DynamicArray_range(double start, double end, double step) {
    DynamicArray *da = DynamicArray_new();
    for (double value = start; value <= end; value += step) {
        DynamicArray_push(da, value);
    }
    return da;
}

// Concatenate two arrays into a new array
DynamicArray *DynamicArray_concat(const DynamicArray *a, const DynamicArray *b) {
    assert(a != NULL && b != NULL);
    DynamicArray *result = DynamicArray_copy(a);
    for (int i = 0; i < DynamicArray_size(b); i++) {
        DynamicArray_push(result, DynamicArray_get(b, i));
    }
    return result;
}

// Returns a sub-array of n elements from the beginning if n is positive,
// or from the end if n is negative. Fills with zeros if there aren't enough elements.
DynamicArray *DynamicArray_take(const DynamicArray *da, int n) {
    assert(da != NULL);
    DynamicArray *result = DynamicArray_new();
    int size = DynamicArray_size(da);

    if (n > 0) {
        for (int i = 0; i < n; i++) {
            if (i < size) {
                DynamicArray_push(result, DynamicArray_get(da, i));
            } else {
                DynamicArray_push(result, 0);  // Fill with zeros if not enough elements
            }
        }
    } else if (n < 0) {
        n = -n;  // Make n positive to simplify calculation
        for (int i = size - n; i < size; i++) {
            if (i >= 0) {
                DynamicArray_push(result, DynamicArray_get(da, i));
            } else {
                DynamicArray_push(result, 0);  // Fill with zeros if not enough elements
            }
        }
    }

    return result;
}

// Utility functions for lifecycle management and debugging
int DynamicArray_num_arrays(void) {
    return array_count;
}

void DynamicArray_destroy_all(void) {
    // This would require tracking all arrays created, not implemented here
}

int DynamicArray_is_valid(const DynamicArray *da) {
    return da != NULL && da->buffer != NULL;
}

// Comparator for double values, used in qsort
int compare_doubles(const void *a, const void *b) {
    double diff = *(double *)a - *(double *)b;
    return (diff > 0) - (diff < 0);
}
