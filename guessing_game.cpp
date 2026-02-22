#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

void printWelcomeMessage() {
    cout << "Welcome to the Number Guessing Game!\n";
    cout << "I'm thinking of a number between 1 and 100.\n";
}

int getDifficultyLevel() {
    int level;
    cout << "Please select the difficulty level:\n";
    cout << "1. Easy (10 chances)\n";
    cout << "2. Medium (5 chances)\n";
    cout << "3. Hard (3 chances)\n";
    cout << "Enter your choice: ";
    cin >> level;
    return level;
}

int getTotalChances(int level) {
    switch (level) {
        case 1: return 10;
        case 2: return 5;
        case 3: return 3;
        default: return 5; // Default to medium if invalid input
    }
}

void playGame() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    int number = rand() % 100 + 1; // Random number between 1 and 100
    int level = getDifficultyLevel();
    int totalChances = getTotalChances(level);
    int attempts = 0;
    bool guessedCorrectly = false;
    int guess;

    auto startTime = chrono::steady_clock::now();

    cout << "Great! You have selected the " 
         << (level == 1 ? "Easy" : level == 2 ? "Medium" : "Hard") 
         << " difficulty level.\n";

    while (attempts < totalChances && !guessedCorrectly) {
        cout << "Enter your guess: ";
        cin >> guess;
        attempts++;

        if (guess == number) {
            guessedCorrectly = true;
            cout << "Congratulations! You guessed the correct number in " 
                 << attempts << " attempts.\n";
        } else {
            cout << "Incorrect! The number is " 
                 << (guess < number ? "greater than " : "less than ") 
                 << guess << ".\n";
        }
    }

    if (!guessedCorrectly) {
        cout << "Sorry, you've run out of chances. The number was " << number << ".\n";
    }

    auto endTime = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = endTime - startTime;
    cout << "Time taken: " << elapsed_seconds.count() << " seconds.\n";
}

bool playAgain() {
    char choice;
    cout << "Would you like to play again? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

int main() {
    do {
        printWelcomeMessage();
        playGame();
    } while (playAgain());

    cout << "Thank you for playing!\n";
    return 0;
}
