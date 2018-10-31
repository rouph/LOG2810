#include <fstream>
#include "graph.h"
#include <string>
#include <iostream>
graph::graph() : fileName("centresLocaux1.txt") {}

void graph::CreateGraph() {
	std::ifstream centreLocaux;
	centreLocaux.open(fileName);
	extractNodes(centreLocaux);
	ExtractArchs(centreLocaux);
	graphSet = false;
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
		arch ttest(Nodes[ifirstStation - 1], Nodes[isecondStation - 1], itime);
		arch lol(Nodes[isecondStation - 1], Nodes[ifirstStation - 1], itime);
		Nodes[ifirstStation - 1]->addArch(ttest);
		Nodes[isecondStation - 1]->addArch(lol);
	}
}
void graph::setShortestPath(int begining, int end, double pourcentageNeeded) {

	if(graphSet == true && !Nodes[begining - 1]->isStart())
		for (unsigned int i = 0; i < Nodes.size(); i++)
		{
			Nodes[i]->resetNode();
			queue.clear();

		}

	if (Nodes[begining - 1]->getVehicule()[0]->getTime() != 0) {
		graphSet = true;
		Nodes[begining - 1]->isStart(true);
		queue.push_back(Nodes[begining - 1]);
		Nodes[begining - 1]->getVehicule()[0]->updateTime(0);
		Nodes[begining - 1]->getVehicule()[0]->updatePourcentage(100);
		Nodes[begining - 1]->isVisited(true);
		//hon talama awal element mano  lelement a la posisiton end-1 we update
		while (queue[0] != Nodes[end - 1])
		{
			queue[0]->updateNode(queue, pourcentageNeeded);

		}
	}
}

void graph::affichagePlusCourChemin(Node* node) {

	if (node->getVehicule()[0]->getPourcentage() >= 0) {
		Node* prev = node;
		while (prev != NULL) {

			std::cout << *prev->getStationNumber() << "<-";
			prev = prev->getPreviousNode();
		}
		std::cout << "poucentage: " << node->getVehicule()[0]->getPourcentage() << " temps: " << node->getVehicule()[0]->getTime() << endl;

		if (node->getVehicule()[0]->getWhereCharged().size() > 0)
			std::cout << "avec recharge aux position : ";
		for (int i = 0; i < node->getVehicule()[0]->getWhereCharged().size(); i++) {
			std::cout << *node->getVehicule()[0]->getWhereCharged()[i] << " ";
		}
	}
	else {
		std::cout << " chemin impossbile car pourcentage finale < 20 " << endl;
	}
}


void graph::getShortestPath(int begining, int end, int patientType) {
	//NIHI
	switch (patientType) {
	case healthRisk::lowRisk:
		setShortestPath(begining, end, pourcentage::NINH::lowRisk);
		break;
	case healthRisk::mediumRisk:
		setShortestPath(begining, end, pourcentage::NINH::mediumRisk);
		break;
	case healthRisk::highRisk:
		setShortestPath(begining, end, pourcentage::NINH::highRisk);
		break;
	}
	//LIion
	if (Nodes[end - 1]->getVehicule()[0]->getPourcentage() < 20) {
		for (unsigned int i = 0; i < Nodes.size(); i++)
		{
			Nodes[i]->resetNode();
			queue.clear();
		}
		switch (patientType) {
		case healthRisk::lowRisk:
			setShortestPath(begining, end, pourcentage::LIion::lowRisk);
			break;
		case healthRisk::mediumRisk:
			setShortestPath(begining, end, pourcentage::LIion::mediumRisk);
			break;
		case healthRisk::highRisk:
			setShortestPath(begining, end, pourcentage::LIion::highRisk);
			break;
		}

	}

	affichagePlusCourChemin(Nodes[end - 1]);
}
