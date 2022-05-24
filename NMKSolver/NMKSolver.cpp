#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

int min(int a, int b) {
    if (a > b) return b;
    else return a;
}

int max(int a, int b) {
    if (a < b) return b;
    else return a;
}

class TicTacToe {
public:    
    TicTacToe(int Y, int X, int NUM_TO_WIN, int player);
    void SOLVE_GAME_STATE();
    void GEN_ALL_POS_MOV();
    void GEN_ALL_POS_MOV_CUT_IF_GAME_OVER();
private:
    int Y, X, NUM_TO_WIN;
    int** board, ** buffor;
    int player;
    int curVal; //if checkIfSbWin returns true it will have a value of winner player
    void printBoard(int** board);
    void copyBoard(int** b1, int** b2);
    int getAmountOfPossibleMoves(int** board);
    bool checkIfsbWin(int** board);
    int checkWinner(int** board);
    int minmax(int** b, int turn);
};


TicTacToe::TicTacToe(int Y, int X, int NUM_TO_WIN, int player)
{
    this->Y = Y;
    this->X = X;
    this->NUM_TO_WIN = NUM_TO_WIN;
    this->player = player;

    board = new int* [Y];
    buffor = new int* [Y];
    for (int i = 0; i < Y; i++)
    {
        board[i] = new int[X];
        buffor[i] = new int[X];
    }
    for (int y = 0; y < Y; y++)
    {
        for (int x = 0; x < X; x++) {
            scanf("%d", &board[y][x]);
        }
    }
}

void TicTacToe::printBoard(int** b) {

    for (int y = 0; y < Y; y++)
    {
        for (int x = 0; x < X; x++) {
            printf("%d ", b[y][x]);
        }
        printf("\n");
    }
}

void TicTacToe::copyBoard(int** board1, int** board2) { //from first to second
    for (int y = 0; y < Y; y++)
    {
        for (int x = 0; x < X; x++) {
            board2[y][x] = board1[y][x];
        }
    }
}

void TicTacToe::GEN_ALL_POS_MOV() {

    //if the board shows winning pos print 0
    copyBoard(board, buffor);
    if (checkIfsbWin(buffor)) {
        printf("0\n");
        return;
    }

    printf("%d\n", getAmountOfPossibleMoves(board));

    for (int y = 0; y < Y; y++)
    {
        for (int x = 0; x < X; x++) {
            if (board[y][x] == 0) {
                buffor[y][x] = player;
                printBoard(buffor);
            }
            copyBoard(board, buffor);
        }
    }
}

void TicTacToe::GEN_ALL_POS_MOV_CUT_IF_GAME_OVER()
{

    copyBoard(board, buffor);
    if (checkIfsbWin(buffor)) {
        printf("0\n");
        return;
    }

    for (int y = 0; y < Y; y++)
    {
        for (int x = 0; x < X; x++) {
            if (board[y][x] == 0) {
                buffor[y][x] = player;
                if (checkIfsbWin(buffor)) {
                    printf("1\n");
                    printBoard(buffor);
                    return;
                }
            }
            copyBoard(board, buffor);
        }
    }

    printf("%d\n", getAmountOfPossibleMoves(board));

    for (int y = 0; y < Y; y++)
    {
        for (int x = 0; x < X; x++) {
            if (board[y][x] == 0) {
                buffor[y][x] = player;
                printBoard(buffor);
            }
            copyBoard(board, buffor);
        }
    }
}

int TicTacToe::checkWinner(int** b)
{
    if (checkIfsbWin(b)) {
        if (curVal == 1)
            return 1;
        else //if (curVal == 2)
            return 2;
    }
    else
        return 0;
}
int getOpponent(int activePlayer)
{
    return activePlayer == 1 ? 2 : 1;
}
int TicTacToe::minmax(int** b, int turn)
{
    int bestScore = 0;
    if (checkIfsbWin(b)) {
        if (curVal == 1)
            return 1;
        else //if (curVal == 2)
            return -1;
    }
    if (getAmountOfPossibleMoves(b) == 0)
        return 0;

    int nextTurn = getOpponent(turn);

    bool flag = true;
    if (turn == 1) {
        bestScore = -1;
        for (int i = 0; i < Y && flag; i++) {
            for (int j = 0; j < X && flag; j++) {
                if (b[i][j] == 0) { //the spot is avaible
                    b[i][j] = turn;
                    bestScore = max(minmax(b, nextTurn), bestScore);
                    b[i][j] = 0;
                    if (bestScore == 1) flag = false;
                }
            }
        }
    }
    else {
        bestScore = 1;
        for (int i = 0; i < Y && flag; i++) {
            for (int j = 0; j < X && flag; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = turn;
                    bestScore = min(minmax(b, nextTurn), bestScore);
                    board[i][j] = 0;
                    if (bestScore == -1) flag = false;
                }
            }
        }
    }
    return bestScore;
}

