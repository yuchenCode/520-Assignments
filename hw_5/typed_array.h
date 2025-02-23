#ifndef TYPED_ARRAY
#define TYPED_ARRAY

#include <assert.h>
#include <iostream>
#include <stdexcept>

template <typename ElementType>
class TypedArray {

public:

    TypedArray();
    TypedArray(const TypedArray& other);

    // Copy constructor
    TypedArray& operator=(const TypedArray& other);

    // Destructor
    ~TypedArray();

    // Getters
    ElementType &get(int index); 
    ElementType &safe_get(int index) const;
    int size() const;

    // Setters
    void set(int index, ElementType value);

    void push(const ElementType& value);              // Add element to the end
    ElementType pop();                                // Remove and return element from the end
    void push_front(const ElementType& value);        // Add element to the front
    ElementType pop_front();

    // New method for concatenation
    TypedArray concat(const TypedArray& other) const;

    // New method to reverse the array
    TypedArray& reverse();

    // Concatenation operator
    TypedArray operator+(const TypedArray& other) const;

private:

    int capacity,
        origin,
        end;

    ElementType * buffer;   

    const int INITIAL_CAPACITY = 10;

    int index_to_offset(int index) const;
    int offset_to_index(int offset) const;
    bool out_of_buffer(int offset) const;
    void extend_buffer(void);    

};

template <typename ElementType>
TypedArray<ElementType>::TypedArray() {
    buffer = new ElementType[INITIAL_CAPACITY]();
    capacity = INITIAL_CAPACITY;    
    origin = capacity / 2;
    end = origin;    
}

// Copy constructor: i.e TypedArray b(a) where a is a TypedArray
template <typename ElementType>
TypedArray<ElementType>::TypedArray(const TypedArray& other) : TypedArray() {
    *this = other;
}

// Assignment operator: i.e TypedArray b = a 
template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::operator=(const TypedArray<ElementType>& other) {
    if ( this != &other) {
        delete[] buffer; // don't forget this or you'll get a memory leak!
        buffer = new ElementType[other.capacity]();
        capacity = other.capacity;
        origin = other.origin;
        end = origin;
        for ( int i=0; i<other.size(); i++) {
            set(i,other.safe_get(i));
        }
    }
    return *this;
}

// Destructor
template <typename ElementType>
TypedArray<ElementType>::~TypedArray() {
    delete[] buffer;
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::get(int index) {
    if (index < 0) {
        throw std::range_error("Out of range index in array");
    }
    if ( index >= size() ) {
        ElementType x;
        set(index, x);
    } 
    return buffer[index_to_offset(index)];
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::safe_get(int index) const {
    if (index < 0 || index >= size() ) {
        throw std::range_error("Out of range index in array");
    }
    return buffer[index_to_offset(index)];
}

template <typename ElementType>
int TypedArray<ElementType>::size() const {
    return end - origin;
}

// Setters
template <typename ElementType>
void TypedArray<ElementType>::set(int index, ElementType value) {
    if (index < 0) {
        throw std::range_error("Negative index in array");
    }
    while ( out_of_buffer(index_to_offset(index) ) ) {
        extend_buffer();
    }
    buffer[index_to_offset(index)] = value; // Should call the copy constructor
                                            // of ElementType.
    if ( index >= size() ) {
        end = index_to_offset(index+1);
    }
}

// Push: Adds an element to the end of the array
template <typename ElementType>
void TypedArray<ElementType>::push(const ElementType& value) {
    // Ensure there's enough space in the buffer
    if (out_of_buffer(end)) {
        extend_buffer(); // Expand the buffer if necessary
    }

    // Use set(), which will automatically update `end` if needed
    set(size(), value);
}

// Pop: Removes and returns the last element of the array
template <typename ElementType>
ElementType TypedArray<ElementType>::pop() {
    if (size() == 0) {
        throw std::range_error("Cannot pop from an empty array");
    }

    // Get the last element before decrementing `end`
    ElementType value = get(size() - 1);

    // Decrement `end` to remove the last element
    end--;

    return value;
}

// Push front: Adds an element to the front of the array
template <typename ElementType>
void TypedArray<ElementType>::push_front(const ElementType& value) {
    // Ensure there's enough space in the buffer
    if (out_of_buffer(origin - 1)) {
        extend_buffer(); // Expand the buffer if necessary
    }

    // Decrement origin to make space at the front
    origin--;
    set(0, value);  // Insert the element at the front
}

// Pop front: Removes and returns the first element of the array
template <typename ElementType>
ElementType TypedArray<ElementType>::pop_front() {
    if (size() == 0) {
        throw std::range_error("Cannot pop from an empty array");
    }

    // Get the first element
    ElementType value = get(0);

    // Shift all elements one position to the left
    for (int i = 1; i < size(); i++) {
        set(i - 1, get(i));
    }

    // Decrement `end` to remove the last element
    end--;

    return value;
}

// concat method: concatenates the current array and the other array
template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::concat(const TypedArray<ElementType>& other) const {
    TypedArray<ElementType> result;

    // Copy elements from the current array
    for (int i = 0; i < size(); i++) {
        result.set(i, safe_get(i));  // Use safe_get() instead of get()
    }

    // Copy elements from the other array
    for (int i = 0; i < other.size(); i++) {
        result.set(size() + i, other.safe_get(i));  // Use safe_get() instead of get()
    }

    return result;
}

// reverse method: reverses the current array in place
template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::reverse() {
    int start = 0;
    int end = size() - 1;

    // Swap elements from the start and end until reaching the middle
    while (start < end) {
        // Swap values
        ElementType temp = get(start);
        set(start, get(end));
        set(end, temp);

        // Move towards the middle
        start++;
        end--;
    }

    return *this; // Return reference to the current array
}

// Concatenation operator: concatenates the current array and the other array
template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::operator+(const TypedArray<ElementType>& other) const {
    return concat(other); // Use the previously defined concat method
}

template <typename ElementType>
std::ostream &operator<<(std::ostream &os, TypedArray<ElementType> &array)
{
    os << '[';
    for (int i=0; i<array.size(); i++ ) {
        os << array.get(i);
        if ( i < array.size() - 1 ) {
            os << ",";
        }
    }
    os << ']';
    return os;
}

// Private methods

template <typename ElementType>
int TypedArray<ElementType>::index_to_offset ( int index ) const {
    return index + origin;
}

/* Position of the element at buffer position 'offset' */
template <typename ElementType>
int TypedArray<ElementType>::offset_to_index ( int offset ) const  {
    return offset - origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
template <typename ElementType>
bool TypedArray<ElementType>::out_of_buffer ( int offset ) const {
    return offset < 0 || offset >= capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
template <typename ElementType>
void TypedArray<ElementType>::extend_buffer() {

    auto temp = new ElementType[2 * capacity]();
    int new_origin = capacity - (end - origin)/2,
           new_end = new_origin + (end - origin);

    for ( int i=0; i<size(); i++ ) {
        temp[new_origin+i] = get(i);
    }

    delete[] buffer;
    buffer = temp;

    capacity = 2 * capacity;
    origin = new_origin;
    end = new_end;

    return;

}

#endif