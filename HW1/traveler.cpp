#pragma once
#include <iostream>
#include <string>
//Alpay Nacar
using namespace std;

struct traveler {
	int currX, currY, step;
	traveler* prev;
	traveler(int currX, int currY, traveler* prev = nullptr, int step=0) : currX(currX), currY(currY), prev(prev), step(step) {}
	string text(){
		return to_string(currX) + " " + to_string(currY);
	}
};






