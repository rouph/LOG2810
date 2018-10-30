#include "sommet.h"
#include<functional>
#include<array>
	//Getters
	Node::Node(int number, bool station):
	   previousNode(NULL)
	,  bHasStation(station)
	,  bIsVisited(false)
	,  bisStart(false)

	{
		stationNumber = new int(number);
		vehicule* test = new vehicule(0, invalidDistance);
		vehiculeStatus.push_back(test);
	}



	Node* Node::getPreviousNode(){
		return previousNode;
	}

	bool Node::isVisited(){
		return bIsVisited;
	}
	bool Node::hasStation(){
		return bHasStation;
	}
	vector<arch> Node::getArchs(){
		return archs;
	}
	///////////////

	void Node::setPreviousNode(Node * prevNode) {
		previousNode = prevNode;
	}
	void Node::isVisited(bool status){
		bIsVisited = status;
	}
	void Node::hasStation(bool status){
		bHasStation = status;
	}
	void Node::addArch(arch element) {
		archs.push_back(element);
	}
	int* Node::getStationNumber() {
		return stationNumber;
	}
	void Node::resetNode() {
		previousNode = NULL;
		bIsVisited = false;
		for (int i = 0; i < vehiculeStatus.size(); i++)
			vehiculeStatus[i]->reset();
	}
	bool Node::isStart() {
		return bisStart;
	}
	void Node::isStart(bool status) {
		 bisStart = status;
	}
	void Node::updateNode(vector<Node*>& toUpdate) {


		for (unsigned int i = 0; i < archs.size(); i++) {
			if (!archs[i].getNode2()->isVisited()) {
				toUpdate.push_back(archs[i].getNode2());
				archs[i].getNode2()->isVisited(true);
			}
		}

		for (unsigned int i = 0; i < archs.size(); i++) {
			if (archs[i].canUpdate())
			{
				archs[i].updateNode2(bHasStation);
			}
		}

		if (toUpdate.size() > 1)
			toUpdate.erase(toUpdate.begin());

		std::sort(toUpdate.begin(), toUpdate.end(),
			[]( Node* a,  Node* b) -> bool
		{
			return a->getVehicule()[0]->getTime() <  b->getVehicule()[0]->getTime()		;
		});
	}

	void Node::addVehiculeStatusAndSort(vehicule* status) {
		vehiculeStatus.push_back(status);
		sortVehicule();
	}

	vector<vehicule*> Node::getVehicule(){
		return vehiculeStatus;
	}
	void Node::sortVehicule(){
		std::sort(vehiculeStatus.begin(), vehiculeStatus.end(),
			[](vehicule* a, vehicule* b) -> bool
		{
			return (a->getTime() < b->getTime()) && (a->getPourcentage() >= 20) || ((a->getTime() > b->getTime()) && (b->getPourcentage() < 20));
		});
	}


	void Node::resetVehicule() {
		for (int i = 0; i < vehiculeStatus.size(); i++)
			delete vehiculeStatus[i];
		vehiculeStatus.clear();
	}
