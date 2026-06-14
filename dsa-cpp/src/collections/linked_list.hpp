#pragma once

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "exception.hpp"

using namespace std;

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

template<typename T>
class linked_list {

    private:

        node<T>* head;
        node<T>* tail;
        size_t _size;

    public:

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

        const size_t size() {
            return _size;
        }

        const bool is_empty() {
            return head == nullptr;
        }

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