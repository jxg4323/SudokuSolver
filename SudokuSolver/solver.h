#pragma once
#ifndef Solver_h
#define Solver_h
#include<stdio.h>
#include<string>
#include<iostream>
#include<stdlib.h>
#include<map>
#include<algorithm>
#include<fstream>
#include"Cell.h"
/// CONSTANTS
#define BASE_ALLOC 4
#define FREQ_START 1
const string CELL_DELIMITER = "|";
using namespace std;
class Solver {
private:
	vector<Cell> grid;
	string inputF, outputF;
public:
	bool DEBUG = false;
	Solver();
	string getInputName();
	string getOutputName();
	void setInputFile(string);
	void setOutputFile(string);
	void setDebug(bool);
	void readPuzzle(Solver*);
	friend ostream& operator << (ostream& out, Solver& obj);
	bool solve();
	bool isSafe(int,int,int);
	bool checkRow(int,int,int);
	bool checkCol(int,int,int);
	bool checkGrid(int &r,int &c);
};
#endif // ! Solver_h