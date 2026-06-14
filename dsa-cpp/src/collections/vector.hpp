#pragma once

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "exception.hpp"

using namespace std;

template<typename T>
class vector;

template<typename T>
ostream& operator << (ostream& os, const vector<T>& v);

template<typename T>
class vector {

    private:

        T* mem;
        size_t _size;
        size_t _capacity;

        void expand() {
            const size_t new_capacity = _capacity * 2 + 2;
            T* temp = new T[new_capacity];
            for (size_t i = 0; i < _size; i++) {
                temp[i] = mem[i];
            }
            delete[] mem;
            mem = temp;
            _capacity = new_capacity;
        }

    public:

        vector() {
            _size = 0;
            _capacity = 10;
            mem = new T[_capacity];
        }

        vector(const size_t _capacity) {
            _size = 0;
            this->_capacity = _capacity;
            mem = new T[_capacity];
        }

        ~vector() {
            delete[] mem;
            _size = 0;
            _capacity = 0;
        }

        const size_t size() {
            return _size;
        }

        const size_t capacity() {
            return _capacity;
        }

        const bool is_empty() {
            return _size == 0;
        }

        void push(const T data) {
            if (_size + 1 >= _capacity)
                expand();
            mem[_size++] = data;
        }

        T pop() {
            if (_size == 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            return mem[--_size];
        }

        void insert(const size_t index, const T data) {
            if (index > _size || index < 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            if (_size + 1 >= _capacity)
                expand();
            for (size_t i = _size; i > index; i--) {
                mem[i] = mem[i - 1];
            }
            mem[index] = data;
            _size++;
        }

        T remove(const size_t index) {
            if (index >= _size || index < 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            T temp = mem[index];
            for (size_t i = index; i < _size - 1; i++) {
                mem[i] = mem[i + 1];
            }
            _size--;
            return temp;
        }

        friend ostream& operator << <>(ostream& os, const vector<T>& v);

        const T& operator [] (const size_t index) const {
            if (index >= _size || index < 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            return mem[index];
        }

        T& operator [] (const size_t index) {
            if (index >= _size || index < 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            return mem[index];
        }
};

template<typename T>
ostream& operator << (ostream& os, const vector<T>& v) {
    os << "[";
    for (size_t i = 0; i < v._size; i++) {
        os << v.mem[i];
        if (i < v._size - 1)
            os << ", ";
    }
    os << "]";
    return os;
}

#endif