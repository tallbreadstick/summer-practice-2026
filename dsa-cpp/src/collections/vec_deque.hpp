#pragma once

#ifndef VEC_DEQUE_HPP
#define VEC_DEQUE_HPP

#include <iostream>
#include <cstdint>
#include <cstddef>

using namespace std;

// vector double-ended queue abstract class

template<typename T>
class vec_deque {

    public:

        virtual ~vec_deque() = default;

        virtual const size_t size() = 0;
        virtual const bool is_empty() = 0;

        virtual void push_front(const T data) = 0;
        virtual void push_back(const T data) = 0;
        virtual T pop_front() = 0;
        virtual T pop_back() = 0;
        virtual const T& peek_front() = 0;
        virtual const T& peek_back() = 0;

        virtual const T& operator [] (const size_t index) const = 0;
        virtual T& operator [] (const size_t index) = 0;

};

#endif