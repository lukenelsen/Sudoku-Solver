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





void Cell::write(int entry) {
    this->value = entry;
    this->available = {};
}



Puzzle::Puzzle() {
    solution_log = "";
}



Puzzle::Puzzle(string board_input) {
    solution_log = "Board initialized with the following entries:";
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            char entry = board_input[9*i+j];
            if (entry != '.') { board[i][j].write((int)entry-48); }
        }
    }
}



void Puzzle::print_board() {
    for (int i=0; i<9; i++) {
        if (i%3 == 0) {cout << " -------------------------" << endl;}
        for (int j=0; j<9; j++) {
            if (j%3 == 0) {cout << " |";}
            if (board[i][j].value > 0) {
                cout << " " << board[i][j].value;
            }
            else {cout << " .";}
        }
        cout << " |" << endl;
    }
    cout << " -------------------------" << endl;
}


//int main(int argc, const char * argv[]) {

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
    Puzzle P;
    P.print_board();
    
    cout << "Meow!" << endl << endl;
    
    Puzzle Q("123456789234567891345678912456789123567891234678912345789123456891234567912345678");
    Q.print_board();
    
    cout << 343 << endl << endl;
    
    cout << "Enter the Sudoku puzzle below, row by row.\n"
            "For blank cells, enter the '.' character.\n"
            "Do not separate the entries.  (Example:  .3...27..)\n"
            "Press Enter when you are finished with a row.\n"  << endl;
    
    string board_input = "";
    string row_input;
    for (int i=1; i<10; i++) {
        cout << "Row " << i << ":  ";
        cin >> row_input;
        board_input += row_input;
    }
    
    
    Puzzle R(board_input);
    R.print_board();
    
    return 0;
}




