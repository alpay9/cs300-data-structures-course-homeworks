#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Stack.cpp"
#include "coord.cpp"
#include "traveler.cpp"
//Alpay Nacar

class Maze
{
public:
	Maze(int rowSz, int colSz, int mazeID);
	~Maze();
	bool isUsed(int row, int col);
	void addNextCell();
	void chooseRandomWall(int& x, int& y);

	void findPath(int from_row, int from_col, int to_row, int to_col, ofstream& oFile);
	void backtrack(Stack<coord>& stack, int prevX, int prevY, ofstream& oFile);

	void write_into(ListNode<coord>* ptr, ofstream& file);
	string text(int x, int y);
private:
	Stack<coord> stack;
	vector<vector<coord> > mat;
	int rowSize;
	int colSize;
};

#include "Maze.cpp"