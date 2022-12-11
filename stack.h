#pragma once
#include "list.h"

template <class T>
class stack {
	list<T> list;
public:
    void push(const T& elem) {
    	list.add_front(elem);
    }
    
    T pop() {
    	return list.pop_front();
    }
    
    T peek() {
    	return list[0];
    }
    
    size_t get_size() {
        return list.get_size();
    }

    bool is_empty() {
    	return list.is_empty();
    }
};