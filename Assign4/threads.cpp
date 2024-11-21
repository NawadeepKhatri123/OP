
#include <thread>
#include <vector>
#include <ncurses.h>
#include <cstring>
#include <iostream>
#include <chrono>
#include <mutex>

using namespace std;

using VEC = vector<int>;
using MATRIX = vector<VEC>;

// Function declarations
void mouse_curse();
void displayMatrix(const MATRIX &M);
void game_of_life(MATRIX &M, int startRow, int endRow, int startCol, int endCol);
int count_neighbors(const MATRIX &M, int y, int x);
void run_game(MATRIX &M, int boardSize, int threadCount, int maxGen);

int main(int argc, char *argv[])
{
    // Parse command line arguments
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <board_size> <threads> <max_generations>\n";
        return 1;
    }

    // str to int
    int boardSize = stoi(argv[1]);
    int threadCount = stoi(argv[2]);
    int maxGen = stoi(argv[3]);

    if (boardSize % threadCount != 0) {
        std::cerr << "Board size must be divisible by the thread count\n";
        return 1;
    }

    mouse_curse();  // Start the mouse interaction and matrix initialization
    return 0;
}

void mouse_curse()
{
    MEVENT event;

    int yMax = 0, yMin = 1000, xMax = 0, xMin = 1000;
    vector<pair<int, int>> clicks;

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    mouseinterval(3);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    int boardSize = 20;
    MATRIX M(boardSize, VEC(boardSize, 0)); // Initialize a 20x20 matrix with 0 (dead)

    displayMatrix(M);

    // Listen for mouse clicks to set initial live cells
    while (1) {
        int c = getch();
        switch (c) {
            case KEY_MOUSE:
                if (getmouse(&event) == OK)
                    if (event.bstate & BUTTON1_PRESSED) {
                        int matrixY = event.y;
                        int matrixX = event.x / 5; // Adjust x position for matrix
                        if (matrixY < M.size() && matrixX < M[matrixY].size()) {
                            M[matrixY][matrixX] = 1; // Change value to 1 (alive)
                            clicks.push_back({matrixY, matrixX});
                        }
                        displayMatrix(M);
                    }
                break;
            case 's':  // Press 's' to start the simulation
                run_game(M, boardSize, 4, 10);  // Start the game with 10 generations
                return;
            case 'q': 
                goto end;  // Exit
        }
    }

end:
    endwin(); // End ncurses mode
}

// Function to display the matrix
void displayMatrix(const MATRIX &M)
{
    clear();
    for (int y = 0; y < M.size(); y++) {
        for (int x = 0; x < M[y].size(); x++) {
            if (M[y][x] == 1) {
                mvprintw(y, x * 5, " X ");
            } else {
                mvprintw(y, x * 5, " . ");
            }
        }
    }
    refresh();
}

// Function to count alive neighbors of a cell
int count_neighbors(const MATRIX &M, int y, int x)
{
    int aliveNeighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;  // Skip the cell itself
            int ny = y + i;
            int nx = x + j;
            if (ny >= 0 && ny < M.size() && nx >= 0 && nx < M[ny].size()) {
                aliveNeighbors += M[ny][nx];
            }
        }
    }
    return aliveNeighbors;
}

// Function to implement the Game of Life logic within a specified sub-region of the matrix
void game_of_life(MATRIX &M, int startRow, int endRow, int startCol, int endCol)
{
    MATRIX newM = M; // Create a copy of the matrix to store new generation
    for (int y = startRow; y < endRow; y++) {
        for (int x = startCol; x < endCol; x++) {
            int aliveNeighbors = count_neighbors(M, y, x);
            if (M[y][x] == 1) {
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    newM[y][x] = 0; // Cell dies
                }
            } else {
                if (aliveNeighbors == 3) {
                    newM[y][x] = 1; // Cell becomes alive
                }
            }
        }
    }
    // Copy back the new generation into the original matrix
    for (int y = startRow; y < endRow; y++) {
        for (int x = startCol; x < endCol; x++) {
            M[y][x] = newM[y][x];
        }
    }
}

// Function to run the Game of Life simulation for a number of generations
void run_game(MATRIX &M, int boardSize, int threadCount, int maxGen)
{
    int regionSize = boardSize / threadCount;
    vector<thread> threads;

    for (int gen = 0; gen < maxGen; gen++) {
        threads.clear();  // Clear thread vector for each generation

        // Create threads to process each region
        for (int i = 0; i < threadCount; i++) {
            for (int j = 0; j < threadCount; j++) {
                int startRow = i * regionSize;
                int endRow = (i + 1) * regionSize;
                int startCol = j * regionSize;
                int endCol = (j + 1) * regionSize;

                // Launch a thread to update a region of the matrix
                threads.push_back(thread(game_of_life, ref(M), startRow, endRow, startCol, endCol));
            }
        }

        // Wait for all threads to finish
        for (auto& t : threads) {
            t.join();
        }

        // Display the new generation
        displayMatrix(M);
        this_thread::sleep_for(chrono::milliseconds(500)); // Wait for a short period before showing the next generation
    }
}

