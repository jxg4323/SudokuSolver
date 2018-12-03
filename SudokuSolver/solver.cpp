#include"solver.h"

Solver::Solver() {
	grid = vector<Cell>(STANDARD_SIZE);
	inputF = "puzzle1";
	outputF = inputF + "Solved";
}

// accessors
string Solver::getInputName() {
	return inputF;
}
string Solver::getOutputName() {
	return outputF;
}
// mutators
void Solver::setDebug(bool b) {
	DEBUG = b;
}
void Solver::setInputFile(string file) {
	inputF = file;
}
void Solver::setOutputFile(string file) {
	outputF = file;
}

// Member Functions
/*
 * Alters the input operator so that when an istream object
 * (a.k.a inputFile) and a Solver object attempts to get
 * info from the file then this routine is used to fill the
 * puzzle array in the Solver Object
 * -- Because of the friend declaration the function will
 *	  have access to Solver's private members
 * -- Change the string number to int iff the string
		isn't a space and if it is then make the int a 0.
 */
void Solver::readPuzzle(Solver* solver) {
	ifstream input(solver->inputF);
	string line;
	int r(0), c(0),gridCol(0),gridRow(0);
	while (getline(input, line)) {
		// Need to every third number check if the cell I am in is full and
		// if not then add to the cell, if the cell is full move to the next
		// one 
		// The following if ladder checks when the puzzle rows are within a 
		// cell row then maintain the column count within the corresponding
		// cell row otherwise increase the column level to the next cell row
		if ((r% GRID_DIM == 0) && r > 0)
			gridCol++; // jump to next cell row
		else if( r % GRID_DIM > 0)
			gridCol -= 2; // stay in the same cell row

		for (unsigned int i = 0; i < line.size(); i++) {
			if (isdigit(line[i])) {
				// move to the next cell when the third number is found or if the current cell is full
				if (((c % GRID_DIM) == 0 && c > 0) || !(solver->grid[gridCol].isFull()))
					gridCol++;
				solver->grid[gridCol].addNum(atoi(&line[i]));
				c++;
			}
		}
		c = 0;
		r++;
	}
	input.close();
}
/*
* For each of the 9 columns I can get the 1st,2nd,3rd
* rows from the respective cells three at a time.
* Grab three cells strings formatted and then based on
* the format print the nth row on each cell and when that
* row # reaches three get the next three cells.
 * -- Because of the friend declaration the function will
 *	  have access to Solver's private members
 */
// TODO: PRETTY PRINT
ostream& operator << (ostream& out, Solver& obj) {
	int gridCol(0), gridRow(0);
	cout << " ------- ------- ------- \n";
	for (int i = 0; i < STANDARD_SIZE; i+=3) {
		Cell one, two, thr;
		string s, t, u,stok,ttok,utok;
		one = obj.grid[i];
		two = obj.grid[i + 1];
		thr = obj.grid[i + 2];
		s = one.format();
		t = two.format();
		u = thr.format();
		//print
		for (int j = 0; j < GRID_DIM; j++) {
			stok = s.substr(0,s.find(CELL_DELIMITER));
			ttok = t.substr(0,t.find(CELL_DELIMITER));
			utok = u.substr(0,u.find(CELL_DELIMITER));
			cout << "| " << stok << "| " << ttok << "| " << utok << "|" << "\n";
			s.erase(0, (s.find(CELL_DELIMITER)+1));
			t.erase(0, (t.find(CELL_DELIMITER)+1));
			u.erase(0, (u.find(CELL_DELIMITER)+1));
		}
		cout << " ------- ------- ------- \n";
	}
	
	return out;
}
/*
 * In order to solve the puzzle you have to take a position
 * to start it can be any position and look down the row
 * both horizontal and vertical to make sure no numbers in
 * the row match your guess and if they do then pick a
 * different number, then move to the next open cell. Continue
 * this process until you reach a point when you have either
 * solved the puzzle or the available squares to be filled
 * can only be filled with numbers that have already been
 * used. At that point back track to last best space and try
 * a different number.
 *
 * The difficult part will be the intuitive check, because
 * when I solve a puzzle myself I select random numbers
 * and a random spot on the puzzle and then check that space
 * if my number fails then I run through the rest and if
 * those fail then I pick another random spot or based on
 * what I have seen so far I moved to a spot with an
 * educated guess.
 *
 * When I solved if my first random intuitive check turns
 * out bad then I check another random number and continue
 * with that same number until I get stuck at which point
 * i move onto another number.
 *
 * Return:
 *	-> 0 if the solution was found
 *	-> 1 if the solution wasn't found
 */
