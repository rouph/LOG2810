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

	{}

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
		//hyde btehtam bl algo akide fina nhasena bas se3a 12am anw bhebkon
		//so awal for ta yhat kel node lma chefnehon bl queue
		for (unsigned int i = 0; i < archs.size(); i++) {
			if (!archs[i].getNode2()->isVisited()) {
				toUpdate.push_back(archs[i].getNode2());
				archs[i].getNode2()->isVisited(true);
			}
		}
		//tene for hone kermel yzabet ldistance wel prev metel ma hkina
		for (unsigned int i = 0; i < archs.size(); i++) {
			if (archs[i].getNode2()->getTotalDistance() > archs[i].getNode1()->getTotalDistance() + archs[i].getTime()) {
				archs[i].getNode2()->updateDistance(archs[i].getNode1()->getTotalDistance() + archs[i].getTime());
				archs[i].getNode2()->setPreviousNode(archs[i].getNode1());
			}
		}
		//hon bi mahe awal element men lvecteur, lezem nghayer an vecteur coz nhame awal position sa coute le l'argent esti
		if (toUpdate.size() > 1)
			toUpdate.erase(toUpdate.begin());
		//icite on sort(e) le'osti dvector ta nerja nchuf chu next element li nar nechteghel 3le
		std::sort(toUpdate.begin(), toUpdate.end(),
			[]( Node* a,  Node* b) -> bool
		{
			return a->getTotalDistance() <  b->getTotalDistance();
		});
	}

