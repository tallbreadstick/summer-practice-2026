#pragma once

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <cstdint>
#include <cstddef>

using namespace std;

// queue abstract class

template<typename T>
class queue {

    public:

        virtual ~queue() = default;

        virtual const size_t size() = 0;
        virtual const bool is_empty() = 0;
        
        virtual void offer(const T data) = 0;
        virtual T poll() = 0;
        virtual const T& peek() = 0;

};

#endif