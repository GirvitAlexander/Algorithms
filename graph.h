#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

#include "dsu.h"
#include "dynamic_arr.h"
#include "stack.h"
#include "queue.h"
#include "list.h"

class Graph {
private:

    struct vertex {
        size_t weight;
        size_t num;
        vertex() : num(0), weight(0) {};
        vertex(const size_t& weight, const size_t& num) : weight(weight), num(num) {}
    };

	// Ребро
	struct edge {
		size_t weight;
        size_t ver1, ver2;

		edge(const size_t& weight, const size_t& ver1, const size_t& ver2) :
			weight(weight), ver1(ver1), ver2(ver2) {}
	};

    // Знак меньше для двух рёбер по весам
    bool compare_left_w(const edge& e1, const edge& e2) {
        if (e1.weight == e2.weight) {
            if (ver[e1.ver1] == ver[e1.ver1]) {
                return ver[e1.ver2] < ver[e2.ver2];
            }
            return ver[e1.ver1] < ver[e2.ver1];
        }
        return e1.weight < e2.weight;
    }
    // Равенство двух рёбер по весам
    bool equals_w(const edge& e1, const edge& e2) {
        if (e1.weight == e2.weight) {
            if (ver[e1.ver1] == ver[e1.ver1]) {
                if (ver[e1.ver2] == ver[e2.ver2]) {
                    return true;
                }
            }
        }
        return false;
    }

    // Знак меньше для двух рёбер по вершинам
    bool compare_left_v(const edge& e1, const edge& e2) {
        if (ver[e1.ver1] == ver[e2.ver1]) {
            return ver[e1.ver2] < ver[e2.ver2];
        }

        return ver[e1.ver1] < ver[e2.ver1];
    }
    // Равенство двух рёбер по вершинам
    bool equals_v(const edge& e1, const edge& e2) {
        if (ver[e1.ver1] == ver[e2.ver1]) {
            if (ver[e1.ver2] == ver[e2.ver2]) {
                return true;
            }
        }

        return false;
    }

    // Вспомогательная фукция для QuickSort
    size_t randInt(size_t l, size_t r)
    {
        r -= l;
        float m = (float)rand() / RAND_MAX;

        return l + m * r;
    }
    // QuickSort граней по весам
    void qSort_edge_weight(int l, int r)
    {
        if (r <= l)
            return;

        edge x = edge_graph[randInt(l, r)];
        int m = l, k = l;
        for (int i = l; i <= r; i++)
        {
            if (compare_left_w(edge_graph[i], x))
                swap_edge_weight(i, m++);
            else if (equals_w(edge_graph[i], x))
            {
                swap_edge_weight(i, k++);
                if (m != k - 1)
                    swap_edge_weight(i, m++);
                else
                    m++;
            }
        }
        int q = m - 1;
        for (int i = l; i < k; i++)
            swap_edge_weight(i, q--);

        qSort_edge_weight(l, m - k + l - 1);
        qSort_edge_weight(m, r);
    }

    // Swap двух граней
    void swap_edge_weight(int i, int j)
    {
        edge tmp = edge_graph[i];
        edge_graph[i] = edge_graph[j];
        edge_graph[j] = tmp;
    }

    // QuickSort граней по вершинам
    void qSort_edge_vertex(int l, int r)
    {
        if (r <= l)
            return;

        edge x = mst[randInt(l, r)];
        int m = l, k = l;
        for (int i = l; i <= r; i++)
        {
            if (compare_left_v(mst[i], x))
                swap_edge_vertex(i, m++);
            else if (equals_v(mst[i], x))
            {
                swap_edge_vertex(i, k++);
                if (m != k - 1)
                    swap_edge_vertex(i, m++);
                else
                    m++;
            }
        }
        int q = m - 1;
        for (int i = l; i < k; i++)
            swap_edge_vertex(i, q--);

        qSort_edge_vertex(l, m - k + l - 1);
        qSort_edge_vertex(m, r);
    }

    // Swap двух граней
    void swap_edge_vertex(int i, int j)
    {
        edge tmp = mst[i];
        mst[i] = mst[j];
        mst[j] = tmp;
    }

