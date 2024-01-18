
#include <iostream>

#include <chrono>

#include <vector>

#include <algorithm>

#include <unordered_map>

#include <random>

#include "node.hpp"

extern const int SIZE = 8;
extern const int MAX_DEPTH = 4;
extern const char AI_TILE = 'X';
extern const char USER_TILE = 'O';
extern const char BLANK_TILE = '-';

void setupBoard();

void printBoard();

bool getYesNoResponse(std::string msg);

char getCharFromAtoH();

int getIntFrom1to8();

char checkFourInARow(char b[SIZE][SIZE]);

void getMoveFromUser();

int minimax(char b[SIZE][SIZE], int depth, int alpha, int beta, bool maxPlayer);

void AIMakeMove();

int main(int, char**);
