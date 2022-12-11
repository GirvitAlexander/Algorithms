
#include <iostream>
#include <string>
#include "graph.h"



int main() {
	std::string file;
	std::cout << "Enter name file with graph:\n";
	std::cin >> file;

	Graph G(file);
	std::cout << "Enter the file name where will be mst:\n";
	std::cin >> file;

	G.MST(file);

	std::string str;
	std::cout << "Enter vertex name and the file name where will be dfs:\n";
	std::cin >> str >> file;
	G.dfs(str, file);

	std::cout << "Enter vertex name and the file name where will be bfs:\n";
	std::cin >> str >> file;
	G.bfs(str, file);
}