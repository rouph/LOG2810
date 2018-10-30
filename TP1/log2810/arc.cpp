#include"arc.h"


arch::arch(Node* node1, Node* node2, int itime) : Node1(node1)
	, Node2(node2)
	, archtime(itime)
{
}

int arch::getTime(){
	return archtime;
}

Node* arch::getNode1(){
	return Node1;
}

Node* arch::getNode2(){
	return Node2;
}

bool arch::canUpdate() {
	vehicule * node2BestVehicule = Node2->getVehicule()[0];
	vehicule * node1BestVehicule = Node1->getVehicule()[0];

	return (node2BestVehicule->getTime() > node1BestVehicule->getTime() + archtime
		&& (getNode1()->getVehicule()[0]->getPourcentage() - 6 * ((double)(archtime) / 60)) >= 20 ||

		node2BestVehicule->getTime() > Node1->getVehicule()[0]->getTime() + archtime
		&& (node2BestVehicule->getPourcentage()) < 20  ||

		node2BestVehicule->getTime() < Node1->getVehicule()[0]->getTime() + archtime
		&& (node2BestVehicule->getPourcentage() < 20) ) && Node1->getPreviousNode() != Node2;
}