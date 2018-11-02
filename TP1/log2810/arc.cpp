#include"arc.h"
#include<iostream>

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

bool arch::shortestPathConditions(double pourcentagePerHour) {
	vehicule * node2BestVehicule = Node2->getVehicule()[0];
	vehicule * node1BestVehicule = Node1->getVehicule()[0];

	return (node2BestVehicule->getTime() > node1BestVehicule->getTime() + archtime
		&& (getNode1()->getVehicule()[0]->getPourcentage() - percentageNeeded(pourcentagePerHour)) >= 20 ||
		 (node2BestVehicule->getPourcentage()) < 20 ) && Node1->getPreviousNode() != Node2;
}

bool arch::subGraphConditions(double pourcentage){
	vehicule * node2BestVehicule = Node2->getVehicule()[0];
	vehicule * node1BestVehicule = Node1->getVehicule()[0];
	Node * prev = Node1;
	bool test = true;
	while(prev != NULL) {
		if (prev == Node2) {
			test = false;
			break;
		}
		else
			prev = prev->getPreviousNode();
	}
	return (node2BestVehicule->getTime() < node1BestVehicule->getTime() + archtime
		&& (getNode1()->getVehicule()[0]->getPourcentage() - percentageNeeded(pourcentage)) >= 20 ||
		  (node2BestVehicule->getPourcentage()) < 20) && test;
}

void arch::updateNode2(bool hasStation, double pourcentagePerHour) {

	Node2->resetVehicule();
	Node2->setPreviousNode(Node1);
	vector<vehicule*> vehiculeStatus = Node1->getVehicule();
	if (!hasStation)
		updateNode2VehiculeStatus(vehiculeStatus, pourcentagePerHour, false);
	else
		rechargeAndUpdateNode2VehiculeStatus(vehiculeStatus, pourcentagePerHour);
}

void arch::updateNode2VehiculeStatus(const vector<vehicule*>& vehiculeStatus,const double& pourcentagePerHour,const bool & canRecharge) {
	for (int j = 0; j < vehiculeStatus.size(); j++) {
		vehicule* test = new vehicule((vehiculeStatus[j]->getPourcentage() - percentageNeeded(pourcentagePerHour)), vehiculeStatus[j]->getTime() + archtime);
		for (int z = 0; z < vehiculeStatus[j]->getWhereCharged().size(); z++) {
			test->addChargedStation(vehiculeStatus[j]->getWhereCharged()[z]);
		}
		Node2->addVehiculeStatusAndSort(test, canRecharge);
	}
}

void arch::rechargeAndUpdateNode2VehiculeStatus(vector<vehicule*> vehiculeStatus, double pourcentagePerHour) {

	for (int j = 0; j < vehiculeStatus.size(); j++) {
		vehicule* notRecharged = new vehicule((vehiculeStatus[j]->getPourcentage() - percentageNeeded(pourcentagePerHour)), vehiculeStatus[j]->getTime() + archtime);
		vehicule* Recharged = (vehiculeStatus[j]->getPourcentage() >= 20) ? new vehicule(((double)100 - percentageNeeded(pourcentagePerHour)), (vehiculeStatus[j]->getTime() + archtime + 120)) : notRecharged;
		for (int z = 0; z < vehiculeStatus[j]->getWhereCharged().size(); z++) {
			int* number = vehiculeStatus[j]->getWhereCharged()[z];
			notRecharged->addChargedStation(number);
			Recharged->addChargedStation(number);
		}
		Recharged->addChargedStation(Node1->getStationNumber());
		Node2->addVehiculeStatusAndSort(notRecharged,true);
		if (Recharged != notRecharged)
			Node2->addVehiculeStatusAndSort(Recharged,true);
	}
}
double arch::percentageNeeded(double pourcentagePerHour) {

	return pourcentagePerHour * ((double)(archtime) / 60);
}

ostream& operator<<(ostream& o, const arch& pArch) {
	o << *pArch.Node2->getStationNumber() << ',' << pArch.archtime;
	return o;
}