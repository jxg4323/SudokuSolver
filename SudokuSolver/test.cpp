#include "solver.h"
#include <ctime>

int main(int args, char** argv) {

	ofstream output;
	Solver solver = Solver();
	Solver solver2 = Solver();
	string outFile = solver.getOutputName();

	double firstElapsedTime(0);

	output.open(outFile);

	solver.readPuzzle(&solver);
	
	cout << "First Solution:\n";
	clock_t begin = clock();
	solver.solve();
	clock_t end = clock();
	firstElapsedTime = double(end - begin) / CLOCKS_PER_SEC;
	cout  << solver << "Time: " << firstElapsedTime << "\n";
	
	output.close();
}