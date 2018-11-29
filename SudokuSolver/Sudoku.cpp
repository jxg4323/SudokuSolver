#include "solver.h"
#include <ctime>

void help() {
	fprintf(stderr,"usage: Sudoku [-hd] [-i INFILE] [-o OUTFILE]\n"
		"Options:\n"
		"-h\t Prints helpful message to stdout\n" 
		"-d\t Debug output\n"
		"-i INFILE Read puzzle from INFILE (Default puzzle2)"
		"-o OUTFILE Write solved puzzle to OUTFILE (Default stdout)");
}

int main(int argc, char** argv) {
	int result = EXIT_SUCCESS;
	string infile, outfile;


	return result;
}