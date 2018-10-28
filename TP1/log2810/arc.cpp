#include"arc.h"


arch::arch(Node* node1, Node* node2, int itime) : Node1(node1)
	, Node2(node2)
	, time(itime)
{
}

int arch::getTime(){
	return time;
}

Node* arch::getNode1(){
	return Node1;
}

Node* arch::getNode2(){
	return Node2;
}

