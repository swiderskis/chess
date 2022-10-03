#include "Menu.hpp"

// Methods
bool Menu::validUserInput(char input, string validInput) {
    string invalidCharInput = "ERROR: Invalid column input!\n";

    if (validInput.find(input) != std::string::npos) {
        return true;
    } else {
        cout << invalidCharInput;
        return false;
    }
}

// Checks if int input is valid
bool Menu::validUserInput(int input, int minValidInput, int maxValidInput) {
    string invalidIntInput = "ERROR: Invalid row input!\n";

    if (input < minValidInput || input > maxValidInput) {
        cout << invalidIntInput;
        return false;
    } else {
        return true;
    }
}

// Converts char col input into int input
int Menu::charToIntInput(char input) {
    string chars = "ABCDEFGH";
    return chars.find(input);

}
// Clears console
// Taken from https://stackoverflow.com/questions/6486289/how-can-i-clear-console
void Menu::clearConsole() {
    #if defined _WIN32
        system("cls");
        //clrscr(); // including header file : conio.h
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
    #elif defined (__APPLE__)
        system("clear");
    #endif
}
