/*
File: project1final.c
Compiler Version: Code::Blocks
Author: Vincesid O. Comp 120
Date: Nov. 16, 2024

------------------------------------------------------
Comp120 -- Project 1
Tic Tac Toe program for project 1.

This Tic Tac Toe uses a 1D array of size 9. User represents 'O' and Computer Represents 'X'
User begins with first turn, then computer until a win / tie is reached.
The program asks if user wants to play again and loops the round until user does not want to
play anymore.
-------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

/* Symbolic Constants */
#define GRIDSIZE 9
#define EMPTY ' '
#define USER 'O'
#define COMPUTER 'X'
#define MINSQUARE 0
#define MAXSQUARE 8
#define TRUE 1
#define FALSE 0

/* Prototypes */

/* I/O functions */
void displayOneRow(char, char, char);
void displayHorizontalLine();
void displayTTTBoards(char[]);
void emptyGridArray(char[]);
void playGame(); // use a do-while loop for this function
void playRound();
void usersTurn(char[]);
void compTurn(char[]);
int userSaysYes(char[]);
int randInt();
char TTTopponent(char);

/* Debugging functions */
int getIntInputInRange(int, int);
int isSquareAvailable(int, char[]);
void clearInputStream();
char getCharInput();
int getIntInput();

/* Winner checking functions */
int rowIsWinner(char[]);
int isWinner(char[]);
int columnIsWinner(char[]);
int DiagIsWinner(char[]);
int isTie(char[]);

// Ask tamara if I need to put description for main here
int main() {
    srand((unsigned) time(NULL)); // Generates random numbers to use for randInt() function
    playGame();
    return 0;
}

/* Plays the Game of TTT.
   Keeps looping until user does not want to play anymore,
   no input or return value
*/
void playGame() {
    int goAgain = TRUE;
    char TTTgridguide[GRIDSIZE] = {48, 49, 50, 51, 52, 53, 54, 55, 56};

    do {
        
        playRound();
        goAgain = userSaysYes("Do you want to play again? "); // Prompts the user if they want to play another round
    } while (goAgain == TRUE);
}

/* Plays a round of TTT,
   loops until max turns reached or a win is detected,
   no input or return value
*/
void playRound() {
    char TTTboard[GRIDSIZE];
    int maxTurns = GRIDSIZE; // max possible turns are 9, which is same as the grid size
    int winnerFound = FALSE;
    int currentPlayer = USER;
    int i; // indicates number of turns

    displayTTTBoards(TTTgridguide); // Displays guideline for selecting numbers
    emptyGridArray(TTTboard);

    for (i = 0; i < maxTurns && winnerFound != TRUE; ++i) {
        if (currentPlayer == USER)
            usersTurn(TTTboard);
        else if (currentPlayer == COMPUTER)
            compTurn(TTTboard);

        winnerFound = isWinner(TTTboard);
        if (winnerFound == TRUE && currentPlayer == USER) // Checks if there is a winner and the current player is a User
            printf("User wins!\n");
        else if (winnerFound == TRUE && currentPlayer == COMPUTER)
            printf("Computer Wins!\n");

        if (winnerFound == FALSE && isTie(TTTboard) == TRUE) {
            printf("It's a tie!\n");
            winnerFound = TRUE;
        }

        currentPlayer = TTTopponent(currentPlayer); // After each iteration (turn) TTTopponent swaps the current player to USER or COMPUTER; depending on the input
    }
}

/* Function takes the input of who the current player is,
   swaps the current player with the other player after each turn
   returns the not current player
*/
char TTTopponent(char player) {
    if (player == COMPUTER)
        return (USER);
    else if (player == USER)
        return (COMPUTER);
    return -1;
}

/* Function uses randInt() for a random integer in the valid range,
   an 'X' is placed based on the generated integer,
   Makes sure that the random integer matches an available square
   INPUT: array of the current TTT board
   OUTPUT: No output, but updates the TTT board
*/
void compTurn(char TTTboard[]) { // need to generate a randINT that is valid in range
    printf("Computers Turn!\n\n");
    int integer = randInt();
    while (isSquareAvailable(integer, TTTboard) != TRUE) {
        integer = randInt();
    }
    TTTboard[integer] = COMPUTER;
    displayTTTBoards(TTTboard);
}

