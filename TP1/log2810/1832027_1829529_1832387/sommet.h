#ifndef NODE_H
#define NODE_H

#include <vector>
#include "arc.h"
#include "constante.h"
#include "vehicule.h"
#include <string>
using namespace std;
class arch;
class vehicule;
class Node {

public:
	Node(int number, bool station);
	~Node();
	Node* getPreviousNode();
	bool isInQueue();
	bool hasStation();
	int* getStationNumber();
	vector<arch> getArchs();


	//setters
	void setPreviousNode(Node * prevNode);
	void isInQueue(bool status);
	void hasStation(bool status);
	void addArch(arch element);
	string getVehiculeType();
	void setVehiculeType(string type);
	//reset
	void resetNode();

	//algo
	void updateNode(vector<Node*>& toUpdate, double& PercentageNeeded, bool canRecharge);
	void addVehiculeStatusAndSort(vehicule* status,const bool & canRecharge = true);
	vector<vehicule*> getVehicule();
	void sortVehicule(const bool & canRecharge);
	void resetVehicule();
	void clearNode();
	friend ostream& operator<<(ostream& o, const Node& node);
private:

	int* stationNumber;
	vector<vehicule*> vehiculeStatus;

	Node * previousNode;
	bool bHasStation;
	bool bIsInQueue;
	string vehiculeType;
	vector<arch> archs;
};

#endif