#ifndef ARCH_H
#define ARCH_H

#include "sommet.h"
#include "vehicule.h"
using namespace std;
class Node;
class arch {
public:
	arch(Node* node1, Node* node2, int itime);
	int getTime();
	Node* getNode1();
	Node* getNode2();
	bool canUpdate(double pourcentagePerHour);
	void updateNode2(bool hasStation, double pourcentagePerHour);
	void updateNode2VehiculeStatus(vector<vehicule*> vehiculeStatus, double pourcentagePerHour);
	void rechargeAndUpdateNode2VehiculeStatus(vector<vehicule*> vehiculeStatus, double pourcentagePerHour);
	friend ostream& operator<<(ostream &o, const arch& pArch);
private:
	double percentageNeeded(double pourcentagePerHour);
	int archtime;
	Node* Node1;
	Node* Node2;
};

#endif