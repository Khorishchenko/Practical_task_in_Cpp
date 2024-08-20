#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

// ANSI escape codes for colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

// Mock class for Game class to isolate the unit test
class MockGame {
public:
    void startGame() {
        int guess;
        bool correct = false;

        std::cout << BLUE << "Вгадай число від 1 до 100: " << RESET;

        while (!correct) {
            std::string input = "invalid_input"; // Simulate invalid input
            std::istringstream iss(input);
            iss >> guess;

            if (iss.fail()) {
                throw std::invalid_argument("Invalid input. Please enter a number.");
            }

            correct = checkGuess(guess);
        }

        displayResult(true);
    }

    bool checkGuess(int guess) {
        // Implement the logic for checking the guess
        // Return true for valid guess, false otherwise
    }

    void displayResult(bool result) {
        // Implement the logic for displaying the result
    }
};

// Unit test for the startGame method
void testStartGameHandlesInvalidInput() {
    MockGame game;

    try {
        game.startGame();
        std::cerr << "Error: Invalid input handling test failed." << std::endl;
    } catch (const std::invalid_argument& e) {
        if (std::string(e.what()) != "Invalid input. Please enter a number.") {
            std::cerr << "Error: Invalid input handling test failed." << std::endl;
        }
    }
}

int main() {
    testStartGameHandlesInvalidInput();
    return 0;
}