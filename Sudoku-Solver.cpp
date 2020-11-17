//
//  main.cpp
//  Sudoku-Solver
//
//  Created by Luke Nelsen beginning 10/12/20.
//  Last updated 11/17/20.
//  Copyright © 2020 Luke Nelsen. All rights reserved.
//

#include "Sudoku.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;




// Helper Functions

void wait_for_user() {
    cout << endl
    << "Enter any character when you are ready to return to the previous menu. ";
    string user_input;
    cin >> user_input;
    cout << endl << endl;
    return;
}



void menu_learn() {
    return;
}



void puzzle_expanded_view(Puzzle & P) {
    cout << P.make_board_available_string() << endl
         << "Enter any character when you are ready to return to the previous menu. ";
    string user_input;
    cin >> user_input;
    cout << endl << endl;
    return;
}



void learn_no_solutions(Puzzle & P) {
    return;
}



void view_log(Puzzle & P) { // Needs updated to add a pause!
    while (true) {
        cout << endl << "LOG MENU" << endl
        << "What would you like to do?" << endl
        << "(1) Show the shorter version of the log" << endl
        << "(2) Show the full version of the log" << endl
        << "[0] Return to the Puzzle Menu" << endl << endl;
        while (true) {
            cout << "Enter your choice: ";
            string menu_option;
            cin >> menu_option;
            cout << endl;
            if (menu_option.size()>1) {
                cout << "Oops!  Your response has more than one character.\n"
                "Simply type one of \"1\", \"2\", or \"0\" and hit Enter." << endl << endl;
                continue;
            }
            char const choice = menu_option[0];
            if (choice=='1') { P.print_log_terse(); break; }
            if (choice=='2') { P.print_log(); break; }
            else if (choice=='0') { return; }
            else {
                cout << "Oops!  Your entry was not a recognized option.\n"
                "Simply type one of \"1\", \"2\", or \"0\" and hit Enter." << endl << endl;
                continue;
            }
        }
        wait_for_user();
    }
    return;
}



void enter_step(Puzzle & P) {
    return;
}



void show_unique_solution(Puzzle P) {  // Copy the puzzle to not change current state for the user
    P.move_to_next_solution();
    cout << P.make_board_entry_string();
    wait_for_user();
    return;
}



void show_unique_next_step(Puzzle & P) {
    return;
}



void undo_last_step(Puzzle & P) {
    return;
}



void reset_puzzle(Puzzle & P) {
    return;
}



void show_nonunique_next_step(Puzzle & P) {
    return;
}



void show_nonunique_prev_solution(Puzzle & P) {
    return;
}



void find_spec_nonunique_solution(Puzzle & P) {
    return;
}



void menu_puzzle_impossible(Puzzle & P) {
    while (true) {
        cout << endl << "IMPOSSIBLE PUZZLE MENU" << endl << endl << P.make_board_entry_string()
        << endl << "The puzzle you entered (shown above) has no solutions." << endl
        << "What would you like to do?" << endl
        << "(1) See an expanded view of the puzzle board" << endl
        << "( ) Learn why there are no solutions [not yet available]" << endl
        << "[0] Leave this puzzle and return to the Main Menu" << endl << endl;
        while (true) {
            cout << "Enter your choice: ";
            string menu_option;
            cin >> menu_option;
            cout << endl;
            if (menu_option.size()>1) {
                cout << "Oops!  Your response has more than one character.\n"
                "Simply type one of \"1\", \"2\", or \"0\" and hit Enter." << endl << endl;
                continue;
            }
            char const choice = menu_option[0];
            if (choice=='1') { puzzle_expanded_view(P); break; }
            if (choice=='2') { learn_no_solutions(P); break; }
            else if (choice=='0') { return; }
            else {
                cout << "Oops!  Your entry was not a recognized option.\n"
                "Simply type one of \"1\", \"2\", or \"0\" and hit Enter." << endl << endl;
                continue;
            }
        }
    }
}



