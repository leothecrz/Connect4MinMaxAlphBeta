
#include "main.hpp"

//GLOBALS
char board[SIZE][SIZE];
bool gameover = false;
int moves;
int minimaxCalls;
int copiesFound;
ENDSTATES endstate = NOT_SET;
std::unordered_map<size_t, Node> transpositionTable;
//

void setupBoard()
{
    for (size_t i = 0; i < SIZE; i++)
        for (size_t j = 0; j < SIZE; j++)
            board[i][j] = BLANK_TILE;
}

void printBoard()
{
    char letterLabel = 'A';

    std::cout << "\n";
    std::cout << "\t  ";
    for (size_t j = 1; j <= SIZE; j++)
        std::cout << j << ' ';
    std::cout << "\n";

    for (size_t i = 0; i < SIZE; i++) 
    {
        std::cout << '\t' << letterLabel++ << ' ';  
        for (size_t j = 0; j < SIZE; j++)
            std::cout << board[i][j] << ' ';
        std::cout << "\n";
    }
    std::cout << std::endl;
}

bool getYesNoResponse(std::string msg)
{
    std::string response;
    while (true)
    {
        std::cout << msg;
        std::cin >> response;

        for (char &c : response) c = tolower(c);

        if (response == "y") return true;
        else if (response == "n") return false;
        else
            std::cout << "Invalid response. Please enter 'y' or 'n'." << std::endl;
    }
}

char getCharFromAtoH() 
{
    char userInput;
    do {
        std::cout << "Enter a character from 'A' to 'H': ";
        std::cin >> userInput;
        userInput = tolower(userInput);

        if (userInput < 'a' || userInput > 'h')
            std::cout << "Invalid input. Please enter a character from 'A' to 'H'." << std::endl;
        
    } while (userInput < 'a' || userInput > 'h');
    return userInput;
}

int getIntFrom1to8() 
{
    int userInput;
    do {
        std::cout << "Enter an integer from 1 to 8: ";
        std::cin >> userInput;

        if (userInput < 1 || userInput > 8)
            std::cout << "Invalid input. Please enter an integer from 1 to 8." << std::endl;
        
    } while (userInput < 1 || userInput > 8);
    return userInput;
}

void getMoveFromUser()
{

    std::cout << "-- Users Turn --\n";
    
    char cRow = getCharFromAtoH();
    int col = getIntFrom1to8() - 1;
    int row = cRow - 'a';
    
    if(board[row][col] != BLANK_TILE)
    {
        std::cout << "Tile already used. Select another.\n";
        getMoveFromUser();
        return;
    }

    board[row][col] = USER_TILE;
    if(USER_TILE == checkFourInARow(board))
    {
        gameover = true;
        endstate = PLAYER_WIN;
    }

}

int evaluateConnectFour(const char board[SIZE][SIZE], char player) 
{
    int score = 0;

    return score;
}

char checkFourInARow(char b[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j <= SIZE - 4; j++) 
        {
            char candidate = b[i][j];
            if (candidate != '-' 
                && b[i][j + 1] == candidate 
                && b[i][j + 2] == candidate 
                && b[i][j + 3] == candidate) 
                return candidate;
        }
    
    for(int i = 0; i <= SIZE - 4; i++) 
        for (int j = 0; j < SIZE; j++) 
        {
            char candidate = b[i][j];
            if (candidate != '-' 
                && b[i + 1][j] == candidate 
                && b[i + 2][j] == candidate 
                && b[i + 3][j] == candidate) 
                return candidate;
        }
    
    return '\0';
}


