#pragma once
#ifndef Cell_h
#define Cell_h
#include<stdio.h>
#include<string>
#include<iostream>
#include<vector>
/// CONSTANTS
#define STANDARD_SIZE 9
#define BLANK_SPACE 0
#define EXIT_FAILED -2
#define GRID_DIM 3
#define CELL_DEF_VAL -1
#define ARRAY_END 8
using namespace std;
class Cell {
private:
	vector<int> array;
public:
	Cell();
	void addNum(int);
	void addNum(int, int);
	int getNum(int);
	int getBlank();
	int setBlank(int);
	bool isFull();
	string format();
	int getLoc(int);
	bool checkCell(int);
	bool checkLoc(int);
	bool checkRow(int,int);
	bool checkCol(int,int);
	bool Cell::operator==(const Cell&)const;
};
	
#endif // | Cell_h
