#ifndef ARCH_H
#define ARCH_H

#include "sommet.h"

using namespace std;
class Node;
class arch {
public:
	arch(Node* node1, Node* node2, int itime);
	int getTime();
	Node* getNode1();
	Node* getNode2();

private:
	int time;
	Node* Node1;
	Node* Node2;
};

#endif