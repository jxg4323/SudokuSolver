#pragma once
#ifndef MazeSolver_h
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
class MazeSolver {
private:
	CoordQueue queue;
	int** maze;
	int** visisted;
	int colNum[4], rowNum[4];
	int r, c, pathNum;
	bool solved, solveable;
};

#endif // ! MazeSolver_h
