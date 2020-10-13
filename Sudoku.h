#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;


class Cell {
public:
    int value;
    list<int> available;
    Cell() {value = 0; available = {1,2,3,4,5,6,7,8,9};};  // 0 means an empty space
    Cell(int v) {value = v; available = {};};
    void write(int entry);
};

class Puzzle {
public:
    Cell board [9][9];
    Puzzle();
    Puzzle(string board_input);
    void print_board();
    void update_board_string();
    string board_string;
    string solution_log;
};




