#ifndef NODE_H
#define NODE_H

#include <vector>
#include "arc.h"
#include "constante.h"
#include "vehicule.h"
using namespace std;
class arch;
class vehicule;
class Node {
	//Getters
public:
	Node(int number, bool station);

	int getTotalDistance();
	Node* getPreviousNode();
	bool isVisited();
	bool hasStation();
	int getStationNumber();
	vector<arch> getArchs();
	bool isStart();
	///////////////

	//setters
	void updateDistance(int distance);
	void setPreviousNode(Node * prevNode);
	void isVisited(bool status);
	void hasStation(bool status);
	void addArch(arch element);
	void isStart(bool status);
	//reset
	void resetNode();

	//algo
	void updateNode(vector<Node*>& toUpdate);

	void addVehiculeStatusAndSort(vehicule status);
	vector<vehicule> getVehicule();
	void sortVehicule();
	void resetVehicule();
private:
	int totalDistance;
	bool bisStart;
	int stationNumber;

	vector<vehicule> vehiculeStatus;

	Node * previousNode;
	bool bHasStation;
	bool bIsVisited;
	vector<arch> archs;
};

#endif