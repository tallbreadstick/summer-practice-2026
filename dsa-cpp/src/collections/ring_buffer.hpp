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
class deque_model_r : public deque<T> {

    public:

        void push_front(const T data) final { deque_push_front(data); }
        void push_back(const T data) final { deque_push_back(data); }
        T pop_front() final { return deque_pop_front(); }
        T pop_back() final { return deque_pop_back(); }
        const T& peek_front() final { return deque_peek_front(); }
        const T& peek_back() final { return deque_peek_back(); }

        virtual void deque_push_front(const T data) = 0;
        virtual void deque_push_back(const T data) = 0;
        virtual T deque_pop_front() = 0;
        virtual T deque_pop_back() = 0;
        virtual const T& deque_peek_front() = 0;
        virtual const T& deque_peek_back() = 0; 

};

template<typename T>
class vec_deque_model_r : public vec_deque<T> {

    public:

        void push_front(const T data) final { vec_deque_push_front(data); }
        void push_back(const T data) final { vec_deque_push_back(data); }
        T pop_front() final { return vec_deque_pop_front(); }
        T pop_back() final { return vec_deque_pop_back(); }
        const T& peek_front() final { return vec_deque_peek_front(); }
        const T& peek_back() final { return vec_deque_peek_back(); }

        virtual void vec_deque_push_front(const T data) = 0;
        virtual void vec_deque_push_back(const T data) = 0;
        virtual T vec_deque_pop_front() = 0;
        virtual T vec_deque_pop_back() = 0;
        virtual const T& vec_deque_peek_front() = 0;
        virtual const T& vec_deque_peek_back() = 0; 

};

template<typename T>
class ring_buffer :
    public deque_model_r<T>,
    public vec_deque_model_r<T>
{

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
            _capacity = new_capacity;
        }

    public:

        // constructors and destructors

        ring_buffer() {
            start = 0;
            _size = 0;
            _capacity = 10;
            mem = new T[_capacity];
        }

        ring_buffer(const size_t capacity) {
            start = 0;
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

        const T& peek_head() {
            if (_size == 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            return mem[start];
        }

        const T& peek_tail() {
            if (_size == 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            return mem[(start + _size - 1) % _capacity];
        }

        // mutable operations

        void push_head(const T data) {
            if (_size == _capacity)
                expand();
            if (start == 0)
                start = _capacity;
            mem[--start] = data;
            _size++;
        }

        void push_tail(const T data) {
            if (_size == _capacity)
                expand();
            mem[(start + _size++) % _capacity] = data;
        }

        T pop_head() {
            if (_size == 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            T data = mem[start];
            start = (start + 1) % _capacity;
            _size--;
            return data;
        }

        T pop_tail() {
            if (_size == 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            return mem[(start + --_size) % _capacity];
        }

        void shrink_to_fit() {
            T* temp = new T[_size];
            for (size_t i = 0; i < _size; i++) {
                temp[i] = mem[(start + i) % _capacity];
            }
            delete[] mem;
            mem = temp;
            _capacity = _size;
        }

        // operator overloads

        friend ostream& operator << <>(ostream& os, const ring_buffer<T>& r);

        const T& operator [] (const size_t index) const {
            if (index >= _size)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            return mem[(start + index) % _capacity];
        }

        T& operator [] (const size_t index) {
            if (index >= _size)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            return mem[(start + index) % _capacity];
        }

        // deque model overrides

        void deque_push_front(const T data) override {
            push_head(data);
        }

        void deque_push_back(const T data) override {
            push_tail(data);
        }

        T deque_pop_front() override {
            return pop_head();
        }

        T deque_pop_back() override {
            return pop_tail();
        }

        const T& deque_peek_front() override {
            return peek_head();
        }

        const T& deque_peek_back() override {
            return peek_tail();
        }

        // vec deque model overrides

        void vec_deque_push_front(const T data) override {
            push_head(data);
        }

        void vec_deque_push_back(const T data) override {
            push_tail(data);
        }

        T vec_deque_pop_front() override {
            return pop_head();
        }

        T vec_deque_pop_back() override {
            return pop_tail();
        }

        const T& vec_deque_peek_front() override {
            return peek_head();
        }

        const T& vec_deque_peek_back() override {
            return peek_tail();
        }

};

template<typename T>
ostream& operator << (ostream& os, const ring_buffer<T>& r) {
    os << "[";
    for (size_t i = 0; i < r._size; i++) {
        os << r.mem[(r.start + i) % r._capacity];
        if (i < r._size - 1)
            os << ", ";
    }
    os << "]";
    return os;
}

#endif