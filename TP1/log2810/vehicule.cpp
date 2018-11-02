#include "vehicule.h"


vehicule::vehicule(double pourc, int temps): pourcentage(pourc), time(temps) {

}

double vehicule::getPourcentage() {
	return pourcentage;
}
int vehicule::getTime() {
	return time;
}
void vehicule::updateTime(int status) {
	time = status;
}
std::vector<int*> vehicule::getWhereCharged() {
	return whereCharged;
}
void vehicule::addChargedStation(int* station) {
	whereCharged.push_back(station);
}

void vehicule::updatePourcentage(double status) {
	pourcentage = status;
}

void vehicule::reset() {
	pourcentage = 0;
	time = invalidDistance;
	whereCharged.clear();
}


string vehicule::getVehiculeType(){
	return vehiculeType;
}
void vehicule::setVehiculeType(string type){
	vehiculeType = type;
}