#include "graph.h"
#include <iostream>
#include <string>

int main()
{

	char option = 'e';
	int start = 0;
	int finish = 0;
	string vehicule = "Ni-MH";
	int patientRisk = 0;
	string file = "centresLocaux1.txt";

	graph test;

	//INTERFACE
	while(option!='d'){
		std::cout << " (a) Update map " << endl
			<< " (b) Determine shortest safest path" << endl
			<< " (c) Extract sub-graph " << endl
			<< " (d) Quit" << endl;
		cin >> option;

		if (option == 'a' || option == 'A') {

			std::cout << "Enter the file name of your map" << endl;
			cin >> file;
			graph graphe;
			graphe.CreateGraph(file);
			graphe.displayGraph();
			// REINITIALISER B ET C
		}

		if (option == 'b' || option == 'B') {
			std::cout << "Select a starting point" << endl;
			cin >> start;

			std::cout << "Select a destination " << endl;
			cin >> finish;

			std::cout << "Enter the patient's health risk " << endl
				<< " 1 : low risk " << endl
				<< " 2 : medium risk " << endl
				<< " 3 : high risk " << endl;
			cin >> patientRisk;
			test.getShortestPath(start, finish, patientRisk);
			//AJOUTER FONCTION QUI CHERCHE LE PLUS COURT CHEMIN
		}

		if (option == 'c' || option == 'C') {
			std::cout << "Select a starting point" << endl;
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

			//AJOUTER FONCTION QUI FAI LE SOUS GRAPHE
		}

	}
	return 0;
}