#include "graph.h"
#include <iostream>
#include <string>

int main()
{

	char option = 'e';
	int start = 0;
	int finish = 0;
	int vehicule = 0;
	int patientRisk = 0;
	string file = "centresLocaux1.txt";

	graph graphe;

	//INTERFACE
	while(option!= menuOption::quit){
		std::cout << " (a) Update map " << endl
			<< " (b) Determine shortest safest path" << endl
			<< " (c) Extract sub-graph " << endl
			<< " (d) Quit" << endl;
		cin >> option;
		if (option != menuOption::updateMap &&
			option != menuOption::shortestPath &&
			option != menuOption::subGraph &&
			option != menuOption::quit) {
			cout << option << " is not a valid option" << endl;
		}
		option = tolower(option);
		switch (option) {
		case menuOption::updateMap:
			std::cout << "Enter the file name of your map" << endl;
			cin >> file;
			try {
				graphe.CreateGraph(file);
				graphe.displayGraph();
			}
			catch (string e) {
				cout << e << endl;
			}
	
			// REINITIALISER B ET C
			break;
		case menuOption::shortestPath:
			std::cout << "Select a starting point" << endl;
			cin >> start;

			std::cout << "Select a destination " << endl;
			cin >> finish;

			std::cout << "Enter the patient's health risk " << endl
				<< " 1 : low risk " << endl
				<< " 2 : medium risk " << endl
				<< " 3 : high risk " << endl;
			cin >> patientRisk;
			try {
				graphe.getShortestPath(start, finish, patientRisk);
			}
			catch (string e) {
				cout << e << endl;
			}
			break;
		case menuOption::subGraph:
			std::cout << "Select ac starting point" << endl;
			cin >> start;

			std::cout << "Enter the number of the chosen vehicule" << endl
				<< "1 : Ni-MH" << endl
				<< "2 : Li-ion" << endl;
			cin >> vehicule;

			std::cout << "Enter the patient's health risk " << endl
				<< " 1 : low risk " << endl
				<< " 2 : medium risk " << endl
				<< " 3 : high risk " << endl;
			cin >> patientRisk;
			graphe.sousGraph(start, vehicule, patientRisk);
			break;
		}
	}
	return 0;
}