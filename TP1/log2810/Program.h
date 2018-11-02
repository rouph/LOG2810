#ifndef  PROGRAM_H
#define PROGRAM_H
#include <vector>
#include"graph.h"
class Program {
public:
	Program();
	void StartProgram();
	void updateMap();
	void shortest();
	void subGraph();

private:
	graph ourGraph;
};

#endif