void menu_puzzle_unique(Puzzle & P) {
    while (true) {
        cout << endl << "PUZZLE MENU (UNIQUE SOLUTION)" << endl << endl << P.make_board_entry_string()
        << endl << "The current state of your puzzle is shown above." << endl
        << "What would you like to do?" << endl
        << "(1) See an expanded view of the puzzle board" << endl
        << "(2) View the log of steps made so far" << endl
        << "( ) Enter my own step toward solving the puzzle [not yet available]" << endl
        << "(4) Show me the solution" << endl
        << "( ) Show me a next step toward the solution [not yet available]" << endl
        << "( ) Undo the last step [not yet available]" << endl
        << "( ) Reset the puzzle to its initial entries [not yet available]" << endl
        << "[0] Leave this puzzle and return to the Main Menu" << endl << endl;
        while (true) {
            cout << "Enter your choice: ";
            string menu_option;
            cin >> menu_option;
            cout << endl;
            if (menu_option.size()>1) {
                cout << "Oops!  Your response has more than one character.\n"
                "Simply type an integer between 0 and 7 and hit Enter." << endl << endl;
                continue;
            }
            char const choice = menu_option[0];
            if (choice=='1') { puzzle_expanded_view(P); break; }
            if (choice=='2') { view_log(P); break; }
            if (choice=='3') { enter_step(P); break; }
            if (choice=='4') { show_unique_solution(P); break; }
            if (choice=='5') { show_unique_next_step(P); break; }
            if (choice=='6') { undo_last_step(P); break; }
            if (choice=='7') { reset_puzzle(P); break; }
            else if (choice=='0') { return; }
            else {
                cout << "Oops!  Your entry was not a recognized option.\n"
                "Simply type an integer between 0 and 7 and hit Enter." << endl << endl;
                continue;
            }
        }
    }
}



