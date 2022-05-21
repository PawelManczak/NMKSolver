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
    int Y, X, NUM_TO_WIN;
    int** board, ** buffor;
    int player;
    int curVal; //if checkIfSbWin returns true it will have a value of winner player
    TicTacToe(int Y, int X, int NUM_TO_WIN, int player);
    void printBoard(int** board);
    void swapValues(int** b1, int** b2);
    void copyBoard(int** b1, int** b2);
    int getAmountOfPossibleMoves(int** board);
    bool checkIfsbWin(int** board);
    void SOLVE_GAME_STATE();
    void GEN_ALL_POS_MOV();
    void GEN_ALL_POS_MOV_CUT_IF_GAME_OVER();
private:
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
            //cin >> board[y][x];
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

void TicTacToe::swapValues(int** b1, int** b2) {
    for (int y = 0; y < Y; y++)
    {
        for (int x = 0; x < X; x++) {
            swap(b1[y][x], b2[y][x]);
        }
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

int TicTacToe::minmax(int** b, int turn)
{
    if (checkIfsbWin(b)) {
        if (curVal == turn)
            return 1;
        else //if (curVal == 2)
            return -1;
    }
    if (getAmountOfPossibleMoves(b) == 0)
        return 0;

    int nextTurn = turn == 1 ? 2 : 1;

    bool flag = true;
    if (turn == 1) {
        int bestScore = -2;
        for (int i = 0; i < Y && flag; i++) {
            for (int j = 0; j < X && flag; j++) {
                // Is the spot available?
                if (b[i][j] == 0) {
                    b[i][j] = turn;
                    int score = minmax(board, nextTurn);
                    b[i][j] = 0;
                    bestScore = max(score, bestScore);
                    if (bestScore == 1) flag = false;
                }
            }
        }
        return bestScore;
    }
    else {
        int bestScore = INT_MAX;
        for (int i = 0; i < Y && flag; i++) {
            for (int j = 0; j < X && flag; j++) {
                // Is the spot available?
                if (board[i][j] == 0) {
                    board[i][j] = turn;
                    int score = minmax(board, nextTurn);
                    board[i][j] = 0;
                    bestScore = min(score, bestScore);
                    if (bestScore == -1) flag = false;
                }
            }
        }
        return bestScore;
    }
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

    int prevVal = 0; // 1=player1, 2=player2, 0=no owner. Player who occupied the previous space
    int numInRow = 0; // how many of prevValue has we seen before this

    for (int j = 0; j < Y; j++) { // every row
        prevVal = 0; // at row start we aren't counting in-a-row for either player
        for (int i = 0; i < X; i++) { // walk through this row:
            curVal = board[j][i];
            if (curVal != prevVal) { prevVal = curVal; numInRow = 1; }
            else { // we found a repeat:
                numInRow++;
                if (numInRow >= NUM_TO_WIN && curVal != 0) {
                    return true;
                }
            }
        }
    }

    prevVal = 0;
    numInRow = 0;
    for (int j = 0; j < X; j++) { // every row
        prevVal = 0; // at row start we aren't counting in-a-row for either player
        for (int i = 0; i < Y; i++) { // walk through this row:
            curVal = board[i][j];
            if (curVal != prevVal) { prevVal = curVal; numInRow = 1; }
            else { // we found a repeat:
                numInRow++;
                if (numInRow >= NUM_TO_WIN && curVal != 0) {
                    return true;
                }
            }
        }

    }

    //przkatna
    prevVal = 0;
    numInRow = 0;

    //from the left to the bottom
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            curVal = board[y][x];
            //cout << "c:" <<curVal << endl;
            //printBoard(board);
            int xt = x, yt = y;
            numInRow = 0;
            while (yt < Y && xt < X) {
                // cout << "c" << board[yt][xt] <<  endl;
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
                // cout << "c" << board[yt][xt] << endl;
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
    if (checkWinner(board) == 1) {
        printf("FIRST_PLAYER_WINS\n");
        return;
    }
    else if (checkWinner(board) == 2) {
        printf("SECOND_PLAYER_WINS\n");
        return;
    }

    copyBoard(board, buffor);

    while (!checkIfsbWin(board) && getAmountOfPossibleMoves(buffor) != 0)
    {
        int bestScore = -2;
        int bestY, bestX;
        for (int y = 0; y < Y; y++)
        {
            for (int x = 0; x < X; x++) {
                if (board[y][x] == 0) {
                    buffor[y][x] = player;
                    int score = minmax(buffor, player);
                    buffor[y][x] = 0;
                    if (score > bestScore) {
                        bestScore = score;
                        bestX = x;
                        bestY = y;
                    }
                }
                copyBoard(board, buffor);
            }
        }
        board[bestY][bestX] = player;
        player = player == 1 ? 2 : 1;

    }

    if (checkWinner(board) == 1) {
        printf("FIRST_PLAYER_WINS\n");
        return;
    }
    else if (checkWinner(board) == 2) {
        printf("SECOND_PLAYER_WINS\n");
        return;
    }




}
int main()
{
    int N = -1, M = -1, K = -1;
    //board szie NxM
    //size of line to win 
    int player = -1;
    string command = " ";

    char tmp[50];


    while (scanf("%49s", &tmp) != EOF) {
        command = tmp;
        scanf("%d %d %d %d", &N, &M, &K, &player);
        //cin >> N >> M >> K >> player;
        TicTacToe game = TicTacToe(N, M, K, player);


        if (command == "GEN_ALL_POS_MOV") {
            game.GEN_ALL_POS_MOV();
        }
        else if (command == "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") {
            game.GEN_ALL_POS_MOV_CUT_IF_GAME_OVER();
        }
        else if (command == "SOLVE_GAME_STATE") {
            game.SOLVE_GAME_STATE();
        }

    }
}
