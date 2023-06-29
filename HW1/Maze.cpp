#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Maze.h"
#include "Stack.h"
#include "coord.cpp"
#include "traveler.cpp"
//Alpay Nacar


Maze::Maze(int rowSz, int colSz, int mazeID) : stack(), rowSize(rowSz), colSize(colSz) {
	for (int row = 0; row < rowSize; row++) {
		mat.push_back(vector<coord>());
		for (int col = 0; col < colSize; col++) {
			mat[row].push_back(coord(row, col));
		}
	}
	stack.push(mat[0][0]);
	for (int knockedDownWalls = 0; knockedDownWalls < rowSize * colSize - 1; knockedDownWalls++) {
		addNextCell();
		coord tmp = stack.top()->data;
	}
	string filename = "maze_" + to_string(mazeID) + ".txt";
	ofstream myFile(filename);
	myFile << to_string(rowSize) << " " << to_string(colSize) << endl;
	write_into(stack.top(), myFile);
	myFile.close();
}

Maze::~Maze() {}

void Maze::write_into(ListNode<coord>* ptr, ofstream& file) {
	if (ptr->next) write_into(ptr->next, file);
	file << text(ptr->data.x, ptr->data.y) << endl;
}

bool Maze::isUsed(int row, int col) {
	return mat[row][col].isUsed();
}

void Maze::addNextCell() {
	ListNode<coord>* ptr = stack.top();
	while (ptr) {
		int ptrX = ptr->data.x;
		int ptrY = ptr->data.y;
		chooseRandomWall(ptrX, ptrY);
		if (ptrX - 1 == ptr->data.x) {
			mat[ptrY][ptrX].leftConnection = true;
			mat[ptrY][ptrX - 1].rightConnection = true;
			stack.push(mat[ptrY][ptrX]);
			return;
		}
		else if (ptrX + 1 == ptr->data.x) {
			mat[ptrY][ptrX].rightConnection = true;
			mat[ptrY][ptrX + 1].leftConnection = true;
			stack.push(mat[ptrY][ptrX]);
			return;
		}
		else if (ptrY - 1 == ptr->data.y) {
			mat[ptrY][ptrX].downConnection = true;
			mat[ptrY - 1][ptrX].upConnection = true;
			stack.push(mat[ptrY][ptrX]);
			return;
		}
		else if (ptrY + 1 == ptr->data.y) {
			mat[ptrY][ptrX].upConnection = true;
			mat[ptrY + 1][ptrX].downConnection = true;
			stack.push(mat[ptrY][ptrX]);
			return;
		}
		else ptr = ptr->next;
	}
}

void Maze::chooseRandomWall(int& x, int& y) {
	bool canGoLeft, canGoRight, canGoUp, canGoDown;
	canGoLeft = canGoRight = canGoUp = canGoDown = false;
	int count = 0;
	if(x != 0 && !mat[y][x-1].isUsed()){ canGoLeft = true; count++; }
	if(x+1 != colSize && !mat[y][x+1].isUsed()) { canGoRight = true; count++; }
	if(y != 0 && !mat[y-1][x].isUsed()) { canGoDown = true; count++; }
	if(y+1 != rowSize && !mat[y+1][x].isUsed()) { canGoUp = true; count++; }
	if (!count) return;
	int rnd = rand() % count + 1;
	if (canGoLeft) {
		if (rnd == 1) {
			x--;
			return;
		}
	}
	else { rnd++; }
	if (canGoRight) {
		if (rnd == 2) {
			x++;
			return;
		}
	}
	else { rnd++; }
	if (canGoUp) {
		if (rnd == 3) {
			y++;
			return;
		}
	}
	else { rnd++; }
	if (canGoDown) {
		y--;
		return;
	}
}

void Maze::findPath(int from_row, int from_col, int to_col, int to_row, ofstream& oFile) {
	//find the path using stack
	Stack<coord> st;
	vector<vector<bool>> passed(rowSize, vector<bool>(colSize, false));
	st.push(mat[0][0]);
	for (int step = 0; step < rowSize * colSize; step++) {
		ListNode<coord>* ptr = st.top();
		while (ptr && !passed[ptr->data.y][ptr->data.x]) {
			coord& c = ptr->data;
			if (c.leftConnection && !passed[c.y][c.x-1]) {
				st.push(mat[c.y][c.x - 1]);
				if (c.x - 1 == to_col && c.y == to_row) break;
			}
			if (c.rightConnection && !passed[c.y][c.x + 1]) {
				st.push(mat[c.y][c.x+1]);
				if (c.x + 1 == to_col && c.y == to_row) break;
			}
			if (c.upConnection && !passed[c.y+1][c.x]) {
				st.push(mat[c.y+1][c.x]);
				if (c.x == to_col && c.y + 1 == to_row) break;
			}
			if (c.downConnection && !passed[c.y-1][c.x]) {
				st.push(mat[c.y-1][c.x]);
				if (c.x == to_col && c.y - 1 == to_row) break;
			}
			passed[c.y][c.x] = true;
			ptr = ptr->next;
		}
		if (st.top()->data.x == to_col && st.top()->data.y == to_row) break;
	}
	//write the path into output file
	backtrack(st, st.top()->data.x+1, st.top()->data.y, oFile);
}

void Maze::backtrack(Stack<coord>& st,int prevX, int prevY, ofstream& oFile) {
	while (st.top()) {
		if (
			(st.top()->data.x + 1 == prevX && st.top()->data.y == prevY) || //left
			(st.top()->data.x - 1 == prevX && st.top()->data.y == prevY) || //right
			(st.top()->data.x == prevX && st.top()->data.y + 1 == prevY) || //up
			(st.top()->data.x == prevX && st.top()->data.y - 1 == prevY) //down
			) break;
		st.pop();
	}
	if (st.top()) {
		int currX = st.top()->data.x;
		int currY = st.top()->data.y;
		st.pop();
		if (st.top()) { 
			backtrack(st, currX, currY, oFile); // recursion
		}
		oFile << to_string(currX) << " " << to_string(currY) << endl; // write curr cell
	}
}

string Maze::text(int x, int y) {
	string str = "x=" + to_string(x) + " y=" + to_string(y);
	str += " l="; //left
	if (!mat[y][x].leftConnection) str += to_string(1);
	else str += to_string(0);
	str += " r="; //right
	if (!mat[y][x].rightConnection) str += to_string(1);
	else str += to_string(0);
	str += " u="; //up
	if (!mat[y][x].upConnection) str += to_string(1);
	else str += to_string(0);
	str += " d="; //down
	if (!mat[y][x].downConnection) str += to_string(1);
	else str += to_string(0);
	return str;
}
