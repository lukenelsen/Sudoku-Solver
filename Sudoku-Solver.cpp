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
                    || (row_input == "sample2") || (row_input == "sample3")
                    || (row_input == "sample4") || (row_input == "sample5")
                    || (row_input == "sample6")
                    || (row_input == "dots")) { break; }  // Shortcut for testing
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
            else if (row_input == "sample4") {  // Shortcut for testing
                board_input = "...26.7.168..7..9.19...45..82.1...4...46.29...5...3.28..93...74.4..5..367.3.18...";
                break;
            }
            else if (row_input == "dots") {  // Shortcut for testing
                board_input = ".................................................................................";
                break;
            }
            else if (row_input == "sample5") {  // Shortcut for testing
                board_input = "123456789456789123789123456214365897365978241978241635...........................";
                break;
            }
            else if (row_input == "sample6") {  // Shortcut for testing
                board_input = "123456789456789123789123456......................................................";
                break;
            }
        }
        
        // Now ask user to verify puzzle; if not, prompt user to re-enter.
        Puzzle P(board_input);
        cout << endl << "Here is the puzzle you entered:" << endl;
        cout << P.make_board_entry_string();
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
    Puzzle P = get_puzzle_from_user();
    cout << "Now analyzing your puzzle..." << endl;
    if (P.is_board_filled()) {
        cout << "Your puzzle has already been entirely filled!\nThere is nothing left to do with it." << endl;
        return 0;
    }
    
    // We automatically analyze the board to determine if it has 0, 1, or 2+ solutions.
    //   Our menu options will depend on which of these cases we are in.
    int count = P.count_solutions();
    if (count==0) {
        cout << "Your puzzle is impossible; there are no solutions." << endl;
        // impossible_menu();
    }
    else if (count==1) {
        cout << "Your puzzle has exactly one solution." << endl;
        // unique_menu();
    }
    else {
        if (count>1000) { cout << "Your puzzle has over one thousand solutions." << endl; }
        else {cout << "Your puzzle has exactly "+to_string(count)+" solutions." << endl; }
        // nonunique_menu();
    }
    
    // The first thing we do after getting the puzzle is check that the entries do not already violate
    //   any rules (namely that there are no repeat numbers in any row, column, or house and that all
    //   unfilled cells have at least one available option).
    if (P.check_for_obvious_problems()) {
        cout << "Uh-oh!  There are some problems with the puzzle board.\n";
        P.print_obvious_problems();
        return 0;
    }
    
    
    
    
    

    
    
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
        this->log_line = " Write value "+to_string(entry)+" to r"+to_string(row_coord+1)+"c"+to_string(col_coord+1);
    }
    else if (step_type == "remove") {
        this->log_line = " Remove possible value(s) from r"+to_string(row_coord+1)+"c"+to_string(col_coord+1)+": ";
        for (int option : available_removed) { this->log_line += " "+to_string(option); }
    }
    this->log_line += ".\n";
}



Step::Step(string step_type) {
    this->step_type = step_type;
}



Puzzle::Puzzle(string board_input) {
    Step step("Initialization");
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            char entry = board_input[9*i+j];
            if (entry != '.') {
                board[i][j].write((int)entry-48);
                StepUnit s("write",i,j,(int)entry-48,{1,2,3,4,5,6,7,8,9});
                step.stepunit_stack.push_back(s);
            }
        }
    }
    step.log_line = "User entered the following puzzle:\n"+make_board_entry_string();
    step_stack.push_back(step);
    update_available_options_all();
    init_step = step_stack.back();
}



void Puzzle::print_log() {
    int step_counter = 0;  // Step 0 will be initialization.
    for (Step step : step_stack) {
        cout << "Step "+to_string(step_counter)+":  "+step.step_type << endl;
        cout << "    "+step.log_line << endl;
        int stepunit_counter = 1;
        for (StepUnit s : step.stepunit_stack) {
            cout << "    Step "+to_string(step_counter)+"."+to_string(stepunit_counter)+":   ";
            cout << (stepunit_counter<10 ? " " : "");
            cout << s.log_line;
            stepunit_counter++;
        }
        step_counter++;
    }
}



string Puzzle::make_board_entry_string() {
    string board_string = "";
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
    return board_string;
}



