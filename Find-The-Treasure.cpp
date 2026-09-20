#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
using namespace std;
// Set console text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
// Reset console text color to default
void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
// Class to show welcome message
class Welcome {
public:
    static void show() {
        setColor(14);
        cout << "====================================================\n";
        cout << "           Welcome to ' Find The Treasure'        \n";
        cout << "====================================================\n\n";
        resetColor();
        setColor(11);
        cout << "Your journey begins now, adventurer.\n";
        cout << "Think wisely, choose bravely, and good luck!\n";
        cout << "====================================================\n\n";
        resetColor();
    }
};
// Class to store and manage player information
class Player {
    string name;
    int score;
public:
    Player(string n) {
        name = n;
        score = 0;
    }
    void updateScore(int val) {
        score += val;
    }
    int getScore() const {
        return score;
    }
    string getName() const {
        return name;
    }
    void resetScore() {
        score = 0;
    }
};
// Class to track time taken by player
class Timer {
    time_t startTime;
public:
    void start() {
        startTime = time(0);// current system time
    }
    int getElapsed() const {
        return (int)(time(0) - startTime);// returns time in seconds
    }
};
// Class to give hints to the player
class Hint {
public:
    static void give(int treasureDoor, int totalDoors) {
        int clueType = rand() % 3;// pick 0, 1 or 2 randomly
        setColor(11);
        cout << "Hint: ";
        if (clueType == 0) {
            if (treasureDoor % 2 == 0) // Hint about even/odd door number
                cout << "Try even numbered doors.\n";
            else
                cout << "Try odd numbered doors.\n";
        }
        else if (clueType == 1) {
            if (treasureDoor > totalDoors / 2)  // Hint about door range (low or high)
                cout << "Look towards the higher numbered doors.\n";
            else
                cout << "Look near the lower numbered doors.\n";
        }
        else {
            if (treasureDoor != 1) // Hint about door #1 specifically
                cout << "The treasure is not behind the first door.\n";
            else
                cout << "Try the first door!\n";
        }
        resetColor();
    }
};
// Class to ask a simple quiz question to the player
class Quiz {
public:
    static void ask(Player &p) {
        int a = rand() % 10 + 1;
        int b = rand() % 10 + 1;
        setColor(14);
        cout << "Quiz: What is " << a << " + " << b << "? (Answer quickly): ";
        resetColor();
        string input = "";
        time_t start = time(0);
        // Get input within 3 seconds
        while (time(0) - start < 3) {
            if (_kbhit()) 
			{// Check if key was pressed
                char ch = _getch();
                if (ch == '\r') break;  // Enter key
                if (isdigit(ch)) {
                    cout << ch;
                    input += ch; // append digit to input string
                }
            }
        }
        cout << endl;
        if (input == "") {
            setColor(12);
            cout << "Time's up! No points.\n";
            resetColor();
            return;
        }
        int answer = stoi(input); // convert string to integer
        if (answer == a + b) {
            setColor(10);
            cout << "Correct! You earned 3 points.\n";
            p.updateScore(3);
        }
        else {
            setColor(12);
            cout << "Wrong answer. No points deducted.\n";
        }
        resetColor();
    }
};
// Class representing each door in the game
class Door {
    int type; 
    bool opened;
    int treasureDoor;
    static int totalDoors;
public:
    Door(int treasure, int total) : opened(false), treasureDoor(treasure) {
        totalDoors = total;
                // Randomly assign door type
        int r = rand() % 100;
        if (r < 25) type = 0;
        else if (r < 45) type = 1;
        else if (r < 70) type = 2;
        else type = 3;
    }
    bool open(Player &p, int doorNum) {
        if (opened) {
            setColor(12);
            cout << "This door is already opened.\n";
            resetColor();
            return false;
        }
        opened = true;
        if (doorNum == treasureDoor) {
            setColor(10);
            cout << "You found the TREASURE! (+5 points)\n";
            p.updateScore(5);
            resetColor();
            return true;
        }
        switch (type) {
        case 1:
            setColor(12);
            cout << "Trap! You lost 2 points.\n";
            p.updateScore(-2);
            resetColor();
            break;
        case 2:
            Hint::give(treasureDoor, totalDoors);
            break;
        case 3:
            Quiz::ask(p);
            break;
        default:
            cout << "This door is empty.\n";
            break;
        }
        return false;
    }
};
int Door::totalDoors = 0;
// Class that represents a full level with many doors
class Level {
    string name;
    int numDoors;
    int tries;
    int treasureDoor;
    Door **doors; // Dynamically create doors
public:
    Level(string n, int d, int t) : name(n), numDoors(d), tries(t) {
        treasureDoor = rand() % numDoors + 1;
        doors = new Door *[numDoors];
        for (int i = 0; i < numDoors; i++) {
            doors[i] = new Door(treasureDoor, numDoors);
        }
    }
    ~Level() {
        for (int i = 0; i < numDoors; i++) {
            delete doors[i];
        }
        delete[] doors;
    }
    bool play(Player &p, Timer &timer) {
        setColor(11);
        cout << "\nLevel: " << name << " | Doors: " << numDoors << " | Tries: " << tries << "\n\n";
        resetColor();
        for (int i = 0; i < tries; i++) {
            setColor(14);
            cout << "Try " << i + 1 << " of " << tries << " | Choose door (1-" << numDoors << "): ";
            resetColor();
            int choice;
            cin >> choice;
            if (choice < 1 || choice > numDoors) {
                setColor(12);
                cout << "Invalid door number, try again.\n";
                resetColor();
                i--;
                continue;
            }
            if (doors[choice - 1]->open(p, choice)) {
                return true; // Treasure found
            }
            cout << "Current Score: " << p.getScore() << "\n";
            cout << "Time elapsed: " << timer.getElapsed() << " seconds\n\n";
        }
        setColor(12);
        cout << "You didn't find the treasure. The treasure was behind door " << treasureDoor << ".\n\n";
        resetColor();
        return false;
    }
};
// Creates different levels based on difficulty
class LevelFactory {
public:
    static Level *create(int choice) {
        if (choice == 1) return new Level("Easy", 5, 3);
        if (choice == 2) return new Level("Medium", 8, 4);
        if (choice == 3) return new Level("Hard", 12, 6);
        return nullptr;
    }
};
// Displays final result after each game
class ScoreBoard {
public:
    static void display(const Player &p, const Timer &t) {
        setColor(11);
        cout << "\n===== YOUR ADVENTURE SUMMARY =====\n\n";
        setColor(13);
        cout << "Player Name: " << p.getName() << "\n";
        cout << "Final Score: " << p.getScore() << "\n";
        cout << "Total Time: " << t.getElapsed() << " seconds\n\n";
        resetColor();
    }
};
// Controls the flow of the full game
class Game {
    Player *player;
    Timer timer;
public:
    void start() {
        srand((unsigned)time(0));
        Welcome::show();
        setColor(11);
        cout << "Enter your name: ";
        resetColor();
        string name;
        cin >> name;
        player = new Player(name);
        char playAgain = 'y';
        while (playAgain == 'y' || playAgain == 'Y') {
            timer.start();
            player->resetScore();
            bool won = playMenu();
            ScoreBoard::display(*player, timer);
            if (won) {
                setColor(10);
                cout << "Congratulations! You won this level.\n\n";
                resetColor();
                setColor(11);
                cout << "Do you want to continue to the next level? (y/n): ";
                resetColor();
                cin >> playAgain;
            }
            else {
                setColor(12);
                cout << "Game Over. Do you want to try more levels? (y/n): ";
                resetColor();
                cin >> playAgain;
            }
        }
        setColor(14);
        cout << "\nThanks for playing, " << player->getName() << "! Goodbye!\n";
        resetColor();
        delete player;
    }
    bool playMenu() {
        setColor(14);
        cout << "\nChoose Difficulty Level:\n\n";
        resetColor();
        cout << "1. Easy    (5 doors, 3 tries)\n";
        cout << "2. Medium  (8 doors, 4 tries)\n";
        cout << "3. Hard    (12 doors, 6 tries)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        if (choice == 4) {
            setColor(14);
            cout << "Exiting game...\n";
            resetColor();
            exit(0);
        }
        Level *level = LevelFactory::create(choice);
        if (!level) {
            setColor(12);
            cout << "Invalid choice. Starting Easy level by default.\n";
            resetColor();
            level = LevelFactory::create(1);
        }
        bool won = level->play(*player, timer);
        delete level;
        return won;
    }
};
// Program starts here
int main() {
    Game game;
    game.start();
    return 0;
}
