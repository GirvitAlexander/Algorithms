#pragma once

#include <algorithm>

template <typename T>
class dynamic_array {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void change_capacity(size_t new_cap) {
        if (capacity_ == new_cap) {
            return;
        }
        T* new_data = copy_data(new_cap, *this);
        range_delete(data_, data_ + size_);
        operator delete(data_);
        data_ = new_data;
        capacity_ = new_cap;
    }

    static T* copy_data(size_t capacity, const dynamic_array<T>& other) {
        T* data_ = static_cast<T*>(operator new(sizeof(T) * capacity));
        size_t i = 0;
        for (; i < other.size_; ++i) {
            new (data_ + i) T(other.data_[i]);
        }
        return data_;
    }

    static void range_delete(T* start, T* end) {
        for (T* i = start; i < end; ++i) {
            i->~T();
        }
    }

public:
    dynamic_array() : size_(0), capacity_(0), data_(nullptr) {}
    
    dynamic_array(const dynamic_array& other) :
        data_(copy_data(other.capacity_, other)),
        size_(other.size_), capacity_(other.capacity_) {}
    
    dynamic_array& operator=(const dynamic_array& other) {
        if (this == &other) {
            return *this;
        }
        dynamic_array<T> tmp(other);
        std::swap(size_, tmp.size_);
        std::swap(capacity_, tmp.capacity_);
        std::swap(data_, tmp.data_);
        swap(tmp);
        return *this;
    }
    
    ~dynamic_array() {
        range_delete(data_, data_ + size_);
        operator delete(data_);
    }
    
    T& operator[](size_t i) {
        return *(data_ + i);
    }
    
    const T& operator[](size_t i) const {
        return *(data_ + i);
    }
    
    size_t get_size() const {
        return size_;
    }
    
    void push_back(const T& e) {
        T tmp(e);
        if (capacity_ == size_) {
            reserve((capacity_ == 0) ? 1 : capacity_ * 2);
        }
        new (data_ + size_) T(tmp);
        ++size_;
    }
    
    void pop_back() {
        range_delete(data_ + size_ - 1, data_ + size_);
        --size_;
    }
    
    bool is_empty() const {
        return (size_ == 0);
    }
    
    size_t capacity() const {
        return capacity_;
    }
    
    void clear() {
        range_delete(data_, data_ + size_);
        size_ = 0;
    }
    
    void reserve(size_t new_cap) {
        if (new_cap > capacity_) {
            change_capacity(new_cap);
        }
    }
    
    T& insert(size_t pos, const T& e) {
        push_back(e);
        for (size_t i = size_ - 1; i > pos; --i) {
            std::swap(data_[i], data_[i - 1]);
        }
    
        return *(data_ + pos);
    }
    
    void delete_pos(size_t pos) {
        for (size_t i = pos; i < size_; ++i) {
            std::swap(data_[i], data_[i + 1]);
        }
        range_delete(data_ + size_ - 1, data_ + size_);
        --size_;
    }
};