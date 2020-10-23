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


class StepUnit {
public:
    string step_type;  // Either "write" or "remove"
    int coords [2];
    int entry;
    list<int> available_removed;
    StepUnit(string step_type, int row_coord, int col_coord, int entry, list<int> available_removed);
    string log_line;
};

class Puzzle {
public:
    Cell board [9][9];
    Puzzle();
    Puzzle(string board_input);
    void print_log();
    string make_board_entry_string();
    string make_board_available_string();
    void update_available_options_all();
    list<string> log_stack;
    bool check_for_obvious_problems();
    vector<StepUnit> step_stack;
    void apply_stepunit(StepUnit & stepunit);
    void unapply_stepunit(StepUnit & stepunit);
//    void apply_step(list<StepUnit> & step);
//    void unapply_step(list<StepUnit> & step);
//    void step_back();
//    void step_forward();
//    void solution_back();
//    void solution_forward();
};




