#include "graph.h"
#include <iostream>
#include <string>

int main()
{

	char option = 'e';
	int start = 0;
	int finish = 0;
	string vehicule = "Ni-MH";
	string patientRisk = "---";
	string file = "centresLocaux1.txt";

	graph test;

	test.CreateGraph();
	//test.getShortestPath(1, 3);
	//test.getShortestPath(1, 2);
	//test.getShortestPath(3, 5);
	std::cout << endl;
	test.getShortestPath(1, 7);
	std::cout << endl;
	test.getShortestPath(3, 1);
	std::cout << endl;
	test.getShortestPath(1, 3);
	std::cout << endl;
	test.getShortestPath(7, 1);
	std::cout << endl;
	//test.getShortestPath(1, 1);
	//std::cout << endl;
	



	//INTERFACE



	//std::cout << " (a) Update map " << endl
	//	<< " (b) Determine shortest safest path" << endl
	//	<< " (c) Extract sub-graph " << endl
	//	<< " (d) Quit" << endl;
	//cin >> option;

	//if (option == 'a' || option == 'A') {

	//	std::cout << "Enter the file name of your map" << endl;
	//	cin >> file;
	//	graph graphe;
	//	graphe.CreateGraph();
	//	// REINITIALISER B ET C
	//}

	//if (option == 'b' || option == 'B') {
	//	std::cout << "Select a starting point" << endl;
	//	cin >> start;

	//	std::cout << "Select a destination " << endl;
	//	cin >> finish;

	//	std::cout << "Enter the patient's health risk " << endl
	//		<< " 1 : low risk " << endl
	//		<< " 2 : medium risk " << endl
	//		<< " 3 : high risk " << endl;
	//	cin >> patientRisk;

	//	//AJOUTER FONCTION QUI CHERCHE LE PLUS COURT CHEMIN
	//}

	//if (option == 'c' || option == 'C') {
	//	std::cout << "Select a starting point" << endl;
	//	cin >> start;

	//	std::cout << "Enter the number of the chosen vehicule" << endl
	//		<< "1 : Ni-MH" << endl
	//		<< "2 : Li-ion" << endl;
	//	cin >> vehicule;

	//	std::cout << "Enter the patient's health risk " << endl
	//		<< " 1 : low risk " << endl
	//		<< " 2 : medium risk " << endl
	//		<< " 3 : high risk " << endl;
	//	cin >> patientRisk;

	//	//AJOUTER FONCTION QUI FAI LE SOUS GRAPHE
	//}


	//if (option == 'd' || option == 'D') {

	//}
	return 0;
}