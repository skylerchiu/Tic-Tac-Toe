
/*Testing and debugging scenarios:
 - Ensuring a winning pattern is being recognized for both players, meaning ensuring each column, row, and diagonal would recognize
 when it is filled entirely with either X's or O's
 - Testing for sensing input errors. The program would have to respond in a way that would ask the player for a valid input
 until one is provided. A valid input would mean a number is inputted where it is in the range of 1-16, and has not already
 been taken by an X or an O
 - Testing for the possibility of a tie. When no possible moves are left (where there are no more valid moves, and there
    is no winner) the program should be able to record that as a tie, and ask the user if they wish to restart the game
 - Properly adding the number of wins. The program should properly track the number of wins for each player, and should continue
 adding until the user chooses to end the program

 Possible limitations:
 - An actual string, rather than a number is inputted, which would trigger an infinite loop
 - the number of wins exceeds the number that is stored in the integer value */

#include <iostream>
#include <string>

using namespace std;

bool row_win(string board[4][4]) { //iterates through rows to check for a win
    for (int i = 0; i < 4; i++) {
        bool same = true;
        string mark = board[i][0]; // save the first element of the row
        for (int j = 1; j < 4; j++) { // iterates through every value in the ith row 
            if (board[i][j] != mark) // checks if current value in the row has been marked down by current player
                same = false; // set same as false if there is no mark, therefore there is no row win in this row
        }
        if (same) return true; // if same remains true, that means there is a row win
    }
    return false; // return false because no rows were the same
}

bool col_win(string board[4][4]) { //iterates through columns to check for a win
    for (int i = 0; i < 4; i++) { //iterates through columns
        bool same = true;
        string mark = board[0][i]; // save the first element of the column
        for (int j = 1; j < 4; j++) { //increases row number, but keeps col same
            if (board[j][i] != mark) //checks if all values in that col is same as mark
                same = false; //if all values are not same in col, then that means there is no win in the current column
        }
        if (same) return true; //return true because there is col win detected 
    }
    return false; //return false because there is no win in any of the columns
}

bool diag_right_win(string board[4][4]) { //checks for left to right diagonal win
    string mark = board[0][0]; //starts from first square on board (0,0)
    bool same = true;
    for (int i = 1; i < 4; i++) { //iterates through diagonal from top left to bottom right
        if (board[i][i] != mark) //compares current elkemnt with first element
            same = false; //current element is not the same as mark, therefore there is no diagonal win
    }
    return same; //if mark = board[i][i] for all 3 iterations, that means there is a diagonal win
}

bool diag_left_win(string board[4][4]) { //checks for right-to-left diagonal win
    string mark = board[0][3]; //starts from first row, last square on board (0,3)
    bool same = true;
    for (int i = 1; i < 4; i++) { //iterates through diagonal from top right to bottom left 
        if (board[i][3 - i] != mark) //checks if mark is the same as current element
            same = false; // current element is not the same, thus set same equal to false
    }
    return same; // return true if whole diagonal is same, else return false
}

bool winner(string board[4][4]) { // return true if one player won (any type of win is acheived (column, row or diagonals))
    return col_win(board) || row_win(board) || diag_left_win(board) || diag_right_win(board);
}

bool board_filled(string board[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != "X" && board[i][j] != "O") return false;
        }
    }
    return true;
}

bool game_over(string board[4][4]) {
    return winner(board) || board_filled(board);
}

void display_board(string board[4][4]) { // prints board 
    cout << "-------------" << endl;

    // iterate through every element on the board and print it
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << "\t" << board[i][j]; // prints the element on position i,j
        }
        cout << endl;
    }
    cout << "-------------" << endl;
}

bool incorrect_move(string board[4][4], int coord) { //checks for incorrect move
    int i = (coord - 1) / 4; //finds row number of input (0-3) by integer dividing coord/4
    int j = (coord - 1) % 4; //finds col number of input (0-3) by modding coord by 4

    //if coord is not valid input (<1 or >16) or position on board is already taken, return true 
    return coord < 1 || coord > 16 || board[i][j] == "X" || board[i][j] == "O";
}

void make_move(string board[4][4], int coord, string players_mark) { //takes player input and places move on board 
    int row = (coord - 1) / 4; //finds row number of input (0-3) by integer dividing coord/4
    int col = (coord - 1) % 4; //finds col number of input (0-3) by modding coord by 4
    board[row][col] = players_mark; //equates players mark to row and col position on board
}

int player_number(bool p1_move) { //prints out which player's move it is
    // since true p1_move is true for player 1 and false for p2
    // an input of true results in output: 1 and input of false -> 2
    return int(!p1_move) + 1;
}

int get_move(string board[4][4], bool p1_move) { //takes move from player
    cout << "Enter the position to place your move (Player " << player_number(p1_move) << "): ";
    int coord; //input value should be 1-16, otherwise error message will be printed

    cin >> coord;
    while (incorrect_move(board, coord)) { //while spot is already taken/number does not exist, keep asking for new input
        cout << "Invalid move. Please try again: ";
        cin >> coord;
    }
    return coord; //returns player's (valid) choice of number (1-16)
}

string get_mark(bool p1) { //returns "X" for player 1, and "O" for player 2
    if (p1) return "X";
    return "O";
}

void winner_message(bool p1_won) { //prints game over message
    cout << "Game Over. Player " << player_number(p1_won) << " has won." << endl;
}

void tie_message() { //prints tie message
    cout << "The game is tied." << endl;
}

void print_scores(int p1_score, int p2_score, int ties) {
    cout << "Player 1 score: " << p1_score << endl;
    cout << "Player 2 score: " << p2_score << endl;
    cout << "Number of ties: " << ties << endl;
    cout << endl;
}

bool play_again() { // returns true to start a new game, or false to quit
    cout << "Press q to quit, or p to play again: ";
    char input; //input value should be 1-16, otherwise error message will be printed
    cin >> input;
    if (input == 'q') return false;
    return true;
}

void reset_board(string board[4][4]) {
    // populate board with position numbers
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            board[i][j] = to_string(i * 4 + j + 1); //
    }
}

bool game_loop(string board[4][4], bool p1_move) {
    while (!game_over(board)) { //as long as game is not ever, continue the game
        p1_move = !p1_move; // checks if it's player 1's move or player 2's move
        display_board(board);
        int move = get_move(board, p1_move); // get the move from the player
        make_move(board, move, get_mark(p1_move)); // make the move for the player
    }
    return p1_move;
}

void play() { //loops the game
    // Initialize the needed variables
    string board[4][4]; // intitialize the board
    int p1_score = 0; // keep track of both players wins
    int p2_score = 0;
    int ties = 0; //keep track of number of tie games
    bool p1_starts = true; // keep track of who starts for each game

    while (true) {
        p1_starts = !p1_starts; // change which player should start
        reset_board(board); // reset the board before each new game
        bool winning_player = game_loop(board, p1_starts); // run the current game
        display_board(board); //displays board again at the end of the game
        if (winner(board)) { //prints out winner message if there is a winner
            winner_message(winning_player);
            if (winning_player) p1_score++;
            else p2_score++;
        }
        else {
            tie_message(); // otherwise, print tie message
            ties++;
        }
        print_scores(p1_score, p2_score, ties); // print the scores after every game
        if (!play_again()) return;
    }
}

void finish_message() {
    cout << "Thanks for playing :)" << endl;
}

int main()
{
    play();
    finish_message(); // Thank them for playing
}
