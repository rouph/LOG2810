#include "graph.h"
#include <iostream>
int main() 
{
	graph test;
	test.CreateGraph();
	test.getShortestPath(1, 2);
	std::cout << endl;
	test.getShortestPath(1, 5);
	std::cout << endl;
	test.getShortestPath(1, 3);
	std::cout << endl;
	test.getShortestPath(1, 4);
	std::cout << endl;
	test.getShortestPath(1, 1);
	std::cout << endl;
	test.getShortestPath(3, 5);
	return 0;
}