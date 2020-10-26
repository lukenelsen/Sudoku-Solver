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



class Step {
public:
    string step_type;  // Options include "Initialize Board", "Make Guess", etc.
    vector<StepUnit> stepunit_stack;
    Step(string step_type);
    string log_line;
};



class Puzzle {
public:
    Cell board [9][9];
    Step init_step = Step("Initialization");
    vector<Step> step_stack;
    Puzzle(string board_input);
    void print_log();
    void print_log_terse();
    string make_board_entry_string();
    string make_board_available_string();
    void update_available_options_all();
    bool check_for_obvious_problems();
    void print_obvious_problems();
    bool check_for_none_available();
    void apply_stepunit(StepUnit & stepunit);
    void unapply_last_stepunit();
    void make_guess(int row, int col);
    vector<int> choose_guess_cell();
    bool bump_last_guess();
    bool move_to_next_solution();
    bool is_board_filled();
    void apply_step(Step & step);
    void unapply_last_step();
    void reset_to_initialized();
    int count_solutions();
};




