#pragma once

#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <iostream>
#include <cstdint>
#include <cstddef>

using namespace std;

// double-ended queue abstract class

template<typename T>
class deque {

    public:

        virtual ~deque() = default;

        virtual const size_t size() = 0;
        virtual const bool is_empty() = 0;

        virtual void push_front(const T data) = 0;
        virtual void push_back(const T data) = 0;
        virtual T pop_front() = 0;
        virtual T pop_back() = 0;
        virtual const T& peek_front() = 0;
        virtual const T& peek_back() = 0;

};

#endif