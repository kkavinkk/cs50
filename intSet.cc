#include "intSet.h"

// Default constructor
intSet::intSet() : data(new int[4]), size(0), capacity(4) {}

// Destructor
intSet::~intSet() {
    delete[] data;
}

// Copy constructor (deep copy)
intSet::intSet(const intSet& other) : data(new int[other.capacity]), size(other.size), capacity(other.capacity) {
    for (int i = 0; i < size; ++i)
        data[i] = other.data[i];
}

// Move constructor
intSet::intSet(intSet&& other) : data(other.data), size(other.size), capacity(other.capacity) {
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

// Copy assignment operator
intSet& intSet::operator=(const intSet& other) {
    if (this != &other) {
        delete[] data;
        data = new int[other.capacity];
        size = other.size;
        capacity = other.capacity;
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }
    return *this;
}

// Move assignment operator
intSet& intSet::operator=(intSet&& other) {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        capacity = other.capacity;
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

//ontains
bool intSet::contains(int e) const {
    for (int i = 0; i < size; ++i)
        if (data[i] == e) return true;
    return false;
}

// Add element
void intSet::add(int e) {
    if (contains(e)) return;
    if (size == capacity) {
        capacity *= 2;
        int* newData = new int[capacity];
        for (int i = 0; i < size; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
    }
    data[size++] = e;
}

// Remove element
void intSet::remove(int e) {
    for (int i = 0; i < size; ++i) {
        if (data[i] == e) {
            for (int j = i; j < size - 1; ++j)
                data[j] = data[j + 1];
            --size;
            return;
        }
    }
}

// Set union
intSet intSet::operator|(const intSet& other) const {
    intSet result;
    for (int i = 0; i < size; ++i)
        result.add(data[i]);
    for (int i = 0; i < other.size; ++i)
        result.add(other.data[i]);
    return result;
}

// Set intersection
intSet intSet::operator&(const intSet& other) const {
    intSet result;
    for (int i = 0; i < size; ++i) {
        if (other.contains(data[i]))
            result.add(data[i]);
    }
    return result;
}

// Equality
bool intSet::operator==(const intSet& other) const {
    if (size != other.size) return false;
    for (int i = 0; i < size; ++i) {
        if (!other.contains(data[i])) return false;
    }
    return true;
}

// isSubset
bool intSet::isSubset(const intSet& s) const {
    for (int i = 0; i < s.size; ++i) {
        if (!contains(s.data[i])) return false;
    }
    return true;
}

// Output operator
std::ostream& operator<<(std::ostream& out, const intSet& is) {
    // Create a copy and sort it for printing
    int* sorted = new int[is.size];
    for (int i = 0; i < is.size; ++i)
        sorted[i] = is.data[i];

    // Simple bubble sort
    for (int i = 0; i < is.size - 1; ++i) {
        for (int j = 0; j < is.size - i - 1; ++j) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    out << "(";
    for (int i = 0; i < is.size; ++i) {
        out << sorted[i];
        if (i != is.size - 1) out << ", ";
    }
    out << ")";

    delete[] sorted;
    return out;
}
