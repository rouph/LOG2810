#ifndef  VEHICULE_H
#define VEHICULE_H
#include <vector>
class vehicule {
public:
	vehicule(double pourc = 100, int temps = 0);
	double getPourcentage();
	int getTime();
	void updateTime(int status);
	void updatePourcentage(double status);
	std::vector<int> getWhereCharged();
	void addChargedStation(int station);
private:
	double pourcentage;
	int time;
	std::vector< int> whereCharged;
};

#endif
