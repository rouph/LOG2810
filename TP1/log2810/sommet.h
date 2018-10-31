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
	Node* getPreviousNode();
	bool isVisited();
	bool hasStation();
	int* getStationNumber();
	vector<arch> getArchs();
	bool isStart();
	///////////////

	//setters
	void setPreviousNode(Node * prevNode);
	void isVisited(bool status);
	void hasStation(bool status);
	void addArch(arch element);
	void isStart(bool status);
	//reset
	void resetNode();

	//algo
	void updateNode(vector<Node*>& toUpdate, double pourcentageNeeded);

	void addVehiculeStatusAndSort(vehicule* status);
	vector<vehicule*> getVehicule();
	void sortVehicule();
	void resetVehicule();
	void clearNode();
	friend ostream& operator<<(ostream& o, const Node& node);
private:

	bool bisStart;
	int* stationNumber;
	vector<vehicule*> vehiculeStatus;

	Node * previousNode;
	bool bHasStation;
	bool bIsVisited;
	vector<arch> archs;
};

#endif