//
//  main.cpp
//  Sudoku-Solver
//
//  Created by Luke Nelsen on 10/12/20.
//  Copyright © 2020 Luke Nelsen. All rights reserved.
//

#include "Sudoku.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;




// Helper Functions

Puzzle get_puzzle_from_user() {
    while (true) {  // Function exits when user enters puzzle and verifies correctness.
        
        // First, get entries from user row-by-row.
        
        cout << "Enter your Sudoku puzzle below, row by row.\n"
        "For blank cells, enter the '.' character.\n"
        "Do not separate the entries.  (Example:  .3...27..)\n"
        "Press Enter when you are finished with a row.\n"  << endl;
        
        string board_input = "";
        string row_input;
        string allowable_characters = ".123456789";
        for (int i=1; i<10; i++) {
            while (true) {  // Break from this loop when row has been entered in correct format.
                cout << "Row " << i << ":  ";
                cin >> row_input;
                if ((row_input == "sample") || (row_input == "sample1")
                    || (row_input == "sample2") || (row_input == "sample3")) { break; }  // Shortcut for testing
                bool valid_row = true;
                if (row_input.length() != 9) {
                    cout << "   Oops!  You entered " << row_input.length() << " characters, not 9." << endl;
                    valid_row = false;
                }
                else {
                    for (const char entry : row_input) {
                        if (allowable_characters.find(entry) == string::npos) {
                            // If character is not in string, then .find() returns std::string::npos
                            valid_row = false;
                            cout << "   Oops!  Invalid character (" << entry << ").  Try again, please." << endl;
                        }
                    }
                }
                if (valid_row) {
                    board_input += row_input;
                    break;
                }
                else {
                    cout << "   Try again, please."  << endl;
                }
            }
            if (row_input == "sample") {  // Shortcut for testing
                board_input = "123456789456789123789123456234567891567891234891234567345678912678912345912345678";
                break;
            }
            else if (row_input == "sample1") {  // Shortcut for testing
                board_input = ".3...27..123456.89...............................................................";
                break;
            }
            else if (row_input == "sample2") {  // Shortcut for testing
                board_input = "555......55.......5..............................................................";
                break;
            }
            else if (row_input == "sample3") {  // Shortcut for testing
                board_input = ".123456789.......................................................................";
                break;
            }
        }
        
        // Now ask user to verify puzzle; if not, prompt user to re-enter.
        Puzzle P(board_input);
        cout << endl << "Here is the puzzle you entered:" << endl;
        P.print_board();
        cout << endl << "Is this correct?  (y/n)" << endl;
        while (true) {  // Function exits for 'y'; loop breaks for 'n'; loop continues otherwise.
            string user_verify_input;
            cin >> user_verify_input;
            if (tolower(user_verify_input[0]) == 'y') {
                cout << endl << "Great!  Your puzzle's information has been entered." << endl;
                return P;
            }
            else if (tolower(user_verify_input[0]) == 'n') {
                cout << endl << "Okay, we'll have you re-enter the information for the puzzle." << endl;
                break;
            }
            else {
                cout << "Oops!  The program could not interpret your answer's format.\n"
                        "  An answer beginning with 'y' or 'Y' is interpreted as yes;\n"
                        "  an answer beginning with 'n' or 'N' is interpreted as no.\n"
                        "  Is the puzzle displayed above correct?" << endl;
            }
        }
    }
}



void test() {
    Puzzle P("123456789........................................................................");
    P.print_log();
    StepUnit stepunit("remove", 2, 1, 0, {7});
    P.apply_stepunit(stepunit);
    P.print_log();
}





// Main Procedure

int main() {
    
    test();
    
    
    // We begin by asking the user to enter the puzzle entries.
    
    Puzzle P = get_puzzle_from_user();
    P.update_available_options_all();
    P.print_log();
    
    
    // The first thing we do after getting the puzzle is check that the entries do not already violate
    //   any rules (namely that there are no repeat numbers in any row, column, or house and that all
    //   unfilled cells have at least one available option).
    
    if (P.check_for_obvious_problems()) {
        cout << "Uh-oh!  There are some problems with the puzzle board.\n";
        return 0;
    }
    
    
    // We will also automatically analyze the board to determine if it has 0, 1, or 2+ solutions.
    //   Our menu options will depend on which of these cases we are in.
    
    
    
    // If the puzzle has not already broken rules, then prompt the user for what information they want.
    // (Desired) Options:
    //      find a solution (if it exists);
    //      find all solutions (published puzzles are supposed to have unique solutions);
    //      find next step which can be deduced (if one can given the program's tools);
    //      write a new value in a cell or remove options from a cell's list of available numbers;
    //      see a puzzle's log of steps (automated or user-entered);
    //      step back (undo previous action);
    //      check if a particular tool applies to the current puzzle state.

    
    
    return 0;
}










// Member Functions

void Cell::write(int entry) {
    this->value = entry;
    this->available = {};
}



StepUnit::StepUnit(string step_type, int row_coord, int col_coord, int entry, list<int> available_removed) {
    if (step_type != "write" && step_type != "remove") {cout << "WARNING:  Invalid step type for StepUnit.";}
    this->step_type = step_type;
    this->coords[0] = row_coord;  // (coords values are 0-indexed, but
    this->coords[1] = col_coord;  // log_line prints 1-indexed for user.)
    this->entry = entry;  // should be 0 if step_type is "remove"
    this->available_removed = available_removed; // should be all of Cell.available if step_type is "write"
    if (step_type == "write") {
        this->log_line = "   Write value "+to_string(entry)+" to r"+to_string(row_coord+1)+"c"+to_string(col_coord+1);
    }
    else if (step_type == "remove") {
        this->log_line = "   Remove possible value(s) from r"+to_string(row_coord+1)+"c"+to_string(col_coord+1)+": ";
        for (int option : available_removed) { this->log_line += " "+to_string(option); }
    }
    this->log_line += ".\n";
}



