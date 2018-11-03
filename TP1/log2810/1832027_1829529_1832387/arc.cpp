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

bool arch::shortestPathConditions(double PercentagePerHour) {
	vehicule * node2BestVehicule = Node2->getVehicule()[0];
	vehicule * node1BestVehicule = Node1->getVehicule()[0];

	return (node2BestVehicule->getTime() > node1BestVehicule->getTime() + archtime
			&& (getNode1()->getVehicule()[0]->getPercentage() - percentageNeeded(PercentagePerHour)) >= 20 
			|| (node2BestVehicule->getPercentage()) < 20 ) 
		&& Node1->getPreviousNode() != Node2;
}

bool arch::subGraphConditions(double Percentage){
	vehicule * node2BestVehicule = Node2->getVehicule()[0];
	vehicule * node1BestVehicule = Node1->getVehicule()[0];
	Node * prev = Node1;
	bool node1Present = true;
	/*ce while verifie que le Node1 n'est pas deja dans le Path*/
	while(prev != NULL) {
		if (prev == Node2) {
			node1Present = false;
			break;
		}
		else
			prev = prev->getPreviousNode();
	}
	return (node2BestVehicule->getTime() < node1BestVehicule->getTime() + archtime
		&& (getNode1()->getVehicule()[0]->getPercentage() - percentageNeeded(Percentage)) >= 20 ||
		  (node2BestVehicule->getPercentage()) < 20) && node1Present;
}

void arch::updateNode2(bool hasStation, double PercentagePerHour) {

	Node2->resetVehicule();
	Node2->setPreviousNode(Node1);

	vector<vehicule*> vehiculeStatus = Node1->getVehicule();
	if (!hasStation)
		updateNode2VehiculeStatus(vehiculeStatus, PercentagePerHour, false);
	else
		rechargeAndUpdateNode2VehiculeStatus(vehiculeStatus, PercentagePerHour);
}

void arch::updateNode2VehiculeStatus(const vector<vehicule*>& vehiculeStatus,const double& PercentagePerHour,const bool & canRecharge) {
	for (unsigned int j = 0; j < vehiculeStatus.size(); j++) {
		vehicule* notRecharged = new vehicule((vehiculeStatus[j]->getPercentage() - percentageNeeded(PercentagePerHour)), vehiculeStatus[j]->getTime() + archtime);
		for (unsigned int z = 0; z < vehiculeStatus[j]->getWhereCharged().size(); z++) {
			notRecharged->addChargedStation(vehiculeStatus[j]->getWhereCharged()[z]);
		}
		Node2->addVehiculeStatusAndSort(notRecharged, canRecharge);
	}
}

void arch::rechargeAndUpdateNode2VehiculeStatus(vector<vehicule*> vehiculeStatus, double PercentagePerHour) {

	for (unsigned int j = 0; j < vehiculeStatus.size(); j++) {

		vehicule* notRecharged = new vehicule((vehiculeStatus[j]->getPercentage() - percentageNeeded(PercentagePerHour)), vehiculeStatus[j]->getTime() + archtime);

		vehicule* Recharged = (vehiculeStatus[j]->getPercentage() >= 20) ? new vehicule(((double)100 - percentageNeeded(PercentagePerHour)), (vehiculeStatus[j]->getTime() + archtime + 120)) : notRecharged;

		for (unsigned int z = 0; z < vehiculeStatus[j]->getWhereCharged().size(); z++) {
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

double arch::percentageNeeded(double PercentagePerHour) {
	return PercentagePerHour * ((double)(archtime) / 60);
}

ostream& operator<<(ostream& o, const arch& pArch) {
	o << *pArch.Node2->getStationNumber() << ',' << pArch.archtime;
	return o;
}