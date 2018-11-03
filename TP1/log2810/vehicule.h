#ifndef  VEHICULE_H
#define VEHICULE_H
#include <vector>
#include <string>
#include"constante.h"
using namespace std;
class vehicule {
public:
	vehicule(double pourc = 100, int temps = 0);
	~vehicule();
	double getPourcentage();
	int getTime();
	void updateTime(int status);
	void updatePourcentage(double status);
	std::vector<int*> getWhereCharged();
	void addChargedStation(int* station);
	void reset();
private:
	double pourcentage;
	string vehiculeType;
	int time;
	std::vector<int*> whereCharged;
};

#endif
