#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int gridSize;
int score = 0;

// current grid and previous grid(for undo)
vector<vector<int>> board;
vector<vector<int>> previousBoard;
int previousScore = 0;

//display the board
void displayBoard() {
    cout << "\nScore: " << score << "\n\n";
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (board[i][j] == 0)
                cout << ".\t";
            else
                cout << board[i][j] << "\t";
        }
        cout << "\n";
    }
}

// add a new tile
void addNewTile() {
    vector<pair<int, int>> emptyCells;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (board[i][j] == 0)
                emptyCells.push_back({i, j});
        }
    }

    if (emptyCells.empty())
        return;

    int index = rand() % emptyCells.size();
    int value = (rand() % 10 < 9) ? 2 : 4;

    board[emptyCells[index].first][emptyCells[index].second] = value;
}

//shift non-zero elements to left
vector<int> shiftLeft(vector<int> row) {
    vector<int> result;

    for (int x : row) {
        if (x != 0)
            result.push_back(x);
    }

    while (result.size() < gridSize)
        result.push_back(0);

    return result;
}

// merge equal tiles (here i have custom rule)
vector<int> mergeTiles(vector<int> row) {
    for (int i = 0; i < gridSize - 1; i++) {
        if (row[i] != 0 && row[i] == row[i + 1]) {
            int mergedValue = (row[i] + row[i + 1]) * 2;
            row[i] = mergedValue;
            score += mergedValue;
            row[i + 1] = 0;
            i++; // prevent double merge
        }
    }
    return row;
}

// move left
bool moveLeft() {
    bool changed = false;

    for (int i = 0; i < gridSize; i++) {
        vector<int> originalRow = board[i];
        vector<int> shifted = shiftLeft(originalRow);
        vector<int> merged = mergeTiles(shifted);
        vector<int> finalRow = shiftLeft(merged);

        if (finalRow != originalRow) {
            board[i] = finalRow;
            changed = true;
        }
    }
    return changed;
}

//rotate board clockwise
void rotateBoard(){
    vector<vector<int>> rotated(gridSize, vector<int>(gridSize));

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            rotated[j][gridSize - i - 1] = board[i][j];
        }
    }
    board = rotated;
}

// different directional moves
bool moveRight() {
    rotateBoard();
    rotateBoard();
    bool moved = moveLeft();
    rotateBoard();
    rotateBoard();
    return moved;
}

bool moveUp() {
    rotateBoard();
    rotateBoard();
    rotateBoard();
    bool moved = moveLeft();
    rotateBoard();
    return moved;
}

bool moveDown() {
    rotateBoard();
    bool moved = moveLeft();
    rotateBoard();
    rotateBoard();
    rotateBoard();
    return moved;
}

//Check if any move is possible
bool isMovePossible() {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (board[i][j] == 0)
                return true;
        }
    }

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize - 1; j++) {
            if (board[i][j] == board[i][j + 1])
                return true;
        }
    }

    for (int j = 0; j < gridSize; j++) {
        for (int i = 0; i < gridSize - 1; i++) {
            if (board[i][j] == board[i + 1][j])
                return true;
        }
    }

    return false;
}

// main implementation code
int main() {
    srand(time(0));

    cout << "Enter grid size (4 or 5): ";
    cin >> gridSize;

    if (gridSize != 4 && gridSize != 5) {
        cout << "Invalid grid size.\n";
        return 0;
    }

    board.assign(gridSize, vector<int>(gridSize, 0));
    addNewTile();
    addNewTile();

    char input;

    while (true) {
        displayBoard();
        cout << "\nControls:\n";
        cout << "W = Up | A = Left | S = Down | D = Right\n";
        cout << "U = Undo | Q = Quit\n";

        cin >> input;

        bool moved = false;

        if (input == 'q' || input == 'Q')
            break;

        if (input == 'u' || input == 'U') {
            board = previousBoard;
            score = previousScore;
            continue;
        }

        previousBoard = board;
        previousScore = score;

        if (input == 'a' || input == 'A') moved = moveLeft();
        else if (input == 'd' || input == 'D') moved = moveRight();
        else if (input == 'w' || input == 'W') moved = moveUp();
        else if (input == 's' || input == 'S') moved = moveDown();

        if (moved) {
            addNewTile();
            if (!isMovePossible()) {
                displayBoard();
                cout << "\nGame Over!\n";
                break;
            }
        }
    }

    return 0;
}