bool Solver::solve() {
	int cellNum(0), loc(0);
	
	// puzzle is finished
	if (checkGrid(cellNum, loc)) {
		return true;
	}
	// change to intuitively pick most likely number
	for (int i = 1; i <= STANDARD_SIZE; i++) {
		if (isSafe(cellNum,loc, i)) {
			grid[cellNum].addNum(loc, i);
			if (solve()) {
				return true;
			}
			// for backtracking purposes, if bad solution is found then
			// undo all numbers put in
			grid[cellNum].setBlank(loc);
		}
	}

	return false;
}

// Eventually change to just checking the grid and then randomnly assign
// a blank space to row,col
bool Solver::checkGrid(int &cellNum,int &loc) {
	for (cellNum = 0; cellNum < STANDARD_SIZE; cellNum+=1) {
		loc = grid[cellNum].getBlank();
		if (loc == EXIT_FAILED)
			continue;
		else
			return false;
	}
	return true;
}

/*
 * Check if the square has a number in it already and if 
 * not, then given the value check to see if that value
 * is safe to put in the square.
 *
 * @param int cellNum -> Cell to check
 * @param int loc -> location of a potential value 
 * @param int value -> value to check
 * 
 * Return true if the square is empty and safe and return
 * false if the value given is not safe for that locaiton.
 */
bool Solver::isSafe(int cellNum,int loc, int value) {
	// Check cell,row, and column for the value and check that the location isn't blank
	return (!(grid[cellNum].checkCell(value))&&!(checkRow(cellNum,loc,value))&&!(checkCol(cellNum,loc,value))&&(grid[cellNum].checkLoc(loc)));
}

/*
 * Given the cell number the value is in, based on the 
 * location of the number in the cell calculate the 
 * row that the value is in and compare to adajacent cells
 * and any values in the current cell. Therefore this 
 * function assumes the value has not been placed before
 * calling the function.
 *
 * @param int cellNum -> Cell location in the puzzle
 * @param int value -> value
 * Return true if the value is found and false otherwise.
 */
bool Solver::checkRow(int cellNum,int location, int value) {
	bool result = false;
	int rStart(0),count(0);
	if ((cellNum >= 3) && (cellNum <= 5)) // middle row
		rStart = 3;
	else if ((cellNum >= 6) && (cellNum <= ARRAY_END)) // last row
		rStart = 6;
	for (int inc = 0; inc < 3; inc++) {
		// row doesn't have the value
		if ((grid[rStart + inc]).checkRow(location,value) == true)
			count++;
	}
	// The given value was found in the row
	if (count > 0)
		result = true;
	return result;
}
/*
* Given a particular integer from 0-  check that integer
* against all other integers in the col given.
*
* Return true if the col is safe for the integer given
* and false otherwise.
*/
bool Solver::checkCol(int cellNum,int location, int value) {
	bool result = false;
	int cStart(0), count(0);
	if ((cellNum % GRID_DIM == 1)) // middle column
		cStart = 1;
	else if ((cellNum % GRID_DIM == 2)) // last column
		cStart = 2;
	for (int inc = 0; inc < STANDARD_SIZE; inc += 3) {
		if ((grid[cStart + inc]).checkCol(location, value) == true)
			count++;
	}
	// The given value was found in the column
	if (count > 0)
		result = true;
	return result;
}