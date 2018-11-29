#include "Cell.h"
/// DEFAULT CONSTRUCTOR
Cell::Cell() {
	// don't have to free array the vector class handles it
	array = vector<int>(STANDARD_SIZE,CELL_DEF_VAL);
}

/// ACCESSORS
/*
* Retrieves the location of the value given in the vector which
* represents the Cell.
*/
int Cell::getLoc(int value) {
	return (find(array.begin(), array.end(), value) - array.begin());
}
/*
 * Returns a location of the first blank space found,
 * if none are found the return a -1.
 */
int Cell::getBlank() {
	for (int i = 0; i < STANDARD_SIZE; i++) {
		if ((this->array)[i] == BLANK_SPACE) 
			return i;
	}
	return EXIT_FAILED;
}
/*
 * Return the number in the given location of the 
 * calling Cell object.
 */
int Cell::getNum(int loc) {
	return (this->array)[loc];
}

/// MUTATORS
/*
 * Sets a location in the cell to a blank space, if
 * the given location isn't within the bounds then 
 * return -1 for failure, 0 for success.
 */
int Cell::setBlank(int loc) {
	if (loc < 0 || loc >= STANDARD_SIZE)
		return -1;
	(this->array)[loc] = BLANK_SPACE;
	return 0;
}
/*
 * Check the last value in the vector and if the 
 * value is still the default then the vector isn't
 * full and returns false, otherwise return true.
 */
bool Cell::isFull() {
	return (this->array[ARRAY_END] == CELL_DEF_VAL);
}
/*
* Add the given value to the corresponding cell's array
* at the first most available location.
*/
void Cell::addNum(int value) {
	for (int i = 0; i < STANDARD_SIZE; i++) {
		if (this->array[i] == CELL_DEF_VAL) {
			this->array[i] = value;
			return;
		}
	}
}
/*
* Add a number to the corresponding cell based on location.
*/
void Cell::addNum(int loc, int value) {
	(this->array)[loc] = value;
}

/// FORMATTERS
/*
 * return a string version of the cell in linear format to
 * be formatted down the pipeline.
 *
 * Formats the integer vector so that every three digits there
 * is a pipe 
 *		ex: 
 *			 1 2 3 | 4 5 6 | 7 8 9 |
 */
string Cell::format() {
	string result;
	int c(0);
	vector<int>::iterator it; // iterator for a vecotr of ints
	for (it = this->array.begin(); it != this->array.end(); it++,c++) {
		if (c % 3 == 0 && c > 0) {
			result += "|";
		}
		result += to_string(*it) + " ";
	}
	return result += "|";
}

/// LOGIC FUNCTIONS
/*
 * Based on a number given check to see if the cell
 * contains the number.
 */
bool Cell::checkCell(int value) {
	for (int i = 0; i < STANDARD_SIZE; i++) {
		if (array[i] == value)
			return true;
	}
	return false;
}
/*
 * Checks the associated cells array at the given location for
 * a blank space.
 * Return true if the space is empty and false otherwise
 */
bool Cell::checkLoc(int loc) {
	if ((this->array)[loc] == BLANK_SPACE)
		return true;
	else
		return false;
}
/*
 * Based on the location of a particular value in the Cell, retrieve
 * all values in the corresponding row.
 *
 * Returns true when the given value is found in the row, and false
 * if the value is not found.
 */
bool Cell::checkRow(int location,int value) {
	int rStart = 0;
	bool result = false;
	if ((location >= 3) && (location <= 5))
		rStart = 3;
	else if ((location >= 6) && (location <= ARRAY_END))
		rStart = 6;
	for (int inc = 0; inc < GRID_DIM; inc++) {
		if ((this->array)[rStart + inc] == value)
			result = true;
	}
	return result;
}
/*
 * Based on the location of a particular value in the Cell, retrieve
 * all values in the corresponding column.
 *
 * Returns true when the given value is found in the row, and false
 * if the value is not found.
 */
bool Cell::checkCol(int location, int value) {
	int cStart(0);
	bool result = false;
	if ((location % GRID_DIM == 1))
		cStart = 1;
	else if ((location % GRID_DIM == 2))
		cStart = 2;
	for (int inc = 0; inc < STANDARD_SIZE; inc += 3) {
		if ((this->array)[cStart + inc] == value)
			result = true;
	}
	return result;
}
/*
 * If the cells have the same numerical layout then the cells are
 * equal and this operator will return true. Otherwise the operator
 * will return false.
 */
 bool Cell::operator==(const Cell& rhs)const {
	 int count = 0;
	 for (int i = 0; i < STANDARD_SIZE; i++) {
		 if (array[i] == rhs.array[i])
			 count++;
	 }
	 if (count == 9)
		 return true;
	 return false;
 }
 //bool Cell::operator<(const Cell &r) const
 //{
	//

	// return true;
 //}
 bool operator<(const Cell& lhs, const Cell& rhs)
 {
	 return true;
 }

