#pragma once
#include <cassert>

template <class T>
class queue {
private:

    struct list_b {
        T data;
        list_b* next;

        list_b(const T& data, list_b* next = nullptr) : data(data), next(next) {

        }
    };
    size_t size;
    list_b* begin;
    list_b* end;

    void delete_queue() {
        list_b* cur = begin;

        while (cur != nullptr) {
            begin = cur->next;
            delete cur;
            cur = begin;
        }
        size = 0;
    }

public:
    queue() : begin(nullptr), end(nullptr), size(0) {

    }

    void push(const T& elem) {
        if (begin == nullptr) {
            begin = new list_b(elem);
            end = begin;
        }
        else {
            end->next = new list_b(elem);
            end = end->next;
        }
        ++size;
    }

    T pop() {
        assert(!is_empty());
        list_b* cur = begin;
        T value = cur->data;
        begin = cur->next;
        delete cur;
        --size;
        return value;
    }

    size_t get_size() const {
        return size;
    }

    bool is_empty() const {
        return size == 0;
    }

    ~queue() {
        delete_queue();
    }
};