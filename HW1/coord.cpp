#pragma once
#include <iostream>
//Alpay Nacar

struct coord {
    int x;
    int y;
    bool leftConnection;
    bool rightConnection;
    bool upConnection;
    bool downConnection;

    coord(int y=0, int x=0) : x(x), y(y) {
        leftConnection = rightConnection = upConnection = downConnection = false;
    }

    bool isUsed() {
        return leftConnection || rightConnection || upConnection || downConnection;
    }
};