string Puzzle::make_board_available_string() {
    list<string> string_stack;
    list<string>::iterator it;
    for (int i = 0; i<9; i++) {
        if (i%3==0) { string_stack.push_back(" X-----------------X-----------------X-----------------X\n"); }
        else { string_stack.push_back(" |-----+-----+-----|-----+-----+-----|-----+-----+-----|\n"); }
        string_stack.push_back(" |");
        string_stack.push_back(" |");
        string_stack.push_back(" |");
        it = string_stack.end();
        it--;
        it--;
        it--;
        for (int j=0; j<9; j++) {
            Cell * c = &board[i][j];
            if (c->value > 0) {
                *it += "("+to_string(c->value)+")  |";
                it++;
                *it += "     |";
                it++;
                *it += "     |";
            }
            else {
                list<int>::iterator a = c->available.begin();
                list<int>::iterator b = c->available.end();
                *it += " ";
                for (int k : {1,2,3}) { *it += (find(a,b,k) != b ? to_string(k) : " "); }
                *it += " |";
                *(++it) += " ";
                for (int k : {4,5,6}) { *it += (find(a,b,k) != b ? to_string(k) : " "); }
                *it += " |";
                *(++it) += " ";
                for (int k : {7,8,9}) { *it += (find(a,b,k) != b ? to_string(k) : " "); }
                *it += " |";
            }
            it--;
            it--;
        }
        *it += "\n";
        it++;
        *it += "\n";
        it++;
        *it += "\n";
        it++;
    }
    string_stack.push_back(" X-----------------X-----------------X-----------------X\n");
    string board_string = "";
    for (string s : string_stack) { board_string += s; }
    return board_string;
}



void Puzzle::update_available_options_all() {
    // For each cell, removes any of its currently available options which are found in the cell's
    //   row, column, or house.  (Does not add to available.)
    // Each cell's adjustment is its own StepUnit, which is added to the top Step in the step_stack.
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
                step_stack.back().stepunit_stack.push_back(s);
            }
        }
    }
}



bool Puzzle::check_for_obvious_problems() {
    string add_to_log = "";
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            Cell & c = board[i][j];
            if ((c.value == 0) && (c.available.size() == 0)) {
                return true;
            }
            else if (c.value > 0) {
                // Check row
                for (int k=j+1; k<9; k++) {
                    if (board[i][k].value == c.value) {
                        return true;
                    }
                }
                // Check column
                for (int k=i+1; k<9; k++) {
                    if (board[k][j].value == c.value) {
                        return true;
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
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}



void Puzzle::print_obvious_problems() {
    string add_to_log = "";
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            Cell & c = board[i][j];
            if ((c.value == 0) && (c.available.size() == 0)) {
                cout << "Problem found (No Options): The cell in r"+to_string(i+1)+"c"+to_string(j+1);
                cout << " is unfilled but has no available options.\n";
            }
            else if (c.value > 0) {
                // Check row
                for (int k=j+1; k<9; k++) {
                    if (board[i][k].value == c.value) {
                        cout << "Problem found (Row Repeat):  The cells in r"+to_string(i+1);
                        cout << "c"+to_string(j+1)+" and r"+to_string(i+1)+"c"+to_string(k+1);
                        cout << " both have a "+to_string(c.value)+".\n";
                    }
                }
                // Check column
                for (int k=i+1; k<9; k++) {
                    if (board[k][j].value == c.value) {
                        cout << "Problem found (Column Repeat):  The cells in r"+to_string(i+1);
                        cout << "c"+to_string(j+1)+" and r"+to_string(k+1)+"c"+to_string(j+1);
                        cout << " both have a "+to_string(c.value)+".\n";
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
                            cout << "Problem found (House Repeat):  The cells in r"+to_string(i+1);
                            cout << "c"+to_string(j+1)+" and r"+to_string(3*(i/3)+k+1)+"c"+to_string(3*(j/3)+l+1);
                            cout << " both have a "+to_string(c.value)+".\n";
                        }
                    }
                }
            }
        }
    }
}



void Puzzle::apply_stepunit(StepUnit & stepunit) {
    Cell * cellptr = &board[stepunit.coords[0]][stepunit.coords[1]];
    cellptr->value = stepunit.entry;  // Primarily for "write" type, but changes nothing for "remove" type.
    list<int>::iterator it;
    it = (cellptr->available).begin();
    for (int num : stepunit.available_removed) { cellptr->available.remove(num); }
}
// Applying a StepUnit does not affect the stepunit_stack---StepUnits are added beforehand.
// However, undoing a StepUnit will always automatically remove it from stepunit_stack.



