#pragma once

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <cstdint>
#include <cstddef>

using namespace std;

template<typename T>
class stack {

    public:

        virtual ~stack() = default;

        virtual const size_t size() = 0;
        virtual const bool is_empty() = 0;
        virtual void push(const T data) = 0;
        virtual T pop() = 0;
        virtual const T& peek() = 0;

};

#endif