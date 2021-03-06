#include "sommet.h"
#include<functional>
#include<array>
//Getters
Node::Node(int number, bool station):
   previousNode(NULL)
,  bHasStation(station)
,  bIsInQueue(false)
{
	stationNumber = new int(number);
	vehicule* invalidStatus = new vehicule(0, invalidDistance);
	vehiculeStatus.push_back(invalidStatus);
}

Node::~Node() {
	
	for (unsigned int i = 0; i < vehiculeStatus.size(); i++) {
		delete vehiculeStatus[i];
	}
	vehiculeStatus.clear();
	delete stationNumber;
}

Node* Node::getPreviousNode(){
	return previousNode;
}

bool Node::isInQueue(){
	return bIsInQueue;
}

bool Node::hasStation(){
	return bHasStation;
}

vector<arch> Node::getArchs(){
	return archs;
}

void Node::setPreviousNode(Node * prevNode) {
	previousNode = prevNode;
}

void Node::isInQueue(bool status){
	bIsInQueue = status;
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

string Node::getVehiculeType() {
	return vehiculeType;
}

void Node::setVehiculeType(string type) {
	vehiculeType = type;
}
void Node::resetNode() {
	previousNode = NULL;
	bIsInQueue = false;
	clearNode();
	vehicule* invalidStatus = new vehicule(0, invalidDistance);
	vehiculeStatus.push_back(invalidStatus);
}

void Node::clearNode() {
	for (unsigned int i = 0; i < vehiculeStatus.size(); i++) {
		vehiculeStatus[i]->reset();
		delete vehiculeStatus[i];
	}
	vehiculeStatus.clear();
}

void Node::updateNode(vector<Node*>& toUpdate, double& PercentageNeeded, bool canRecharge) {
	for (unsigned int i = 0; i < archs.size(); i++) {
		if (!archs[i].getNode2()->isInQueue()) {
			toUpdate.push_back(archs[i].getNode2());
			archs[i].getNode2()->isInQueue(true);
		}
	}
	for (unsigned int i = 0; i < archs.size(); i++) {
		if (canRecharge) {
			if (archs[i].shortestPathConditions(PercentageNeeded))
			{
				archs[i].updateNode2(bHasStation, PercentageNeeded);
			}
		}
		else if (archs[i].subGraphConditions(PercentageNeeded))
		{
			archs[i].getNode2()->resetVehicule();
			archs[i].getNode2()->setPreviousNode(archs[i].getNode1());
			vector<vehicule*> vehiculeStatus = archs[i].getNode1()->getVehicule();
			archs[i].updateNode2VehiculeStatus(vehiculeStatus, PercentageNeeded, canRecharge);
		}
	}

	if (toUpdate.size() >= 1)
		toUpdate.erase(toUpdate.begin());

	std::sort(toUpdate.begin(), toUpdate.end(),
		[&](Node* a, Node* b) -> bool
	{
		if (canRecharge)
			return a->getVehicule()[0]->getTime() < b->getVehicule()[0]->getTime();
		else
			return a->getVehicule()[0]->getTime() > b->getVehicule()[0]->getTime();
	});
		
}

void Node::addVehiculeStatusAndSort(vehicule* status, const bool & canRecharge) {
	vehiculeStatus.push_back(status);
	sortVehicule(canRecharge);
}

vector<vehicule*> Node::getVehicule(){
	return vehiculeStatus;
}

void Node::sortVehicule(const bool & canRecharge){
	std::sort(vehiculeStatus.begin(), vehiculeStatus.end(),
		[&](vehicule* a, vehicule* b) -> bool
	{
		if(canRecharge)
			return (a->getTime() < b->getTime()) && (a->getPercentage() >= 20) || ((a->getTime() > b->getTime()) && (b->getPercentage() < 20));
		else
			return (a->getTime() > b->getTime()) && (a->getPercentage() >= 20);
	});
}


void Node::resetVehicule() {
	for (unsigned int i = 0; i < vehiculeStatus.size(); i++)
		delete vehiculeStatus[i];
	vehiculeStatus.clear();
}

ostream& operator<< (ostream& o, const Node& node) {
	o << "(" << *node.stationNumber << ",(";
	for (unsigned int i = 0; i < node.archs.size(); i++) {
		o << "(" << node.archs[i] << ")";
		if (i != node.archs.size() - 1) {
			o << ',';
		} 
	}
	o << "))";
	return o;
}