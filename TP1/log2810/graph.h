#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include <set>
#include <vector>
#include "sommet.h"
#include "constante.h"
using namespace std;
class graph {

public:
	graph();
	void CreateGraph(string fileName);
	void extractNodes(ifstream& file);
	void ExtractArchs(ifstream& file);
	void setShortestPath(int begining, int end, double pourcentageNeeded);
	void affichageChemin(Node* node);
	void getShortestPath(int begining, int end, int patientType);
	void displayGraph();
	void sousGraph(int beginning, int end, double pourcentageNeeded);
	double determinePourcentageNeeded(int vehiculeType, int PatientType);

private:
	void extractNodeInfo(string& line, int& number, bool& hasStation);
	bool graphSet;
	vector<Node*> queue;
	vector<Node*> Nodes;
};

#endif