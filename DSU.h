#pragma once
#include "dynamic_arr.h"

class dsu {
	size_t* parent;
	size_t* rank;
	size_t size;

	void swap(size_t &x, size_t &y) {
		size_t temp = x;
		x = y;
		y = temp;
	}

public:

	void union_set(size_t element_1, size_t element_2) {
		size_t set_1, set_2;
		set_1 = get_set(element_1);
		set_2 = get_set(element_2);
		if (set_1 == set_2)
			return;

		if (rank[set_1] > rank[set_2])
			swap(set_1, set_2);

		parent[set_1] = set_2;

		if (rank[set_1] == rank[set_2])
			++rank[set_2];
	}

	size_t get_set(size_t element) {
		if (parent[element] != element)
			parent[element] = get_set(parent[element]);
		return parent[element];
	}

	dsu(size_t max_elem) : parent(new size_t[max_elem]), rank(new size_t[max_elem]), size(max_elem) {
		for (size_t i = 0; i < max_elem; ++i) {
			parent[i] = i;
			rank[i] = 1;
		}
	}

	~dsu() {
		delete[] parent;
		delete[] rank;
	}
};