/* Function ask user to select available square using integers by
   following the grid guide as guidance. Places an 'O' when user
   succesfully selects an available slot, keeps prompting the user
   for a valid input until it is reached
   INPUT: Array of the current TTT board
   OUTPUT: No output, but updates the TTT board
*/
void usersTurn(char TTTboard[]) {
    int integer;
    printf("It is your turn!\n\n");
    printf("Select a square available using the numbers above:");
    integer = getIntInputInRange(MINSQUARE, MAXSQUARE);
    printf("\n");
    while (isSquareAvailable(integer, TTTboard) != TRUE) {
        printf("Square is not available, please select an available one:");
        integer = getIntInputInRange(MINSQUARE, MAXSQUARE);
        printf("\n");
    }
    TTTboard[integer] = USER;
    displayTTTBoards(TTTboard);
}

/* Function generates a random integer that is in the range of the size of the TTT grid,
   using rand() with the srand() in main().
   INPUT: no input is taken.
   OUTPUT: returns a random value in the range of 0 to 8
*/
int randInt() {
    int range;
    int randomValue;
    range = MAXSQUARE - MINSQUARE + 1;
    randomValue = rand();
    randomValue = randomValue % range;
    randomValue = randomValue + MINSQUARE;
    return randomValue;
}

/* Function checks if the integer parameter corresponds to an available square
   / element in the TTT board array
   ie. checks if the integer-selected element has EMPTY ' ' in it.
   INPUT: an integer, and the current TTT board array
   POST: returns TRUE if the selected element is empty, returns FALSE otherwise
*/
int isSquareAvailable(int i, char TTTboard[]) {
    if (TTTboard[i] == EMPTY)
        return TRUE; // Maybe check if you can put this in one return statement
    return FALSE;
}

/* Function checks if a value is in the range based on min and max values
   INPUT: an integer value, along with minimum and maximum integer values
   OUTPUT: returns 1 (TRUE) if value is indeed within the bounds of min and max, returns 0 (FALSE) otherwise
*/
int valueInRange(int value, int min, int max) {
    return min <= value && max >= value && min <= max;
}

/* This function gets a valid integer input from the user.
   PRE: User has been prompted to enter an integer and min <= max.
   POST: an integer value, i, entered by user is returned, where min <= i <= max.
*/
int getIntInputInRange(int min, int max) {
    int i;
    do {
        i = getIntInput();
        if (valueInRange(i, min, max) != 1)
            printf("Value not in range please enter a valid value:");
    } while (valueInRange(i, min, max) != 1);
    return i;
}

/* This function keeps prompting the user to enter an int until they doso
   Pre: None
   Post: The input integer is returned
*/
int getIntInput() {
    int num;
    char term;
    while(scanf("%d%c",&num,&term) != 2 || term != '\n') {
        printf("Improper input. Please enter an integer: ");
        clearInputStream();
    }
    return num;
}

/* Functions initalizes the TTT grid array with EMPTY for each element
   Pre: Takes the TTT grid array at beginning of each round
   Post: nothing is returned. TTT grid is initialized with elements of EMPTY
*/
void emptyGridArray(char TTTboard[]) {
    int i;
    for (i = 0; i < GRIDSIZE; ++i) {
        TTTboard[i] = EMPTY;
    }
}

// Display functions

/* This function displays one row of a TTT board with squares s1, s2 and s3
   PRE: the output marker is at the start of a new line.
   POST: A row of the TTT board is drawn on the screen.
*/
void displayOneRow(char s1, char s2, char s3) {
    printf(" %c | %c | %c \n", s1, s2, s3);
}

/* This function displays one of the horizontal line in a TTT board.
   PRE: the output marker is at the start of a new line.
   POST: A horizontal line has been drawn on the screen.
*/
void displayHorizontalLine() {
    printf("-----------\n");
}

/* This function displays the current state of the TTT board
   PRE: none.
   POST: Draws the updated TTT board after each turn.
*/
void displayTTTBoards(char TTTboard[]) {
    int i;
    int s1;
    int s2;
    int s3;
    for (i = 0; i < GRIDSIZE; i += 3) { // ROWS
        s1 = TTTboard[i];
        s2 = TTTboard[i + 1];
        s3 = TTTboard[i + 2];
        displayOneRow(s1, s2, s3);
        if (i != 6)
            displayHorizontalLine();
    }
    printf("\n");
}

