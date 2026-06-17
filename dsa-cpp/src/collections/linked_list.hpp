#pragma once

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

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
class stack_model_l : public stack<T> {

    public:

        void push(const T data) final { stack_push(data); }
        T pop() final { return stack_pop(); }
        const T& peek() final { return stack_peek(); }

        virtual void stack_push(const T data) = 0;
        virtual T stack_pop() = 0;
        virtual const T& stack_peek() = 0;

};

template<typename T>
class queue_model_l : public queue<T> {

    public:

        void offer(const T data) final { queue_offer(data); }
        T poll() final { return queue_poll(); }
        const T& peek() final { return queue_peek(); }

        virtual void queue_offer(const T data) = 0;
        virtual T queue_poll() = 0;
        virtual const T& queue_peek() = 0;

};

template<typename T>
class deque_model_l : public deque<T> {

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
class node {

    public:

        T data;
        node<T>* prev;
        node<T>* next;

        node(T data) {
            this->data = data;
            prev = nullptr;
            next = nullptr;
        }

};

template<typename T>
class linked_list;

template<typename T>
ostream& operator << (ostream& os, const linked_list<T>& l);

// doubly-linked list data structure

template<typename T>
class linked_list :
    public stack_model_l<T>,
    public queue_model_l<T>,
    public deque_model_l<T>
{

    private:

        node<T>* head;
        node<T>* tail;
        size_t _size;

    public:

        // constructors and desctructors

        linked_list() {
            head = nullptr;
            tail = nullptr;
            _size = 0;
        }

        ~linked_list() {
            node<T>* ptr = head;
            while (ptr) {
                node<T>* next = ptr->next;
                delete ptr;
                ptr = next;
            }
            _size = 0;
        }

        // immutable operations

        const size_t size() {
            return _size;
        }

        const bool is_empty() {
            return head == nullptr;
        }

        // mutable operations

        void push_head(const T data) {
            node<T>* ptr = new node(data);
            if (head == nullptr)
                tail = ptr;
            else
                head->prev = ptr;
            ptr->next = head;
            ptr->prev = nullptr;
            head = ptr;
            _size++;
        }

        void push_tail(const T data) {
            node<T>* ptr = new node(data);
            if (tail == nullptr)
                head = ptr;
            else
                tail->next = ptr;
            ptr->prev = tail;
            ptr->next = nullptr;
            tail = ptr;
            _size++;
        }

        T pop_head() {
            if (is_empty())
                throw new runtime_error(NULL_POINTER_EXCEPTION);
            T temp = head->data;
            head = head->next;
            if (head == nullptr)
                tail = nullptr;
            else
                head->prev = nullptr;
            _size--;
            return temp;
        }

        T pop_tail() {
            if (is_empty())
                throw new runtime_error(NULL_POINTER_EXCEPTION);
            T temp = tail->data;
            tail = tail->prev;
            if (tail == nullptr)
                head = nullptr;
            else
                tail->next = nullptr;
            _size--;
            return temp;
        }
        
        void insert(const size_t index, const T data) {
            if (index > _size || index < 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            if (index == 0)
                push_head(data);
            else if (index == _size)
                push_tail(data);
            else {
                node<T>* new_node = new node(data);
                if (index < _size / 2) {
                    node<T>* ptr = head;
                    for (size_t i = 1; i < index; i++) {
                        ptr = ptr->next;
                    }
                    ptr->next->prev = new_node;
                    new_node->next = ptr->next;
                    new_node->prev = ptr;
                    ptr->next = new_node;
                } else {
                    node<T>* ptr = tail;
                    for (size_t i = _size - 1; i > index; i--) {
                        ptr = ptr->prev;
                    }
                    ptr->prev->next = new_node;
                    new_node->prev = ptr->prev;
                    new_node->next = ptr;
                    ptr->prev = new_node;
                }   
                _size++;
            }
        }

        T remove(const size_t index) {
            if (index >= _size || index < 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            if (is_empty())
                throw new runtime_error(NULL_POINTER_EXCEPTION);
            if (index == 0)
                return pop_head();
            else if (index == _size - 1) {
                return pop_tail();
            } else {
                T temp;
                if (index < _size / 2) {
                    node<T>* ptr = head;
                    for (size_t i = 1; i < index; i++) {
                        ptr = ptr->next;
                    }
                    temp = ptr->next->data;
                    ptr->next = ptr->next->next;
                    ptr->next->prev = ptr;
                } else {
                    node<T>* ptr = tail;
                    for (size_t i = _size - 1; i > index + 1; i--) {
                        ptr = ptr->prev;
                    }
                    temp = ptr->prev->data;
                    ptr->prev = ptr->prev->prev;
                    ptr->prev->next = ptr;
                }
                _size--;
                return temp;
            }
        }

        // operator overloads

        friend ostream& operator << <>(ostream& os, const linked_list<T>& l);

        const T& operator [] (const size_t index) const {
            if (index >= _size || index < 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            node<T>* ptr;
            if (index < _size / 2) {
                ptr = head;
                for (size_t i = 0; i < index; i++) {
                    ptr = ptr->next;
                }
            } else {
                ptr = tail;
                for (size_t i = _size - 1; i > index; i--) {
                    ptr = ptr->prev;
                }
            }
            return ptr->data;
        }

        T& operator [] (const size_t index) {
            if (index >= _size || index < 0)
                throw new runtime_error(INDEX_OUT_OF_BOUNDS_EXCEPTION);
            node<T>* ptr;
            if (index < _size / 2) {
                ptr = head;
                for (size_t i = 0; i < index; i++) {
                    ptr = ptr->next;
                }
            } else {
                ptr = tail;
                for (size_t i = _size - 1; i > index; i--) {
                    ptr = ptr->prev;
                }
            }
            return ptr->data;
            
        }

        // stack mddel overrides

        void stack_push(const T data) override {
            push_tail(data);
        }

        T stack_pop() override {
            return pop_tail();
        }

        const T& stack_peek() override {
            if (tail == nullptr)
                throw new runtime_error(NULL_POINTER_EXCEPTION);
            return head->data;
        }

        // queue model overrides

        void queue_offer(const T data) override {
            push_tail(data);
        }

        T queue_poll() override {
            return pop_head();
        }

        const T& queue_peek() override {
            if (head == nullptr)
                throw new runtime_error(NULL_POINTER_EXCEPTION);
            return head->data;
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
            if (head == nullptr)
                throw new runtime_error(NULL_POINTER_EXCEPTION);
            return head->data;
        }

        const T& deque_peek_back() override {
            if (tail == nullptr)
                throw new runtime_error(NULL_POINTER_EXCEPTION);
            return tail->data;
        }

};

template<typename T>
ostream& operator << (ostream& os, const linked_list<T>& l) {
    os << "[";
    node<T>* ptr = l.head;
    while (ptr) {
        os << ptr->data;
        if (ptr->next)
            os << ", ";
        ptr = ptr->next;
    }
    os << "]";
    return os;
}

#endif