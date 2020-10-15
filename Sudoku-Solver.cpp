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
                if (row_input == "sample") { break; }  // Shortcut for testing
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





// Main Procedure

int main() {
    
    
    // We begin by asking the user to enter the puzzle entries.
    Puzzle R = get_puzzle_from_user();
    
    // The first thing we do after getting the puzzle is check that the entries do not already violate
    //   any rules (namely that there are no repeat numbers in any row, column, or house and that all
    //   unfilled cells have at least one available option).
//    if (R.check_for_obvious_problems()) {
//        
//    }
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