int minimax(char b[SIZE][SIZE], int depth, int alpha, int beta, bool maxPlayer)
{

    // size_t boardKey = hashBoard(b);
    // auto it = transpositionTable.find(boardKey);
    // if (it != transpositionTable.end())
    // {
    //     Node& ref = transpositionTable[boardKey];
    //     switch (ref.getType())
    //     {
    //     case EXACT: 
    //         copiesFound++;
    //         return ref.getEval();
    //     case UPPER: 
    //             alpha = std::max(alpha, ref.getEval());
    //         break;
    //     case LOWER:
    //             beta = std::min(beta, ref.getEval());
    //         break;
    //     }
    //     if(beta <= alpha)
    //     {
    //         copiesFound++;
    //         return ref.getEval();
    //     }
    // }
    
    char result = checkFourInARow(b);
    if(depth == 0 || result != '\0' )
    {
        int eval = 0;
        if(result == USER_TILE)
            eval = (-depth) - 1 ;
        else if (result == AI_TILE)
            eval = (depth) + 1;
        
        //transpositionTable[boardKey] = Node(depth,eval,EXACT);
        return eval;    
    }
    int c = 0;
    if(maxPlayer)
    {
        int bestScore = INT32_MIN;
        for (size_t i = 0; i < SIZE; i++)
            for (size_t j = 0; j < SIZE; j++)
            {
                if(b[i][j] != BLANK_TILE)
                    continue;
                minimaxCalls++;

                b[i][j] = AI_TILE;
                int score = minimax(b, depth-1, alpha, beta, false);
                b[i][j] = BLANK_TILE;

                bestScore = std::max(score, bestScore);
                alpha = std::max(alpha, score);
                if(beta <= alpha)
                    break;
            }
        //transpositionTable[boardKey] = Node(depth, bestScore, UPPER);
        return bestScore;
    }
    else
    {
        int playerBest = INT32_MAX;
        for (size_t i = 0; i < SIZE; i++)
            for (size_t j = 0; j < SIZE; j++)
            {
                if(b[i][j] != BLANK_TILE)
                    continue;
                minimaxCalls++;

                b[i][j] = USER_TILE;
                int score = minimax(b, depth-1, alpha, beta, true);
                b[i][j] = BLANK_TILE;

                playerBest = std::min(score, playerBest);
                beta = std::min(beta, score);
                if(beta <= alpha)
                    break;
            }
        //transpositionTable[boardKey] = Node(depth, playerBest, LOWER);
        return playerBest;
    }
}

void AIMakeMove()
{

    minimaxCalls = 0;
    copiesFound = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    int bestScore = INT32_MIN;
    std::vector<int> move(2,0);

    transpositionTable.clear();

    for (size_t i = 0; i < SIZE; i++)
        for (size_t j = 0; j < SIZE; j++)
        {
            if(board[i][j] != BLANK_TILE)
                continue;
            
            board[i][j] = AI_TILE;
            int score = minimax(board, MAX_INNER_DEPTH, INT32_MIN, INT32_MAX, false);
            board[i][j] = BLANK_TILE;

            if(score > bestScore)
            {
                bestScore = score;
                move[0] = i;
                move[1] = j;
            }

        }
    
    
    board[move[0]][move[1]] = AI_TILE;
    if(AI_TILE == checkFourInARow(board))
    {
        endstate = AI_WIN;
        gameover = true;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    double executionTimeMicroseconds = static_cast<double>(duration.count()) / 1000000;
    
    std::cout << "Execution time: " << executionTimeMicroseconds << " seconds." 
    << "\nMinimax calls: " << minimaxCalls 
    << "\nMove Made: " << (char)(move[0] + 'A') << " , " << (move[1] + 1)
    << "\nCopies Skiped: " << copiesFound 
    << std::endl;

}

size_t hashBoard(const char b[SIZE][SIZE]) 
{
    std::hash<char> hasher;
    size_t hashValue = 0;

    for (int i = 0; i < SIZE; ++i) 
        for (int j = 0; j < SIZE; ++j) 
            hashValue ^= (hasher(b[i][j]) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2));

    return hashValue;
}

int main(int, char**)
{
    
    bool playerFirst = false;
    if(getYesNoResponse("Will the user go first (y/n) ?\n >>"))
        playerFirst = true;
    else
        playerFirst = false;

    moves = 0;

    setupBoard();
    printBoard();

    while (!gameover)
    {

        playerFirst ? getMoveFromUser() : AIMakeMove();
        printBoard();

        if(!gameover)
        {
            playerFirst ? AIMakeMove() : getMoveFromUser();
            printBoard();
        }
        
        moves += 2;
        if(moves >= 64)
        {
            endstate = DRAW;
            gameover = true;
        }

    }
    
    switch (endstate)
    {
    case PLAYER_WIN:
        std::cout << "\n THE USER WINS \n\n";
        break;
    case DRAW:
        std::cout << "\n ITS A DRAW \n\n";
        break;
    case AI_WIN:
        std::cout << "\n THE AI WINS \n\n";
        break;
    }

}
