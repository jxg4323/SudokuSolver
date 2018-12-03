#include "solver.h"
#include <ctime>
#include <boost/program_options.hpp>

void help() {
	fprintf(stderr,"usage: Sudoku [-hd] [-i INFILE] [-o OUTFILE]\n"
		"Options:\n"
		"-h\t Prints helpful message to stdout\n" 
		"-d\t Debug output\n"
		"-i INFILE Read puzzle from INFILE (Default 'stdin prompt'/puzzle)"
		"-o OUTFILE Write solved puzzle to OUTFILE (Default stdout)");
}

int main(int argc, char** argv) {
	bool debug = false;
	int result = EXIT_SUCCESS;
	string infile, outfile;
	Solver solve = Solver();

	namespace po = boost::program_options;
	po::options_description desc("Allowed Options");
	desc.add_options()
		("help,h","Prints Helpful Message")
		("debug,d","Debug Output")
		("input,i","Provide Input puzzle File")
		("output,o","Provide Solution Output Location");
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		help();
		cout << "\n" << desc << "\n";
	}
	else if (vm.count("debug")) {
		debug = true;
		solve.setDebug(debug);
	}
	else if (vm.count("input")) {
		infile = vm["input"].as<string>();
		solve.setInputFile(infile);
	}
	else if (vm.count("output")) {
		outfile = vm["output"].as<string>();
		solve.setOutputFile(outfile);
	}

	/*ofstream output;
	Solver solver = Solver();
	string outFile = solver.getOutputName();

	double firstElapsedTime(0);

	output.open(outFile);


	solver.readPuzzle(&solver);

	cout << "First Solution:\n";
	clock_t begin = clock();
	solver.solve();
	clock_t end = clock();
	firstElapsedTime = double(end - begin) / CLOCKS_PER_SEC;
	cout << solver << "Time: " << firstElapsedTime << "\n";

	output.close();*/

	return result;
}