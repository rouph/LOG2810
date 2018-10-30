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
	void CreateGraph();
	void extractNodes(ifstream& file);
	void ExtractArchs(ifstream& file);
	void getShortestPath(int begining, int end);
	void affichagePlusCourChemin(Node* node);
private:
	void extractNodeInfo(string& line, int& number, bool& hasStation);
	string fileName;
	bool graphSet;
	vector<Node*> queue;
	vector<Node*> Nodes;
};

#endif