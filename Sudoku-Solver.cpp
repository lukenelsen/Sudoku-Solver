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
    cout << "Enter your Sudoku puzzle below, row by row.\n"
    "For blank cells, enter the '.' character.\n"
    "Do not separate the entries.  (Example:  .3...27..)\n"
    "Press Enter when you are finished with a row.\n"  << endl;
    
    string board_input = "";
    string row_input;
    string allowable_characters = ".123456789";
    for (int i=1; i<10; i++) {
        while (true) {
            cout << "Row " << i << ":  ";
            cin >> row_input;
            bool valid_row = true;
            if (row_input.length() != 9) {
                cout << "   Oops!  You entered " << row_input.length() << " characters, not 9." << endl;
                valid_row = false;
            }
            else {
                for (const char entry : row_input) {
                    if (allowable_characters.find(entry) == string::npos) {
                        // If character not in ".123456789", then .find() returns .length()
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
    }
    
    return Puzzle(board_input);
}





// Main Procedure

int main() {
    //     // Input the puzzle; store as Puzzle object
    //     Puzzle P;
    //
    //     // Test if the input is valid
    //
    //
    //     // Prompt user for whether they want to search for multiple (non-unique)
    //     bool continue_search;
    //
    //     // Start solving!
    //     while (P.move_to_next_solution()) {
    //
    //     }
    Puzzle P("123456789456789123789123456234567891567891234891234567345678912678912345912345678");
    P.print_board();
    
    
    
    Puzzle R = get_puzzle_from_user();
    R.print_board();
    cout << R.solution_log << endl;
    
    return 0;
}










// Member Functions

void Cell::write(int entry) {
    this->value = entry;
    this->available = {};
}



Puzzle::Puzzle() {
    solution_log = "Board initialized as empty.\n";
    update_board_string();
}



Puzzle::Puzzle(string board_input) {
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            char entry = board_input[9*i+j];
            if (entry != '.') {
                board[i][j].write((int)entry-48);
            }
        }
    }
    update_board_string();
    solution_log = "Board initialized with the following entries:\n" + board_string;
}



void Puzzle::print_board() {
    cout << board_string;
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
