#include <fstream>
#include "graph.h"
#include <string>
#include <iostream>
#include<functional>
#include <array>

graph::graph(){}

void graph::CreateGraph(string fileName) {
	
	for (unsigned int i = 0; i < Nodes.size(); i++) {
		Nodes[i]->clearNode();
		delete Nodes[i];
	}
	Nodes.clear();
	graphSet = false;
	
	std::ifstream centreLocaux(fileName);
	//centreLocaux.open(fileName);
	if (centreLocaux.fail()) {
		string e("invalid file name");
		throw e;
	}
	extractNodes(centreLocaux);
	ExtractArchs(centreLocaux);
	graphSet = true;
}
void graph::extractNodeInfo(string& line, int& number, bool& hasStation) {
	string temp = "";
	unsigned int i;
	for ( i = 0; i < line.size(); i++)
	{
		if (line[i] != ',') {
			temp += line[i];
		}
		else
			break;
	}
	number = atoi(temp.c_str());
	hasStation = (line[i+1] == '1');
}
void graph::extractNodes(ifstream& file) {
	while (!file.eof()) {
		string line;
		getline(file, line);
		if (line == "")
			break;
		int number;
		bool hasStation;
		extractNodeInfo(line, number, hasStation);

		Node* temp = new Node(number, hasStation);
		Nodes.push_back(temp);
	}
}
void graph::ExtractArchs(ifstream& file) {
	while (!file.eof()) {
		string firstStation, secondStation, time;
		int ifirstStation, isecondStation, itime;
		getline(file, firstStation, ',');
		getline(file, secondStation, ',');
		getline(file, time);

		ifirstStation = atoi(firstStation.c_str());
		isecondStation = atoi(secondStation.c_str());
		itime = atoi(time.c_str());

		arch wArch(Nodes[ifirstStation - 1], Nodes[isecondStation - 1], itime);
		arch iArch(Nodes[isecondStation - 1], Nodes[ifirstStation - 1], itime);
		Nodes[ifirstStation - 1]->addArch(wArch);
		Nodes[isecondStation - 1]->addArch(iArch);
	}
}
void graph::setShortestPath(int beginning, int end, double pourcentageNeeded) {

	if (!graphSet) 
	{
		string error("Please enter a fileName (option 1)");
		throw error;
	}

	queue.push_back(Nodes[beginning - 1]);
	Nodes[beginning - 1]->getVehicule()[0]->updateTime(0);
	Nodes[beginning - 1]->getVehicule()[0]->updatePourcentage(100);

	while (queue[0] != Nodes[end - 1])
	{
		queue[0]->updateNode(queue, pourcentageNeeded, true);
	}
}

