
#include "Program.h"
#include <iostream>
#include <string>
Program::Program() {}
void Program::StartProgram() {
	char option = 'e';
	while (option != menuOption::quit) {
		std::cout << " (a) Update map " << endl
			<< " (b) Determine shortest safest path" << endl
			<< " (c) Extract sub-graph " << endl
			<< " (d) Quit" << endl;
		cin >> option;
		option = tolower(option);
		if (option != menuOption::updateMap &&
			option != menuOption::shortestPath &&
			option != menuOption::subGraph &&
			option != menuOption::quit) {
			cout << option << " is not a valid option" << endl;
		}
		switch (option) {
		case menuOption::updateMap:
			updateMap();
			break;
		case menuOption::shortestPath:
			shortest();
			break;
		case menuOption::subGraph:
			subGraph();
			break;
		}
	}
}
void Program::updateMap() {
	string file;
	std::cout << "Enter the file name of your map" << endl;
	std::cin >> file;
	try {
		ourGraph.CreateGraph(file);
		ourGraph.displayGraph();
	}
	catch (string e) {
		std::cout << e << endl;
	}
}
void Program::shortest() {
	int start, finish, patientRisk;
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
		ourGraph.getShortestPath(start, finish, patientRisk);
	}
	catch (string e) {
		cout << e << endl;
	}
}
void Program::subGraph() {
	int start, vehiculeType, patientRisk;
	std::cout << "Select ac starting point" << endl;
	cin >> start;

	std::cout << "Enter the number of the chosen vehicule" << endl
		<< "1 : Ni-MH" << endl
		<< "2 : Li-ion" << endl;
	cin >> vehiculeType;

	std::cout << "Enter the patient's health risk " << endl
		<< " 1 : low risk " << endl
		<< " 2 : medium risk " << endl
		<< " 3 : high risk " << endl;
	cin >> patientRisk;
	try {
		ourGraph.sousGraph(start, vehiculeType, patientRisk);
	}
	catch (string e) {
		cout << e << endl;
	}
}
