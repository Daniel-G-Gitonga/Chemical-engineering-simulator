#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif

// -------- Cross-platform non-blocking input --------
#ifndef _WIN32
int kbhit() {
    termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

int getch() {
    return getchar();
}
#endif
// ---------------------------------------------------

class Game {
    std::vector<std::string> pieces = { "🟥","🟦","🟩","🟨","🟪","🟧","🔴","🔵","🟢","🟡" };
    std::vector<std::vector<std::string>> board;
    int rows, cols;
    int x, y;
    std::string piece;

public:
    Game(int r, int c) : rows(r), cols(c) {
        board.assign(rows, std::vector<std::string>(cols, "⬛")); // ⬛ = empty
        spawn();
    }

    void spawn() {
        x = rand() % cols;
        y = 0;
        piece = pieces[rand() % pieces.size()];
        if (board[y][x] != "⬛") {
            draw();
            std::cout << "Game Over!\n";
            exit(0);
        }
    }

    void step() {
        if (y+1 < rows && board[y+1][x] == "⬛") {
            y++;
        } else {
            board[y][x] = piece;
            clearLines();
            spawn();
        }
    }

    void moveLeft() {
        if (x > 0 && board[y][x-1] == "⬛") x--;
    }
    void moveRight() {
        if (x < cols-1 && board[y][x+1] == "⬛") x++;
    }
    void moveDown() {
        if (y+1 < rows && board[y+1][x] == "⬛") y++;
        else step();
    }

    void clearLines() {
        for (int row=rows-1; row>=0; row--) {
            bool full = true;
            for (int col=0; col<cols; col++) {
                if (board[row][col] == "⬛") { full = false; break; }
            }
            if (full) {
                for (int r=row; r>0; r--) {
                    for (int c=0; c<cols; c++) {
                        board[r][c] = board[r-1][c];
                    }
                }
                for (int c=0; c<cols; c++) board[0][c] = "⬛";
                row++;
            }
        }
    }

    void draw() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
        for (int i=0; i<rows; i++) {
            for (int j=0; j<cols; j++) {
                if (i==y && j==x)
                    std::cout << piece;
                else
                    std::cout << board[i][j];
            }
            std::cout << "\n";
        }
        std::cout << "[a=left, d=right, s=down, q=quit]\n";
    }
};

void runGame(int rows, int cols, int speed) {
    Game game(rows, cols);

    while (true) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 'a') game.moveLeft();
            else if (ch == 'd') game.moveRight();
            else if (ch == 's') game.moveDown();
            else if (ch == 'q') break;
        }

        game.step();
        game.draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }
}

int main() {
    srand(time(NULL));

    int rows = 20, cols = 10, speed = 400;
    while (true) {
        std::cout << "\n==== Falling Emoji Blocks ====\n";
        std::cout << "1. Start Game\n";
        std::cout << "2. Set Grid Size (current " << rows << "x" << cols << ")\n";
        std::cout << "3. Set Speed (current " << speed << "ms)\n";
        std::cout << "4. Quit\n";
        std::cout << "Choose: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            runGame(rows, cols, speed);
        } else if (choice == 2) {
            std::cout << "Enter rows: "; std::cin >> rows;
            std::cout << "Enter cols: "; std::cin >> cols;
        } else if (choice == 3) {
            std::cout << "Enter fall speed in ms (lower = faster): ";
            std::cin >> speed;
        } else if (choice == 4) {
            break;
        }
    }

    return 0;
}