void graph::affichageChemin(Node* node) {

	if (node->getVehicule()[0]->getPourcentage() >= 0) {
		Node* prev = node;
		vector<Node*> toCout;
		while (prev != NULL) {
			toCout.push_back(prev);
			prev = prev->getPreviousNode();
		}
		for (unsigned int i = toCout.size() - 1; i > 0; i--) {
			cout << *toCout[i]->getStationNumber() << " -> ";
		}
		cout << *toCout[0]->getStationNumber() << endl;
		std::cout << "pourcentage: " << node->getVehicule()[0]->getPourcentage() << " temps: " << node->getVehicule()[0]->getTime() << endl;
		std::cout << "Vehicule used: " << node->getVehiculeType() << endl;
		if (node->getVehicule()[0]->getWhereCharged().size() > 0)
			std::cout << "Recharged at : ";
		for (unsigned int i = 0; i < node->getVehicule()[0]->getWhereCharged().size(); i++) {
			std::cout << *node->getVehicule()[0]->getWhereCharged()[i] << " ";
		}
	}
	else {
		std::cout << " No possible Path, final pourcentage < 20 " << endl;
	}
}
void graph::getShortestPath(int beginning, int end, int patientType) {
	if (!graphSet) {
		string error("Please enter a fileName (option 1)");
		throw error;
	}

	string e;
	if (beginning < *(Nodes[0]->getStationNumber()) || end > Nodes.size()) {
		e = "poisitions must be between "  + to_string(*(Nodes[0]->getStationNumber())) +" and " + to_string(Nodes.size()) ;
	}
	if (patientType < 1 || patientType > 3) {
		e += '\n';
		e += "please enter valid patient type (1,2,3)";
	}
	if (!e.empty()) {
		throw e;
	}
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		Nodes[i]->resetNode();
		queue.clear();
	}

	Nodes[end - 1]->setVehiculeType("NIHI");
	switch (patientType) {
	case healthRisk::lowRisk:
		setShortestPath(beginning, end, pourcentage::NIMH::lowRisk);
		break;
	case healthRisk::mediumRisk:
		setShortestPath(beginning, end, pourcentage::NIMH::mediumRisk);
		break;
	case healthRisk::highRisk:
		setShortestPath(beginning, end, pourcentage::NIMH::highRisk);
		break;
	}
	//LIion

	if (Nodes[end - 1]->getVehicule()[0]->getPourcentage() < 20) {
		Nodes[end - 1]->setVehiculeType("LIion");
		for (unsigned int i = 0; i < Nodes.size(); i++)
		{
			Nodes[i]->resetNode();
			queue.clear();
		}

		switch (patientType) {
		case healthRisk::lowRisk:
			setShortestPath(beginning, end, pourcentage::LIion::lowRisk);
			break;
		case healthRisk::mediumRisk:
			setShortestPath(beginning, end, pourcentage::LIion::mediumRisk);
			break;
		case healthRisk::highRisk:
			setShortestPath(beginning, end, pourcentage::LIion::highRisk);
			break;
		}

	}

	affichageChemin(Nodes[end - 1]);
}
void graph::displayGraph() {
	for (unsigned int i = 0; i < Nodes.size(); i++) {
		cout << *Nodes[i] << endl;
	}
	cout << endl;
}

void graph::sousGraph(int beginning,int vehiculeType, int PatientType) {
	for (unsigned int i = 0; i < Nodes.size(); i++)
	{
		Nodes[i]->resetNode();
		queue.clear();
	}
	double pourcentageNeeded = determinePourcentageNeeded(vehiculeType, PatientType);
	queue.push_back(Nodes[beginning - 1]);
	Nodes[beginning - 1]->getVehicule()[0]->updateTime(0);
	Nodes[beginning - 1]->getVehicule()[0]->updatePourcentage(100);
	Nodes[beginning - 1]->isInQueue(true);

	while (queue.size() > 0)
	{
		queue[0]->updateNode(queue, pourcentageNeeded, false);
	}

	vector<Node*> temp = Nodes;
	std::sort(temp.begin(), temp.end(),
		[](Node* a, Node* b) -> bool
	{
		return (a->getVehicule()[0]->getTime() > b->getVehicule()[0]->getTime()) && ((a->getVehicule()[0]->getPourcentage() >= 20));
	});

	affichageChemin(temp[0]);
}

double graph::determinePourcentageNeeded(int vehiculeType, int PatientType)
{
	string e;
	if (vehiculeType < 1 || vehiculeType > 2) {
		e = "Please chose a valid vehicule type (1, 2)";
	}
	if (PatientType < 1 || PatientType > 3) {
		e += '\n';
		e += "please enter valid patient type (1, 2, 3)";
	}
	if (!e.empty()) {
		throw e;
	}

	switch (PatientType) {
	case healthRisk::lowRisk:
		return  vehiculeType == 1 ? pourcentage::NIMH::lowRisk : pourcentage::LIion::lowRisk;
	case healthRisk::mediumRisk:
		return  vehiculeType == 1 ? pourcentage::NIMH::mediumRisk : pourcentage::LIion::mediumRisk;
	case healthRisk::highRisk:
		return  vehiculeType == 1 ? pourcentage::NIMH::highRisk : pourcentage::LIion::highRisk;
	}
}	