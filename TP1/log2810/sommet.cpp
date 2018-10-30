#include "sommet.h"
#include<functional>
#include<array>
	//Getters
	Node::Node(int number, bool station): totalDistance(invalidDistance)
	,  stationNumber(number)
	,  previousNode(NULL)
	,  bHasStation(station)
	,  bIsVisited(false)
	,  bisStart(false)

	{
		vehicule* test = new vehicule(0, invalidDistance);
		vehiculeStatus.push_back(test);
	}

	int Node::getTotalDistance() {
		return totalDistance;
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

	//setters
	void Node::updateDistance(int distance){
		totalDistance = distance;
	}
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
	int Node::getStationNumber() {
		return stationNumber;
	}
	void Node::resetNode() {
		previousNode = NULL;
		totalDistance = invalidDistance;
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
		if (!bHasStation) {
			for (unsigned int i = 0; i < archs.size(); i++) {
				if (archs[i].canUpdate())
				{
					archs[i].getNode2()->resetVehicule();
					archs[i].getNode2()->setPreviousNode(archs[i].getNode1());
					for (int j  = 0; j < vehiculeStatus.size(); j++) {
						vehicule* test = new vehicule((vehiculeStatus[j]->getPourcentage() - 6 * ((double)archs[i].getTime() / 60)), vehiculeStatus[j]->getTime() + archs[i].getTime());
						for (int z = 0; z < vehiculeStatus[j]->getWhereCharged().size(); z++) {
							test->addChargedStation(vehiculeStatus[j]->getWhereCharged()[z]);
						}
						archs[i].getNode2()->addVehiculeStatusAndSort(test);
					}
				}
			}
		}
		else {
			for (unsigned int i = 0; i < archs.size(); i++) {
				if (archs[i].canUpdate())
				{
					archs[i].getNode2()->resetVehicule();
					vector<vehicule*> temp = archs[i].getNode1()->getVehicule();
					archs[i].getNode2()->setPreviousNode(archs[i].getNode1());
					for (int j = 0; j < temp.size(); j++) {
						vehicule* test = new vehicule((temp[j]->getPourcentage() - 6 * ((double)(archs[i].getTime()) / 60)), temp[j]->getTime() + archs[i].getTime());
						
						vehicule* test2 =( temp[j]->getPourcentage() >= 20) ? new vehicule((100 - 6 * ((double)(archs[i].getTime()) / 60)), (temp[j]->getTime() + archs[i].getTime() + 120)): test;
						for (int z = 0; z < temp[j]->getWhereCharged().size(); z++) {
							int* number = temp[j]->getWhereCharged()[z];
							test->addChargedStation(number);
							test2->addChargedStation(number);
						}
						int* lol = new int(archs[i].getNode1()->getStationNumber());
						test2->addChargedStation(lol);
						archs[i].getNode2()->addVehiculeStatusAndSort(test);
						if(test2 != test)
							archs[i].getNode2()->addVehiculeStatusAndSort(test2);
					}
				}
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
