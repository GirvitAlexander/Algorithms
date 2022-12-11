#pragma once
#include <cassert>

template <class T>
class list {
private:
    struct list_b {
		T data;
		list_b* next;

		list_b(const T& data, list_b* next = nullptr) : data(data), next(next){

		}
	};
    size_t size;
    list_b* begin;
    
    list_b* list_index(const size_t index, list_b *& prev) {
    	list_b* cur = begin;
    	for (size_t i = 0; i < index; ++i) {
    		prev = cur;
    		cur = cur->next;
    	}
    	return cur;
    }
    
    void delete_list() {
    	list_b* cur = begin;
    
    	while (cur != nullptr) {
    		begin = cur->next;
    		delete cur;
    		cur = begin;
    	}
    	size = 0;
    }
    
public:
    list() : begin(nullptr), size(0) {
    
    }
    
    list(const list& L) : size(L.size) {
    	list_b* cur = begin, *prev = nullptr, *cur_L = L.begin;
    	while (cur_L != nullptr) {
    		prev = cur;
    		cur = new list_b(cur_L->data);
    		if (prev != nullptr) {
    			prev->next = cur;
    		} else {
    			begin = cur;
    		}
    		cur_L = cur_L->next;
    	}
    }
    
    list<T>& operator=(const list& L) {
    	delete_list();
    	list_b* cur = begin, * prev = nullptr, * cur_L = L.begin;
    	while (cur_L != nullptr) {
    		prev = cur;
    		cur = new list_b(cur_L->data);
    		if (prev != nullptr) {
    			prev->next = cur;
    		} else {
    			begin = cur;
    		}
    		cur_L = cur_L->next;
    	}
    	size = L.size;
    	return *this;
    }
    
    void add_front(const T& elem) {
    	begin = new list_b(elem, begin);
    	++size;
    }
    
    void add_back(const T& elem) {
    	list_b* cur = begin, *prev = nullptr;;
    	while (cur != nullptr) {
    		prev = cur;
    		cur = cur->next;
    	}
    	cur = new list_b(elem);
    	prev->next = cur;
    	++size;
    }
    
    void add_index(const T& elem, size_t index) {
    	assert(index >= 0 && index <= size);
    
    	if (index == 0) {
    		add_front(elem);
    		return;
    	}
    
    	list_b* cur, *prev = nullptr;
    	cur = list_index(index, prev);
    
    	list_b* new_elem = new list_b(elem, cur);
    	prev->next = new_elem;
    	++size;
    }
    
    T pop_front() {
    	assert(!is_empty());
    	list_b* cur = begin;
    	T value = cur->data;
    	begin = cur->next;
    	delete cur;
    	--size;
    	return value;
    }
    
    T pop_back() {
    	assert(!is_empty());
    	list_b* cur = begin, * prev = nullptr;
    	while (cur != nullptr) {
    		prev = cur;
    		cur = cur->next;
    	}
    	T value = cur->data;
    	prev->next = nullptr;
    	delete cur;
    	--size;
    	return value;
    }
    
    T delete_index(size_t index) {
    	assert(index >= 0 && index < size);
    
    	if (index == 0) {
    		return pop_front();
    	}
    
    	list_b* cur, *prev;
    	cur = list_index(index, prev);
    	T value = cur->data;
    	prev->next = cur->next;
    	delete cur;
    	--size;
    	return value;
    }
    
    T& operator[](size_t index) {
    	assert(index >= 0 && index < size);
    	list_b* cur, *prev = nullptr;
    	cur = list_index(index, prev);
    	assert(cur != nullptr);
    	return cur->data;
    }
    
    const T& operator[](size_t index) const {
    	assert(index >= 0 && index < size);
    	list_b* cur, * prev = nullptr;
    	cur = list_index(index, prev);
    	assert(cur != nullptr);
    	return cur->data;
    }
    
    size_t get_size() const {
    	return size;
    }
    
    bool is_empty() const {
    	return size == 0;
    }
    
    ~list() {
    	delete_list();
    }
};