void menu_puzzle_nonunique(Puzzle & P, int num_original_solutions) {
    string orig = (num_original_solutions>1000 ? "over one thousand" : to_string(num_original_solutions));
    while (true) {
        Puzzle P_copy = P;
        int current_sols = P_copy.count_solutions();
        string current = (current_sols>1000 ? "over one thousand" : to_string(current_sols));
        cout << endl << "PUZZLE MENU (NON-UNIQUE SOLUTIONS)" << endl << endl << P.make_board_entry_string()
             << endl << "The original puzzle you entered has "+orig+" solutions.";
        if (P.is_board_filled()) { cout << "  One is shown above." << endl; }
        else { cout << "\nThe current state of your puzzle is shown above ("+current+" possible solutions)." << endl; }
        cout << "What would you like to do?" << endl
        << "(1) See an expanded view of the puzzle board" << endl
        << "(2) View the log of steps made so far" << endl
        << "( ) Enter my own step toward solving the puzzle [not yet available]" << endl
        << "(4) Show me the next solution from the current state" << endl
        << "( ) Show me a step toward the next solution [not yet available]" << endl
        << "( ) Undo the last step [not yet available]" << endl
        << "( ) Show me the previous solution from the current state [not yet available]" << endl
        << "( ) Reset the puzzle to its initial entries [not yet available]" << endl
        << "( ) Show me a specific solution to the puzzle [not yet available]" << endl
        << "[0] Leave this puzzle and return to the Main Menu" << endl << endl;
        while (true) {
            cout << "Enter your choice: ";
            string menu_option;
            cin >> menu_option;
            cout << endl;
            if (menu_option.size()>1) {
                cout << "Oops!  Your response has more than one character.\n"
                "Simply type an integer between 0 and 9 and hit Enter." << endl << endl;
                continue;
            }
            char const choice = menu_option[0];
            if (choice=='1') { puzzle_expanded_view(P); break; }
            if (choice=='2') { view_log(P); break; }
            if (choice=='3') { enter_step(P); break; }
            if (choice=='4') { P.move_to_next_solution(); break; }
            if (choice=='5') { show_nonunique_next_step(P); break; }
            if (choice=='6') { undo_last_step(P); break; }
            if (choice=='7') { show_nonunique_prev_solution(P); break; }
            if (choice=='8') { reset_puzzle(P); break; }
            if (choice=='9') { find_spec_nonunique_solution(P); break; }
            else if (choice=='0') { return; }
            else {
                cout << "Oops!  Your entry was not a recognized option.\n"
                "Simply type an integer between 0 and 9 and hit Enter." << endl << endl;
                continue;
            }
        }
    }
}



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
                    || (row_input == "sample6") || (row_input == "sample7")
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
            else if (row_input == "sample7") {  // Shortcut for testing
                board_input = ".743...25.3..476....1....3.....6....4.6.9.3.2....5.....5.......1.2.3..8.36...521.";
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



void menu_enter() {
    Puzzle P(".................................................................................");
    while (true) {
        bool enter_another = false;
        // We begin by asking the user to enter the puzzle entries.
        P = get_puzzle_from_user();
        if (P.is_board_filled()) {
            cout << "Your puzzle has already been entirely filled!\nThere is nothing left to do with it.\n\n"
            << "What would you like to do?\n(1) Enter another puzzle\n[0] Return to the Main Menu\n\n";
            while (true) {
                cout << "Enter your choice: ";
                string menu_option;
                cin >> menu_option;
                cout << endl;
                if (menu_option.size()>1) {
                    cout << "Oops!  Your response has more than one character.\n"
                    "Simply type one of \"1\" or \"0\" and hit Enter." << endl << endl;
                    continue;
                }
                char const choice = menu_option[0];
                if (choice=='1') { enter_another = true; break; }
                else if (choice=='0') { return; }
                else {
                    cout << "Oops!  Your entry was not a recognized option.\n"
                    "Simply type one of \"1\" or \"0\" and hit Enter." << endl << endl;
                    continue;
                }
            }
        }
        if (enter_another) { continue; }
        break;
    }
    
    // We automatically analyze the board to determine if it has 0, 1, or 2+ solutions.
    //   Our menu options will depend on which of these cases we are in.
    int count = P.count_solutions();
    if (count == 0) { menu_puzzle_impossible(P); }
    else if (count == 1) { menu_puzzle_unique(P); }
    else if (count > 1) { menu_puzzle_nonunique(P, count); }
    return;
}



void menu_random() {
    return;
}



int menu_main() {
    string heading = "\n"
    "*--------*--------*-------*-------*--------*--------*\n"
    "|                                                   |\n"
    "|    SSS    U   U   DDD      OOO    K   K   U   U   |\n"
    "|   S   S   U   U   D  D    O   O   K  K    U   U   |\n"
    "|    S      U   U   D   D   O   O   K K     U   U   |\n"
    "|     S     U   U   D   D   O   O   KK      U   U   |\n"
    "|      S    U   U   D   D   O   O   K K     U   U   |\n"
    "|   S   S   U   U   D  D    O   O   K  K    U   U   |\n"
    "|    SSS     UUU    DDD      OOO    K   K    UUU    |\n"
    "*                                                   *\n"
    "|                                                   |\n"
    "|    SSS     OOO    L       V   V   EEEEE   RRRR    |\n"
    "|   S   S   O   O   L       V   V   E       R   R   |\n"
    "|    S      O   O   L       V   V   E       R   R   |\n"
    "|     S     O   O   L       V   V   EEEE    RRRR    |\n"
    "|      S    O   O   L       V   V   E       R   R   |\n"
    "|   S   S   O   O   L        V V    E       R   R   |\n"
    "|    SSS     OOO    LLLLL     V     EEEEE   R   R   |\n"
    "|                                                   |\n"
    "*--------*--------*-------*-------*--------*--------*\n"
    "                   By: Luke Nelsen \n";
    cout << heading;
    
    string main_menu_prompt = "MAIN MENU\n\n"
    "What would you like to do?\n"
    "( ) Learn about Sudoku puzzles [not yet available]\n"
    "(2) Enter my own Sudoku puzzle\n"
    "( ) Use a Sudoku puzzle generator [not yet available]\n"
    "[0] Exit the program\n\n";
    cout << main_menu_prompt;
    
    while (true) {
        cout << "Enter your choice: ";
        string menu_option;
        cin >> menu_option;
        cout << endl;
        if (menu_option.size()>1) {
            cout << "Oops!  Your response has more than one character.\n"
            "Simply type one of \"1\", \"2\", \"3\", or \"0\" and hit Enter." << endl << endl;
            continue;
        }
        char const choice = menu_option[0];
        if (choice=='1') { return 1; }
        else if (choice=='2') { return 2; }
        else if (choice=='3') { return 3; }
        else if (choice=='0') { return 0; }
        else {
            cout << "Oops!  Your entry was not a recognized option.\n"
            "Simply type one of \"1\", \"2\", \"3\", or \"0\" and hit Enter." << endl << endl;
            continue;
        }
    }
}






// Main Procedure

int main() {
    
    int main_choice = menu_main();
    
    while (main_choice > 0) {
        if (main_choice == 1) { menu_learn(); }
        else if (main_choice == 2) { menu_enter(); }
        else if (main_choice == 3) { menu_learn(); }
        
        main_choice = menu_main();
    }
    
    return 0;
}










// Member Functions

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
                StepUnit s("write",i,j,(int)entry-48,{1,2,3,4,5,6,7,8,9});
                step.stepunit_stack.push_back(s);
            }
        }
    }
    step.log_line = "User entered the following puzzle:\n"+make_board_entry_string();
    apply_step(step);
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



void Puzzle::print_log_terse() {
    int step_counter = 1;
    vector<Step>::iterator it = step_stack.begin();
    it++;
    while (it != step_stack.end()) {
        cout << "Step "+to_string(step_counter++)+": "+(*it).step_type+".  "+(*it++).log_line << endl;
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
    // For use after user initialization.
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
                StepUnit s("remove",i,j,0,{to_remove});
                step_stack.back().stepunit_stack.push_back(s);
                apply_stepunit(s);
            }
        }
    }
}