void Puzzle::unapply_last_stepunit() {
    StepUnit & stepunit = step_stack.back().stepunit_stack.back();
    Cell * cellptr = &board[stepunit.coords[0]][stepunit.coords[1]];
    if (stepunit.step_type == "write") { cellptr->value = 0; }
    list<int>::iterator it;
    it = (cellptr->available).begin();
    for (int num : stepunit.available_removed) {
        while (it != (cellptr->available).end() && *it<num) { it++; }
        (cellptr->available).insert(it, num);
    }
    step_stack.back().stepunit_stack.pop_back();
}



void Puzzle::apply_step(Step & step) {
    for (StepUnit stepunit : step.stepunit_stack) { apply_stepunit(stepunit); }
    step_stack.push_back(step);
}



void Puzzle::unapply_last_step() {
    while (step_stack.back().stepunit_stack.size() > 0) { unapply_last_stepunit(); }
    step_stack.pop_back();
}



void Puzzle::make_guess(int row, int col) {
    int guess = board[row][col].available.front();
    StepUnit stepunit("write", row, col, guess, board[row][col].available);
    Step step("Make Guess");
    step.log_line = "Try writing "+to_string(guess)+" to r"+to_string(row+1)+"c"+to_string(col+1)+".";
    step.stepunit_stack.push_back(stepunit);
    apply_step(step);
}



vector<int> Puzzle::choose_guess_cell() {
    //Current choice scheme:  cell with the least row, then least column, which does not have an entry.
    int i,j;
    for (int k=0; k<81; k++) {
        if (board[k/9][k%9].value == 0) {
            i = k/9;
            j = k%9;
            break;
        }
    }
    vector<int> coords = {i,j};
    return {i,j};
}



bool Puzzle::is_board_filled() {
    for (int k=0; k<81; k++) { if (board[k/9][k%9].value == 0) { return false; } }
    return true;
}



bool Puzzle::bump_last_guess() {
    // Go back to last guess
    while (step_stack.back().step_type != "Make Guess") {
        unapply_last_step();
        // We might not have a previous guess to go back to.
        if (step_stack.size() == 0) { return false; }
    }
    
    // Record the last guess
    int failed_guess = step_stack.back().stepunit_stack.front().entry;
    int row = step_stack.back().stepunit_stack.front().coords[0];
    int col = step_stack.back().stepunit_stack.front().coords[1];
    
    // Undo the last guess and also eliminate that value from available options
    unapply_last_step();
    Step incorrect_guess("Incorrect Guess");
    incorrect_guess.log_line = "Writing "+to_string(failed_guess)+" to r"+to_string(row+1)+"c"+to_string(col+1)+
                                " resulted in a failed detour.";
    StepUnit remove_guess("remove", row, col, 0, {failed_guess});
    incorrect_guess.stepunit_stack.push_back(remove_guess);
    apply_step(incorrect_guess);
    
    return true;
}



bool Puzzle::move_to_next_solution() {
    // If the user-defined puzzle has multiple solutions, then the board might currently be filled.
    // In this case, then we need to backtrack and increment one step before starting.
    if (is_board_filled() && !bump_last_guess()) { return false; }
    
    // Now search for the next solution.
    while (true) {
        // First, see if the current board is clearly unsolvable.
        // If so, backtrack through guessed cells with no more available options.
        while (check_for_obvious_problems()) {
            // For the most recent guessed cell, guess the next available option.
            // If we've backtracked all the way to initialization, we should close out the search.
            if (!bump_last_guess()) { return false; }
        }
        
        // At this point in the loop we are ready to move forward and make our next guess!
        vector<int> coords = choose_guess_cell();
        make_guess(coords[0],coords[1]);
        update_available_options_all();
        
        // Lastly, check to see if the board is now filled---if so, we've arrived at our next solution!
        if (is_board_filled()) { return true; }
    }
}



void Puzzle::reset_to_initialized() {
    while (step_stack.size() > 1) { unapply_last_step(); }  // If we are steps into the puzzle
    if (step_stack.size() < 1) { apply_step(init_step); }  // If the initial step was undone
}



int Puzzle::count_solutions() {
    int solution_count = 0;
    while (move_to_next_solution()) {
        solution_count++;
        if (solution_count > 1000) break;
    }
    reset_to_initialized();
    return solution_count;
}





