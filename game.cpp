#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

// Global Variables
bool gameOver;
int score;
int playerY; // 0 = Ground, 1 = Jump
int hurdlePos;

void Setup() {
    gameOver = false;
    score = 0;
    playerY = 0;
    hurdlePos = 20; // Hurdle start position
}

void Draw() {
    system("cls"); // Screen clear karne ke liye

    // Header Display
    cout << "======================================" << endl;
    cout << "   DEVELOPER: AWAIS AHMAD" << endl;
    cout << "   ROLL NO:   25-ME-108" << endl;
    cout << "======================================" << endl;
    cout << "Score: " << score << endl;

    // Game Area Drawing
    for (int i = 0; i < 3; i++) { // Vertical space
        for (int j = 0; j < 25; j++) {
            if (i == 1 && j == 2 && playerY == 1) cout << "P"; // Player in air
            else if (i == 2 && j == 2 && playerY == 0) cout << "P"; // Player on ground
            else if (i == 2 && j == hurdlePos) cout << "H"; // Hurdle
            else if (i == 2) cout << "_"; // Ground line
            else cout << " ";
        }
        cout << endl;
    }
    cout << "\nPress SPACE to JUMP! (Esc to Quit)" << endl;
}

void Input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == ' ' && playerY == 0) {
            playerY = 1; // Jump up
        }
        if (key == 27) gameOver = true; // Escape key
    }
}

void Logic() {
    // Hurdle movement
    hurdlePos--;
    if (hurdlePos < 0) {
        hurdlePos = 25;
        score++;
    }

    // Gravity logic (simple)
    static int jumpTimer = 0;
    if (playerY == 1) {
        jumpTimer++;
        if (jumpTimer > 4) { // Time spent in air
            playerY = 0;
            jumpTimer = 0;
        }
    }

    // Collision Detection
    if (hurdlePos == 2 && playerY == 0) {
        gameOver = true;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(50); // Game speed control
    }

    cout << "\nGAME OVER!" << endl;
    cout << "Final Score: " << score << endl;
    return 0;
}