	// Ребра графа
	dynamic_array<edge> edge_graph;
    // Граф (список смежности)
    dynamic_array<dynamic_array<vertex>> graph;
    // Минимальное остовое дерево
    dynamic_array<edge> mst;
    // Вершины
    dynamic_array<std::string> ver;

    // Проверка на нахождении вершины в массиве
    size_t check(const std::string& str, bool new_elem = true) {
        for (size_t i = 0; i < ver.get_size(); ++i) {
            if (ver[i] == str) {
                return i;
            }
        }
        assert(new_elem);
        ver.push_back(str);
        graph.push_back(dynamic_array<vertex>());
        return ver.get_size() - 1;
    }

    // Алгоритм Крускала
    void Kruskala() {
        size_t count = 1, cur_edge = 0;
        dsu DSU(ver.get_size());
        while (count != ver.get_size()) {
            if (DSU.get_set(edge_graph[cur_edge].ver1) != DSU.get_set(edge_graph[cur_edge].ver2)) {
                DSU.union_set(edge_graph[cur_edge].ver1, edge_graph[cur_edge].ver2);
                mst.push_back(edge_graph[cur_edge]);
                count++;
            }
            cur_edge++;
        }
    }
public:
    // Инициализация графа
	Graph(const std::string& file) {
        std::string ver1, ver2;
        size_t weight;
        std::ifstream in(file);
        if (in.is_open())
        {
            while (in >> ver1 >> ver2 >> weight)
            {
                size_t ver1_num = check(ver1),
                       ver2_num = check(ver2);
                if (ver1 < ver2) {
                    edge_graph.push_back(edge(weight, ver1_num, ver2_num));
                }
                else {
                    edge_graph.push_back(edge(weight, ver2_num, ver1_num));
                }
            
                graph[ver1_num].push_back(vertex(weight, ver2_num));
                graph[ver2_num].push_back(vertex(weight, ver1_num));
            }
        }
        
        in.close();
	}

    // Поиск минимального остового дерева
    void MST(const std::string& file) {
        qSort_edge_weight(0, edge_graph.get_size() - 1);
        Kruskala();
        std::ofstream out(file);
        size_t sum = 0;
        if (out.is_open())
        {
            qSort_edge_vertex(0, mst.get_size() - 1);
            for (size_t i = 0; i < mst.get_size(); ++i)
            {
                out << ver[mst[i].ver1] << " " << ver[mst[i].ver2] << "\n";
                sum += mst[i].weight;
            }
            out << sum;
        }
        out.close();
    }

    // Обход в глубину
    void dfs(const std::string& str, const std::string& file) {
        std::ofstream out(file);
        if (out.is_open())
        {
            size_t str_num = check(str, false);
            stack<size_t> stack;
            bool* used;

            used = new bool[ver.get_size()];
            for (size_t i = 0; i < ver.get_size(); ++i) {
                used[i] = false;
            }
            stack.push(str_num);
            while (!stack.is_empty()) {
                str_num = stack.pop();
                if (!used[str_num]) {
                    used[str_num] = true;
                    out << ver[str_num] << "\n";
                }
                for (size_t i = 0; i < graph[str_num].get_size(); ++i) {
                    if (!used[graph[str_num][i].num]) {
                        stack.push(graph[str_num][i].num);
                    }
                }
            }

            delete[] used;
        }
        out.close();
    }

    // Обход в ширину
    void bfs(const std::string& str, const std::string& file) {
        std::ofstream out(file);
        if (out.is_open())
        {
            size_t str_num = check(str, false);
            queue<size_t> queue;
            bool* used;

            used = new bool[ver.get_size()];
            for (size_t i = 0; i < ver.get_size(); ++i) {
                used[i] = false;
            }
            queue.push(str_num);
            while (!queue.is_empty()) {
                str_num = queue.pop();
                if (!used[str_num]) {
                    used[str_num] = true;
                    out << ver[str_num] << "\n";
                }
                for (size_t i = 0; i < graph[str_num].get_size(); ++i) {
                    if (!used[graph[str_num][i].num]) {
                        queue.push(graph[str_num][i].num);
                    }
                }
            }

            delete[] used;
        }
        out.close();
    }
};