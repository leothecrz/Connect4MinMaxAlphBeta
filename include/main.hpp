
#include <iostream>

#include <chrono>

#include <vector>

#include <algorithm>

#include <unordered_map>

#include "node.hpp"

//SIZE CONST
extern const int SIZE = 8;
extern const int MAX_INNER_DEPTH = 4;

// TILES
extern const char AI_TILE = 'X';
extern const char USER_TILE = 'O';
extern const char BLANK_TILE = '-';

enum ENDSTATES
{
    NOT_SET,
    PLAYER_WIN,
    DRAW,
    AI_WIN
};

void setupBoard();

void printBoard();

bool getYesNoResponse(std::string msg);

char getCharFromAtoH();

int getIntFrom1to8();

char checkFourInARow(char b[SIZE][SIZE]);

void getMoveFromUser();

int minimax(char b[SIZE][SIZE], int depth, int alpha, int beta, bool maxPlayer);

void AIMakeMove();

size_t hashBoard(const char b[SIZE][SIZE]);

int main(int, char**);
