#include <iostream>
#include <cstdlib>
#include <ctime>

// ANSI escape codes for colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

class Game {
private:
    int numberToGuess;

public:
    Game() {
        srand(time(0));
        numberToGuess = rand() % 100 + 1; // Випадкове число від 1 до 100
    }

    void startGame() {
        int guess;
        bool correct = false;

        std::cout << BLUE << "Вгадай число від 1 до 100: " << RESET;

        while (!correct) {
            std::cin >> guess;
            correct = checkGuess(guess);
        }

        displayResult(true);
    }

private:
    bool checkGuess(int guess) {
        if (guess < numberToGuess) {
            std::cout << YELLOW << "Більше!" << RESET << std::endl;
            return false;
        } else if (guess > numberToGuess) {
            std::cout << YELLOW << "Менше!" << RESET << std::endl;
            return false;
        } else {
            return true;
        }
    }

    void displayResult(bool result) {
        if (result) {
            std::cout << GREEN << "Вітаю! Ви вгадали число." << RESET << std::endl;
        }
    }
};

class Player {
public:
    void play() {
        Game game;
        game.startGame();
    }
};

int main() {
    Player player;
    player.play();
    return 0;
}
