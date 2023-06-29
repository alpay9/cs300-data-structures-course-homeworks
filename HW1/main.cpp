#include <iostream>
#include <vector>
#include "Maze.h"
#include "Stack.h"
#include "coord.cpp"
//Alpay Nacar
using namespace std;



int main() {
	int num_of_mazes, rowSize, colSize;
	cout << "Enter the number of mazes: ";
	cin >> num_of_mazes;
	cout << "Enter the number of rows and columns (M and N): ";
	cin >> rowSize >> colSize;

	vector<Maze*> mazes;
	for (int i = 0; i < num_of_mazes; i++) {
		mazes.push_back(new Maze(rowSize, colSize, i+1));
	}
	cout << endl;

	int mazeID, entryX, entryY, exitX, exitY;
	cout << "All mazes are generated." << endl << endl
		<< "Enter a maze ID between 1 to " << num_of_mazes << " inclusive to find a path: ";
	cin >> mazeID;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> entryX >> entryY;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> exitX >> exitY;
	string iFilename = "maze_" + to_string(mazeID) + ".txt";
	string oFilename = "maze_" + to_string(mazeID) + "_path_" + to_string(entryX) + "_" + to_string(entryY) + "_" + to_string(exitX) + "_" + to_string(exitY) + ".txt";
	ofstream oFile(oFilename);

	mazes[mazeID - 1]->findPath(entryX, entryY, exitX, exitY, oFile);

	return 0;
}


