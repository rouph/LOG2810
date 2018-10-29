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
		vehicule test(0,invalidDistance);
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
				if (archs[i].getNode2()->getVehicule()[0].getTime() > archs[i].getNode1()->getVehicule()[0].getTime() + archs[i].getTime()
					&& (archs[i].getNode1()->getVehicule()[0].getPourcentage() - 6 * (archs[i].getTime()/60)) > 20 || 
					archs[i].getNode2()->getVehicule()[0].getTime() > archs[i].getNode1()->getVehicule()[0].getTime() + archs[i].getTime()
					&& (archs[i].getNode1()->getVehicule()[0].getPourcentage() < 20))
				{
					vector<vehicule> temp = archs[i].getNode1()->getVehicule();
					for (i = 0; i < temp.size(); i++) {
						vehicule test((temp[i].getPourcentage() - 6 * (archs[i].getTime() / 60)), temp[i].getTime() + archs[i].getTime());
						archs[i].getNode2()->resetVehicule();
						archs[i].getNode2()->addVehiculeStatusAndSort(test);
						archs[i].getNode2()->setPreviousNode(archs[i].getNode1());
					}
				}
			}
		}
		else
			for (unsigned int i = 0; i < archs.size(); i++) {
				if (archs[i].getNode2()->getVehicule()[0].getTime() > archs[i].getNode1()->getVehicule()[0].getTime() + archs[i].getTime()
					&& (archs[i].getNode1()->getVehicule()[0].getPourcentage() - 6 * (archs[i].getTime() / 60)) > 20 ||
					archs[i].getNode2()->getVehicule()[0].getTime() > archs[i].getNode1()->getVehicule()[0].getTime() + archs[i].getTime()
					&& (archs[i].getNode1()->getVehicule()[0].getPourcentage() < 20))
				{
					vector<vehicule> temp = archs[i].getNode1()->getVehicule();
					for (i = 0; i < temp.size(); i++) {
						vehicule test((temp[i].getPourcentage() - 6 * (archs[i].getTime() / 60)), temp[i].getTime() + archs[i].getTime());
						vehicule test2((100 - 6 * (archs[i].getTime() / 60), temp[i].getTime() + archs[i].getTime() + 120));
						for(int j = 0 ; j < temp[i].getWhereCharged().size();j++){
							test.addChargedStation(temp[i].getWhereCharged()[j]);
							test2.addChargedStation(temp[i].getWhereCharged()[j]);
						}
						test2.addChargedStation(archs[i].getNode1()->getStationNumber());
						archs[i].getNode2()->resetVehicule();
						archs[i].getNode2()->addVehiculeStatusAndSort(test);
						archs[i].getNode2()->addVehiculeStatusAndSort(test2);
						archs[i].getNode2()->setPreviousNode(archs[i].getNode1());
					}
				}
			}
		if (toUpdate.size() > 1)
			toUpdate.erase(toUpdate.begin());

		std::sort(toUpdate.begin(), toUpdate.end(),
			[]( Node* a,  Node* b) -> bool
		{
			return a->getVehicule()[0].getTime() <  b->getVehicule()[0].getTime() && a->getVehicule()[0].getPourcentage() >= 20 && b->getVehicule()[0].getPourcentage();
		});
	}

	void Node::addVehiculeStatusAndSort(vehicule status) {
		vehiculeStatus.push_back(status);
		sortVehicule();
	}

	vector<vehicule> Node::getVehicule(){
		return vehiculeStatus;
	}
	void Node::sortVehicule(){
		std::sort(vehiculeStatus.begin(), vehiculeStatus.end(),
			[](vehicule a, vehicule b) -> bool
		{
			return (a.getTime() < b.getTime()) && (a.getPourcentage() > 20) && (b.getPourcentage() > 20);
		});
	}

	void Node::resetVehicule() {
		vehiculeStatus.clear();
	}
