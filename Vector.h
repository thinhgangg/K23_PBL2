#pragma once

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Vector {
private:
    T* data;       // Con trỏ tới mảng dữ liệu
    size_t capacity;    // Dung lượng hiện tại của mảng
    size_t size;        // Số lượng phần tử trong mảng

public:
    // Constructor mặc định
    Vector() : data(nullptr), capacity(0), size(0) {}

    // Destructor
    ~Vector() {
        delete[] data; // Giải phóng bộ nhớ
    }

    // Thêm phần tử vào cuối vector
    void push_back(const T& value) {
        if (size >= capacity) {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2; // Tăng dung lượng nếu hết chỗ
            T* new_data = new T[new_capacity]; // Tạo mảng mới với dung lượng lớn hơn

            // Sao chép dữ liệu cũ sang mảng mới
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }

            delete[] data; // Giải phóng mảng cũ
            data = new_data;
            capacity = new_capacity;
        }

        data[size++] = value; // Thêm phần tử mới vào cuối vector
    }

    // Truy cập phần tử (không thay đổi)
    const T& operator[](size_t index) const {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    // Truy cập phần tử (có thể thay đổi)
    T& operator[](size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    // Xóa phần tử tại chỉ số index
    void erase(size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }

        // Dịch chuyển các phần tử còn lại về phía trước
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }

        --size; // Giảm kích thước vector
    }

    // Lấy số lượng phần tử trong vector
    size_t get_size() const {
        return size;
    }

    // Kiểm tra vector có rỗng không
    bool empty() const {
        return size == 0;
    }

    // Xóa tất cả phần tử trong vector
    void clear() {
        size = 0;
    }

    // Iterator
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
