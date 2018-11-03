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
	~graph();
	void CreateGraph(string fileName);
	void extractNodes(ifstream& file);
	void ExtractArchs(ifstream& file);
	void setShortestPath(int beginning, int end, double PercentageNeeded);
	void affichageChemin(Node* node);
	void getShortestPath(int beginning, int end, int patientType);
	void displayGraph();
	void subGraph(int beginning, int vehiculeType, int PatientType);
	double determinePercentageNeeded(int vehiculeType, int PatientType);

private:
	void extractNodeInfo(string& line, int& number, bool& hasStation);
	bool graphSet;
	vector<Node*> queue;
	vector<Node*> Nodes;
};

#endif