int TicTacToe::getAmountOfPossibleMoves(int** board) {
    int amount = 0;
    for (int y = 0; y < Y; y++)
    {
        for (int x = 0; x < X; x++) {
            if (board[y][x] == 0)
                amount++;
        }
    }
    return amount;
}

bool TicTacToe::checkIfsbWin(int** board) {

    int prevVal = 0; //Player who occupied the previous space
    int numInRow = 0; 

    for (int y = 0; y < Y; y++) { 
        prevVal = 0;
        for (int x = 0; x < X; x++) { 
            curVal = board[y][x];
            if (curVal != prevVal) { 
                prevVal = curVal; 
                numInRow = 1; 
            }
            else {
                numInRow++;
                if (numInRow >= NUM_TO_WIN && curVal != 0) {
                    return true;
                }
            }
        }
    }

    prevVal = 0;
    numInRow = 0;
    for (int x = 0; x < X; x++) { 
        prevVal = 0;
        for (int y = 0; y < Y; y++) {
            curVal = board[y][x];
            if (curVal != prevVal) {
                prevVal = curVal; 
                numInRow = 1; 
            }
            else { 
                numInRow++;
                if (numInRow >= NUM_TO_WIN && curVal != 0) {
                    return true;
                }
            }
        }

    }

    prevVal = 0;

    //from the left to the bottom
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            curVal = board[y][x];
            int xt = x, yt = y;
            numInRow = 0;
            while (yt < Y && xt < X) {
                if (board[yt][xt] == curVal)
                    numInRow++;
                else {
                    numInRow = 0;
                    break;
                }
                if (numInRow >= NUM_TO_WIN && curVal != 0) {
                    return true;
                }

                yt++;
                xt++;
            }
        }
    }
    //from the right upper corner to the bottom
    prevVal = 0;

    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            numInRow = 0;
            curVal = board[y][x];
            int xt = x, yt = y;
            while (yt < Y && xt >= 0) {
                if (board[yt][xt] == curVal)
                    numInRow++;
                else {
                    numInRow = 0;
                    break;
                }
                if (numInRow >= NUM_TO_WIN && curVal != 0)
                    return true;

                yt++;
                xt--;
            }
        }
    }

    return false;
}

void TicTacToe::SOLVE_GAME_STATE()
{
    int score = 0;

    if (!checkIfsbWin(board) && getAmountOfPossibleMoves(board) != 0) {
        score = minmax(board, player);
    }
    if (checkIfsbWin(board)) {
        if (curVal == 1)
            score = 1;
        else //if (curVal == 2)
            score = -1;
    }
    if (score == 1) {
        printf("FIRST_PLAYER_WINS\n");
        return;
    }
    else if (score == -1) {
        printf("SECOND_PLAYER_WINS\n");
        return;
    }
    else if (score == 0) {
        printf("BOTH_PLAYERS_TIE\n");
    }

}
int main()
{
    int N = -1, M = -1, K = -1;
    //board szie NxM
    //size of K line to win 
    int player = -1;
    char command[50];


    while (scanf("%49s", &command) != EOF) {

        scanf("%d %d %d %d", &N, &M, &K, &player);
        TicTacToe game = TicTacToe(N, M, K, player);

        
        if (!strcmp("GEN_ALL_POS_MOV", command)) {
            game.GEN_ALL_POS_MOV();
        }
        else if (!strcmp("GEN_ALL_POS_MOV_CUT_IF_GAME_OVER", command)) {
            game.GEN_ALL_POS_MOV_CUT_IF_GAME_OVER();
        }
        else if (!strcmp("SOLVE_GAME_STATE", command)){
            game.SOLVE_GAME_STATE();
        }

    }
}