/* This function prompts the user with a yes/no question and returns their answer.
   PRE: question is a yes/no question the user should answer
   POST: returns true if user answered YES, false if they answer NO
*/
int userSaysYes(char question[]) {
    char answer;
    do {
        printf("%s (Y/N):",question);
        answer = getCharInput();
        answer = toupper(answer);
        clearInputStream();
    } while (!(answer == 'Y' || answer == 'N'));
    printf(" \n\n");
    return (answer == 'Y');
}

// Debugging functions

/* This function clears everything left on the input stream until a newline
   character is read
*/
void clearInputStream() {
    char input=getchar();
    while (input!='\n') {
        input = getchar();
    }
}

/* This function clears the newline characters('\n') from the input stream
   and reads the first non-newline character
   Pre: None
   Post: The first non-newline character is returned.
*/
char getCharInput() {
    char input;
    input  = getchar();
    while(input=='\n') {
        input = getchar();
    }
    return input;
}

// Checks if winner or tie

/* Function checks if there is a winner
   Pre: Takes the most recent TTT board array after each turn
   Post: Returns true if the win is in column, row, diagnoal
*/
int isWinner(char TTTboard[]) {
    return rowIsWinner(TTTboard) == TRUE || columnIsWinner(TTTboard) == TRUE || DiagIsWinner(TTTboard) == TRUE;
}

/* Function checks each row element to see if
   it is same in each row element
   Pre: takes the most recent TTT board array after each turn
   Post: returns true if all elements in row are same and not empty
*/
int rowIsWinner(char TTTboard[]) {
    int i; // Indicates the number of rows
    int s1;
    int s2;
    int s3;
    for (i = 0; i < GRIDSIZE; i += 3) {
        s1 = TTTboard[i];
        s2 = TTTboard[i + 1];
        s3 = TTTboard[i + 2];
        if (s1 == EMPTY && s2 == EMPTY && s3 == EMPTY)
            return FALSE;
        else if (s1 == s2 && s1 == s3 && s2 == s3)
            return TRUE;
    }
    return FALSE;
}

/* Function checks each column to see if
   all elements in column are same
   Pre: takes most recent TTT board array after each turn
   Post: returns true if all elements in column are same and not empty
*/
int columnIsWinner(char TTTboard[]) {
    int i;
    int s1;
    int s2;
    int s3;
    for (i = 0; i < 3; ++i) {
        s1 = TTTboard[i];
        s2 = TTTboard[i + 3];
        s3 = TTTboard[i + 6];
        if (s1 == EMPTY && s2 == EMPTY && s3 == EMPTY)
            return FALSE;
        else if (s1 == s2 && s1 == s3 && s2 == s3)
            return TRUE;
    }
    return FALSE;
}

/* Function checks if elements in diagonal are the same but not empty
   There are only 2 cases in which a diagonal win is possible in a
   3x3 grid
   Pre: takes most recent TTT board array after each turn
   Post: returns true if all elements in diagonal are same and not empty
*/
int DiagIsWinner(char TTTboard[]) {
    if (TTTboard[4] == EMPTY)
        return FALSE;
    else if (TTTboard[0] == TTTboard[4] && TTTboard[0] == TTTboard [8] && TTTboard[4] == TTTboard[8])
        return TRUE;
    else if (TTTboard[2] == TTTboard[4] && TTTboard[2] == TTTboard [6] && TTTboard[4] == TTTboard[6])
        return TRUE;
    return FALSE;
}

/* Function checks if there is winner or not
   by examining each element in the array
   a tie can only occur if all elements are filled
   but isWinner() == FALSE
   Pre: Takes most recent TTT board array after each turn
   Post: returns true if all elements are filled (this will be used in combination with isWinner() function)
*/
int isTie(char TTTboard[]) {
    int i;
    for (i = 0; i < GRIDSIZE; ++i) {
        if (TTTboard[i] == EMPTY)
            return FALSE;
    }
    return TRUE;
}
