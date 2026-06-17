#pragma once

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "exception.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "deque.hpp"

using namespace std;

template<typename T>
class vector;

template<typename T>
ostream& operator << (ostream& os, const vector<T>& v);

template<typename T>
class stack_model_v : public stack<T> {

    public:

        void push(const T data) final { stack_push(data); }
        T pop() final { return stack_pop(); }
        const T& peek() final { return stack_peek(); }

        virtual void stack_push(const T data) = 0;
        virtual T stack_pop() = 0;
        virtual const T& stack_peek() = 0;

};

template<typename T>
class queue_model_v : public queue<T> {

    public:

        void offer(const T data) final { queue_offer(data); }
        T poll() final { return queue_poll(); }
        const T& peek() final { return queue_peek(); }

        virtual void queue_offer(const T data) = 0;
        virtual T queue_poll() = 0;
        virtual const T& queue_peek() = 0;

};

template<typename T>
class deque_model_v : public deque<T> {

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

// vector data structure (dynamic array)

template<typename T>
class vector :
    public stack_model_v<T>,
    public queue_model_v<T>,
    public deque_model_v<T>
{

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

        // constructors and destructors

        vector() {
            _size = 0;
            _capacity = 10;
            mem = new T[_capacity];
        }

        vector(const size_t capacity) {
            _size = 0;
            _capacity = capacity;
            mem = new T[_capacity];
        }

        ~vector() {
            delete[] mem;
            _size = 0;
            _capacity = 0;
        }

        // immutable operations

        const size_t size() {
            return _size;
        }

        const size_t capacity() {
            return _capacity;
        }

        const bool is_empty() {
            return _size == 0;
        }

        // mutable operations

        void append(const T data) {
            if (_size + 1 >= _capacity)
                expand();
            mem[_size++] = data;
        }

        T remove_last() {
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

        void shrink_to_fit() {
            _capacity = _size;
            T* temp = new T[_capacity];
            for (size_t i = 0; i < _size; i++) {
                temp[i] = mem[i];
            }
            delete[] mem;
            mem = temp;
        }

        // operator overloads

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

        // stack model overrides

        void stack_push(const T data) override {
            append(data);
        }

        T stack_pop() override {
            return remove_last();
        }

        const T& stack_peek() override {
            if (_size == 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            return mem[_size - 1];
        }

        // queue model overrides

        void queue_offer(const T data) override {
            append(data);
        }

        T queue_poll() override {
            return remove(0);
        }

        const T& queue_peek() override {
            if (_size == 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            return mem[0];
        }

        // deque model overrides

        void deque_push_front(const T data) override {
            insert(0, data);
        }

        void deque_push_back(const T data) override {
            append(data);
        }

        T deque_pop_front() override {
            return remove(0);
        }

        T deque_pop_back() override {
            return remove_last();
        }

        const T& deque_peek_front() override {
            if (_size == 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            return mem[0];
        }

        const T& deque_peek_back() override {
            if (_size == 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            return mem[_size - 1];
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