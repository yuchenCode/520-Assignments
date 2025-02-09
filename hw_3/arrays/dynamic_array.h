#ifndef _DYNAMIC_ARRAY
#define _DYNAMIC_ARRAY

#include <stdlib.h>
#include <assert.h>

#define DYNAMIC_ARRAY_INITIAL_CAPACITY 10

typedef struct {
    int capacity, origin, end;
    double *buffer;
} DynamicArray;

// Constructors / Destructors
DynamicArray *DynamicArray_new(void);
void DynamicArray_destroy(DynamicArray *);

// Getters / Setters
void DynamicArray_set(DynamicArray *, int, double);
double DynamicArray_get(const DynamicArray *, int);
int DynamicArray_size(const DynamicArray *);

// Printing
char *DynamicArray_to_string(const DynamicArray *);
void DynamicArray_print_debug_info(const DynamicArray *);

// Operations
void DynamicArray_push(DynamicArray *, double);
void DynamicArray_push_front(DynamicArray *, double);
double DynamicArray_pop(DynamicArray *);
double DynamicArray_pop_front(DynamicArray *);

DynamicArray *DynamicArray_map(const DynamicArray *, double (*)(double));

// Mathematical operations
double DynamicArray_min(const DynamicArray *);
double DynamicArray_max(const DynamicArray *);
double DynamicArray_mean(const DynamicArray *);
double DynamicArray_median(DynamicArray *);
double DynamicArray_sum(const DynamicArray *);
double DynamicArray_first(const DynamicArray *);
double DynamicArray_last(const DynamicArray *);

// Additional utility functions
DynamicArray *DynamicArray_copy(const DynamicArray *);
DynamicArray *DynamicArray_range(double, double, double);
DynamicArray *DynamicArray_concat(const DynamicArray *, const DynamicArray *);
DynamicArray *DynamicArray_take(DynamicArray *, int);

// Lifecycle and validity
int DynamicArray_num_arrays(void);
void DynamicArray_destroy_all(void);
int DynamicArray_is_valid(const DynamicArray *);

#endif
