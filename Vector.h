#pragma once

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t size;

public:
    Vector() : data(nullptr), capacity(0), size(0) {}

    ~Vector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size >= capacity) {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            T* new_data = new T[new_capacity];

            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }

            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }

        data[size++] = value;
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    void erase(size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }

        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }

        --size;
    }

    size_t get_size() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

    void clear() {
        size = 0;
    }

    T* begin() {
        return data;
    }

    const T* begin() const {
        return data;
    }

    T* end() {
        return data + size;
    }

    const T* end() const {
        return data + size;
    }
};
