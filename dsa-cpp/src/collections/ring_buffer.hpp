#pragma once

#ifndef RING_BUFFER_HPP
#define RING_BUFFER_HPP

#include <iostream>
#include <cstdint>
#include <cstddef>
#include "exception.hpp"
#include "deque.hpp"
#include "vec_deque.hpp"

using namespace std;

template<typename T>
class ring_buffer;

template<typename T>
ostream& operator << (ostream& os, const ring_buffer<T>& r);

template<typename T>
class ring_buffer {

    private:

        T* mem;
        size_t _size;
        size_t _capacity;
        size_t start;

        void expand() {
            const size_t new_capacity = _capacity * 2 + 2;
            T* temp = new T[new_capacity];
            for (size_t i = 0; i < _size; i++) {
                temp[i] = mem[(start + i) % _capacity];
            }
            delete[] mem;
            mem = temp;
            start = 0;
        }

    public:

        // constructors and destructors

        ring_buffer() {
            _size = 0;
            _capacity = 
            mem = new T[];
        }

        ring_buffer(const size_t capacity) {
            _size = 0;
            _capacity = capacity;
            mem = new T[_capacity];
        }

        ~ring_buffer() {
            delete[] mem;
            _size = 0;
            _capacity = 0;
            start = 0;
        }

        // immutable operations

        const size_t size() {
            return _size;
        }

        const bool is_empty() {
            return _size == 0;
        }

        // mutable operations

        void push_head(const T data) {
            if (_size + 1 >= _capacity)
                expand();
        }

        void push_tail(const T data) {

        }

        T pop_head() {

        }

        T pop_tail() {

        }

        // operator overloads

        friend ostream& operator << <>(ostream& os, const ring_buffer<T>& r);

};

template<typename T>
ostream& operator << (ostream& os, const ring_buffer<T>& r) {
    os << "[";
    for (size_t i = 0; i < r._size; i++) {
        os << r.mem[(start + i) % r._capacity];
        if (i < r._size - 1)
            os << ", ";
    }
    os << "]";
    return os;
}

#endif