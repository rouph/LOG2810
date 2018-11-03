
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
			cout << option << " Is not a valid option." << endl;
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
	try {
		std::cout << "Select a starting point" << endl;
		cin >> start;
		if (cin.fail()) {
			string error("Enter a numeric value");
			throw error;
		}
		std::cout << "Select a destination " << endl;
		cin >> finish;
		if (cin.fail()) {
			string error("Enter a numeric value");
			throw error;
		}
	}
	catch (string e) {
		cin.clear();
		cin.ignore();
		cout << e << endl;
		return;
	}
	std::cout << "Enter the patient's health risk " << endl
		<< " 1 : low risk " << endl
		<< " 2 : medium risk " << endl
		<< " 3 : high risk " << endl;
	cin >> patientRisk;
	try{
	ourGraph.getShortestPath(start, finish, patientRisk);
	}
	catch (string e) {
		cout << e << endl;
	}

}
void Program::subGraph() {
	int start, vehiculeType, patientRisk;
	try {
		std::cout << "Select a starting point" << endl;
		cin >> start;
		if (cin.fail()) {
			string error("Enter a numeric value");
			throw error;
		}
		std::cout << "Enter the number of the chosen vehicule" << endl
			<< " 1 : Ni-MH" << endl
			<< " 2 : Li-ion" << endl;
		cin >> vehiculeType;
		if (cin.fail()) {
			string error("Enter a numeric value");
			throw error;
		}
		std::cout << "Enter the patient's health risk " << endl
			<< " 1 : low risk " << endl
			<< " 2 : medium risk " << endl
			<< " 3 : high risk " << endl;
		cin >> patientRisk;
		if (cin.fail()) {
			string error("Enter a numeric value");
			throw error;
		}
	}
	catch (string e) {
		cin.clear();
		cin.ignore();
		cout << e << endl;
		return;
	}
	try {
		ourGraph.subGraph(start, vehiculeType, patientRisk);
	}
	catch (string e) {
		cout << e << endl;
	}
}
