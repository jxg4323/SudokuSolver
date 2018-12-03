#include "solver.h"
#include <ctime>
#include <boost/program_options.hpp>

int main(int argc, char** argv) {
	bool debug = false;
	int result = EXIT_SUCCESS;
	ofstream output;
	double firstElapsedTime(0);
	string infile, outfile;
	Solver solve = Solver();

	namespace po = boost::program_options;
	po::options_description desc("Allowed Options");
	desc.add_options()
		("help,h","Prints Helpful Message")
		("debug,d","Debug Output")
		("input,i",po::value<string>()->default_value("puzzle2"),"Provide Input puzzle File")
		("output,o",po::value<string>()->default_value(""),"Provide Solution Output Location");
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
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
		output.open(outfile);
	}

	solve.readPuzzle(&solve);

	cout << "Solution:\n";
	clock_t begin = clock();
	solve.solve();
	clock_t end = clock();
	firstElapsedTime = double(end - begin) / CLOCKS_PER_SEC;
	// if output file specified then output to it
	if (outfile != "") {
		output << solve << "Time: " << firstElapsedTime << "\n";
		output.close();
	}
	else // otherwise use stdout
		cout << solve << "Time: " << firstElapsedTime << "\n";

	return result;
}