Puzzle::Puzzle() {
    log_stack = {"Board initialized as empty.\n"};
    update_board_string();
}



Puzzle::Puzzle(string board_input) {
    string add_to_log = "Board initialized:\n";
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            char entry = board_input[9*i+j];
            if (entry != '.') {
                board[i][j].write((int)entry-48);
                StepUnit s("write",i,j,(int)entry-48,{1,2,3,4,5,6,7,8,9});
                step_stack.push_back(s);
                add_to_log += s.log_line;
            }
        }
    }
    update_board_string();
    add_to_log += board_string;
    log_stack.push_back(add_to_log);
}



void Puzzle::print_board() {
    cout << board_string;
}



void Puzzle::print_log() {
    for (string s : log_stack) { cout << s; }
}



void Puzzle::update_board_string() {
    board_string = "";
    for (int i=0; i<9; i++) {
        if (i%3 == 0) {board_string += " -------------------------\n";}
        for (int j=0; j<9; j++) {
            if (j%3 == 0) {board_string +=  " |";}
            if (board[i][j].value > 0) {
                board_string +=  " " + to_string(board[i][j].value);
            }
            else {board_string +=  " .";}
        }
        board_string +=  " |\n";
    }
    board_string +=  " -------------------------\n";
}



void Puzzle::update_available_options_all() {
    // For each cell, removes any of its currently available options which are found in the cell's
    //   row, column, or house.  (Does not add to available.)
    string add_to_log = "Update available values affected by initialization:\n";
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            Cell & c = board[i][j];
            list<int> to_remove = {};
            for (int option : c.available) {  // If cell is already filled, then available is empty.
                bool removed = false;
                // Check row
                for (int k=0; k<9; k++) {
                    if (board[i][k].value == option) {
                        to_remove.push_back(option);
                        removed = true;
                        break;
                    }
                }
                if (removed) {continue;}
                // Check column
                for (int k=0; k<9; k++) {
                    if (board[k][j].value == option) {
                        to_remove.push_back(option);
                        removed = true;
                        break;
                    }
                }
                if (removed) {continue;}
                // Check house
                for (int k=0; k<3; k++) {
                    for (int l=0; l<3; l++) {
                        if (board[3*(i/3)+k][3*(j/3)+l].value == option) {
                            to_remove.push_back(option);
                            removed = true;
                            break;
                        }
                    }
                }
            }
            if (to_remove.size() > 0) {
                for (int option : to_remove) { c.available.remove(option); }
                StepUnit s("remove",i,j,0,{to_remove});
                step_stack.push_back(s);
                add_to_log += s.log_line;
            }
        }
    }
    log_stack.push_back(add_to_log);
}



bool Puzzle::check_for_obvious_problems() {
    string add_to_log = "";
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            Cell & c = board[i][j];
            if ((c.value == 0) && (c.available.size() == 0)) {
                add_to_log += "Problem found (No Options): The cell in R"+to_string(i+1)+"C"+to_string(j+1);
                add_to_log += " is unfilled but has no available options.\n";
            }
            else if (c.value > 0) {
                // Check row
                for (int k=j+1; k<9; k++) {
                    if (board[i][k].value == c.value) {
                        add_to_log += "Problem found (Row Repeat):  The cells in R"+to_string(i+1);
                        add_to_log += "C"+to_string(j+1)+" and R"+to_string(i+1)+"C"+to_string(k+1);
                        add_to_log += " both have a "+to_string(c.value)+".\n";
                    }
                }
                // Check column
                for (int k=i+1; k<9; k++) {
                    if (board[k][j].value == c.value) {
                        add_to_log += "Problem found (Column Repeat):  The cells in R"+to_string(i+1);
                        add_to_log += "C"+to_string(j+1)+" and R"+to_string(k+1)+"C"+to_string(j+1);
                        add_to_log += " both have a "+to_string(c.value)+".\n";
                    }
                }
                // Check house
                for (int k=0; k<3; k++) {
                    for (int l=0; l<3; l++) {
                        // The following check prevents comparing the same row, column, or previously inspected cell.
                        // The inequality 9*i+j >= 9*(3*(i/3)+k)+(3*(j/3)+l) means that the [i][j] cell is
                        // ahead of the [3*(i/3)+k][3*(j/3)+l] cell.
                        if ( (k==i) || (l==j) || ( 9*i+j >= 9*(3*(i/3)+k)+(3*(j/3)+l) ) ) { continue; }
                        if (board[3*(i/3)+k][3*(j/3)+l].value == c.value) {
                            add_to_log += "Problem found (House Repeat):  The cells in R"+to_string(i+1);
                            add_to_log += "C"+to_string(j+1)+" and R"+to_string(3*(i/3)+k+1)+"C"+to_string(3*(j/3)+l+1);
                            add_to_log += " both have a "+to_string(c.value)+".\n";
                        }
                    }
                }
            }
        }
    }
    log_stack.push_back(add_to_log);
    return (add_to_log == "" ? false : true);
}



void Puzzle::apply_stepunit(StepUnit & stepunit) {
    Cell * cellptr = &board[stepunit.coords[0]][stepunit.coords[1]];
    cellptr->value = stepunit.entry;  // Primarily for "write" type, but changes nothing for "remove" type.
    list<int>::iterator it;
    it = (cellptr->available).begin();
    for (int num : stepunit.available_removed) {
        while (it != (cellptr->available).end() && *it>num) { it++; }
        (cellptr->available).insert(it, num);
    }
    log_stack.push_back(stepunit.log_line);
}