void Puzzle::update_available_options_after_written(int row, int col, int entry) {
    // For use in the program's search after the cell at board[row][col] has been filled with value entry.
    // Removes entry from available for each cell in the row, column, or house of row/col.
    // Each cell's adjustment is its own StepUnit, which is added to the top Step in the step_stack.
    // Adjust row
    for (int j=0; j<9; j++) {
        if (j==col) continue;
        Cell & c = board[row][j];
        list<int>::iterator it = c.available.begin();
        while (it != c.available.end()) {
            if (*it++ == entry) {
                StepUnit stepunit("remove", row, j, 0, {entry});
                step_stack.back().stepunit_stack.push_back(stepunit);
                apply_stepunit(stepunit);
                break;
            }
        }
    }
    // Adjust column
    for (int i=0; i<9; i++) {
        if (i==row) continue;
        Cell & c = board[i][col];
        list<int>::iterator it = c.available.begin();
        while (it != c.available.end()) {
            if (*it++ == entry) {
                StepUnit stepunit("remove", i, col, 0, {entry});
                step_stack.back().stepunit_stack.push_back(stepunit);
                apply_stepunit(stepunit);
                break;
            }
        }
    }
    // Adjust house
    for (int k=0; k<3; k++) {
        if (k==row%3) continue;
        for (int l=0; l<3; l++) {
            if (l==col%3) continue;
            Cell & c = board[3*(row/3)+k][3*(col/3)+l];
            list<int>::iterator it = c.available.begin();
            while (it != c.available.end()) {
                if (*it++ == entry) {
                    StepUnit stepunit("remove", 3*(row/3)+k, 3*(col/3)+l, 0, {entry});
                    step_stack.back().stepunit_stack.push_back(stepunit);
                    apply_stepunit(stepunit);
                    break;
                }
            }
        }
    }
}



bool Puzzle::check_for_obvious_problems() {
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            Cell & c = board[i][j];
            // Check if cell is unfilled but has none available
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
            // Check if cell is unfilled but has none available
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



bool Puzzle::check_for_none_available() {
    // Check for any unfilled cells with no options available
    for (int k=0; k<81; k++) if (board[k/9][k%9].value+board[k/9][k%9].available.size() == 0) return true;
    return false;
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
    int min_available = 10;
    for (int k=0; k<81; k++) {
        if (board[k/9][k%9].value == 0 && board[k/9][k%9].available.size() < min_available) {
            i = k/9;
            j = k%9;
            min_available = board[i][j].available.size();
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
        while (check_for_none_available()) {
            // For the most recent guessed cell, guess the next available option.
            // If we've backtracked all the way to initialization, we should close out the search.
            if (!bump_last_guess()) { return false; }
        }
        
        // At this point in the loop we are ready to move forward and make our next move!
        if (try_single_cell_option()) {}
        else {
            vector<int> coords = choose_guess_cell();
            make_guess(coords[0],coords[1]);
            update_available_options_after_written(coords[0], coords[1], step_stack.back().stepunit_stack.back().entry);
        }
        
        // Lastly, check to see if the board is now filled---if so, we've arrived at our next solution!
        if (is_board_filled()) { return true; }
    }
}



void Puzzle::reset_to_initialized() {
    while (step_stack.size() > 1) { unapply_last_step(); }  // If we are steps into the puzzle
    if (step_stack.size() < 1) { apply_step(init_step); }  // If the initial step was undone
}



int Puzzle::count_solutions() {
    // If we see any immediate issues, do not bother beginning a search
    // Note:  check_for_none_available() is used in move_to_next_solution(), but
    //        check_for_obvious_problems() is meant for immediately after initialization.
    if (check_for_obvious_problems()) { return 0; }
    
    int solution_count = 0;
    while (move_to_next_solution()) {
        solution_count++;
        if (solution_count > 1000) break;
    }
    reset_to_initialized();
    return solution_count;
}



bool Puzzle::try_single_cell_option() {
    // Look for a cell which has only one option; if found, write that option.
    for (int k=0; k<81; k++) {
        if (board[k/9][k%9].available.size() == 1) { // Works on first such cell found.
            int row = k/9;
            int col = k%9;
            int value = board[row][col].available.front();
            StepUnit stepunit("write", row, col, value, board[row][col].available);
            Step step("Single Cell Option");
            step.log_line = "The only option for r"+to_string(row+1)+"c"+to_string(col+1)+" is "+to_string(value)+".";
            step.stepunit_stack.push_back(stepunit);
            apply_step(step);
            update_available_options_after_written(row, col, value);
            return true;
        }
    }
    return false;
}

