#include "vehicule.h"


vehicule::vehicule(double pourc, int temps): Percentage(pourc), time(temps) {

}
vehicule::~vehicule() {
}

double vehicule::getPercentage() {
	return Percentage;
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

void vehicule::updatePercentage(double status) {
	Percentage = status;
}

void vehicule::reset() {
	Percentage = 0;
	time = invalidDistance;
	whereCharged.clear();
}
